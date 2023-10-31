/*****************************************************************************/
/*   Copyright 1995 National Instruments Corporation.  All Rights Reserved.  */
/*****************************************************************************/

#include <formatio.h>
#include <visa.h>
#include <ansi_c.h>
#include "hp34401a.h"

#define hp34401a_REVISION     "Rev 1.0b, 9/95, CVI 3.1" /*  Instrument driver revision */
#define BUFFER_SIZE     256L         /* File I/O buffer size */
#define MAX_CMD_LENGTH  256L
    
/* = Hewlett-Packard 34401A Multimeter (VISA) ============================== */
/*  LabWindows 3.1 Instrument Driver                                         */
/*  Original Release: October, 1992                                          */
/*  By: HG, LWILDP, National Instruments, Austin, TX                         */
/*     PH. (800)433-3488   Fax (512)794-5678                                 */
/*  Originally written in C                                                  */
/*  Modification History:                                                    */
/*                                                                           */
/*      June 1995 -  Modified the LabWindows/CVI instrument driver to use    */
/*                   VISA I/O calls.                                         */
/*                   Modified by: JBS, National Instruments, Austin, TX      */
/*                                                                           */
/*      Sept 1995 -  The finished verson of the VISA port was mis-placed and */
/*                   an unfinished version was inadvertently shipped with    */
/*                   CVI 3.1.  This is a Beta Version of the VISA port and   */
/*                   needs to be tested.  The driver should function properly*/
/*                   because the port to VISA only involved changing the     */
/*                   syntax of the I/O calls and Status tracking/reporting   */
/*                   to match the VISA specs.                                */
/*                   Modified by: JRO, National Instruments, Austin, TX      */
/*                                                                           */
/*      Sept 1995 -  Changes to the VISA driver were tested and the following*/
/*                   fixes were made to the instrument driver: Timeout values*/
/*                   changed in the _multiMeas and _fetchMeas functions to   */
/*                   match millisecond units.  Fixed format specifier errors */
/*                   in the _fetchMeas and _checkInstrStatus functions by    */
/*                   changing %d to %d[b2] in the Fmt statements.  Fixed the */
/*                   read count in the viRead statements in the _multiMeas   */
/*                   and _singleMeas functions. Removed the function         */
/*                   localRemote because the commands used are for the RS232 */
/*                   interface which is not supported by this driver.        */
/*                                                                           */
/*                   Modified by: ELH , National Instruments, Austin, TX     */
/*                   Phone (800) 433-3488  Fax (512) 794-5678                */    
/*                                                                           */
/*      June 1996:   Modified for MDLL compatibility.                        */
/*                   Modified by:  TKN, National Instruments                 */
/*                                                                           */
/* ========================================================================= */
 
/*****************************************************************************/
/*= INSTRUMENT-DEPENDENT COMMAND ARRAYS =====================================*/
/*****************************************************************************/
static ViString funcStr[] = {"VOLT:AC", "VOLT", "VOLT:RAT", "CURR:AC", "CURR", "RES","FRES",    
                             "FREQ", "PER", "CONT", "DIOD"}; 
static ViString func2Str[] = {"VOLT:AC","VOLT","VOLT:RAT","CURR:AC","CURR","RES","FRES",    
                              "FREQ:VOLT" ,"PER:VOLT"};
static ViString resolStr[] = {"MAX","DEF","MIN"};
static ViString resolModeStr[] = {"MIN","MAX"};
static ViString mathOpStr[] = {"NULL","AVER","DB","DBM","LIM"};
static ViString trigSrceStr[] = {"IMM", "EXT", "BUS"};
static ViString terminalsStr[] = {"REAR","FRON"};
static ViString autoZeroStr[] = {"OFF","ON","ONCE"};
static ViString autoImpedStr[] = {"OFF","ON"};
static ViString beeperState[] = {"OFF","ON"};
static ViReal64 funLowRange[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0000033};
static ViReal64 funHighRange[] = {100.0, 100.0, 0.0, 3.0, 3.0, 100000000.0, 100000000.0,
                                  300000.0, 0.33};
  
/*****************************************************************************/
/*= INSTRUMENT-DEPENDENT STATUS/RANGE STRUCTURE  ============================*/
/*****************************************************************************/
/* hp34401a_stringValPair is used in the hp34401a_errorMessage function      */
/* hp34401a_statusDataRanges is used to track session dependent status & ranges*/
/*===========================================================================*/
typedef struct  hp34401a_stringValPair
{
   ViStatus stringVal;
   ViString stringName;
}  hp34401a_tStringValPair;
 
struct hp34401a_statusDataRanges {
    ViInt16 triggerMode;
    ViInt16 val2;
    ViInt16 val3;
    ViChar instrDriverRevision[256];
};

typedef struct hp34401a_statusDataRanges *hp34401a_instrRange;

/*****************************************************************************/
/*= UTILITY ROUTINE DECLARATIONS (Non-Exportable Functions) =================*/
/*****************************************************************************/
ViBoolean hp34401a_invalidViBooleanRange (ViBoolean val);
ViBoolean hp34401a_invalidViInt16Range (ViInt16 val, ViInt16 min, ViInt16 max);
ViBoolean hp34401a_invalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max);
ViBoolean hp34401a_invalidViUInt16Range (ViUInt16 val, ViUInt16 min, ViUInt16 max);
ViBoolean hp34401a_invalidViUInt32Range (ViUInt32 val, ViUInt32 min, ViUInt32 max);
ViBoolean hp34401a_invalidViReal32Range (ViReal32 val, ViReal32 min, ViReal32 max);
ViBoolean hp34401a_invalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max);
ViStatus hp34401a_initCleanUp (ViSession openRMSession, ViPSession openInstrSession, ViStatus currentStatus);
ViStatus hp34401a_readToFile (ViSession instrSession, ViString filename, ViUInt32 readBytes, ViPUInt32 retCount);
ViStatus hp34401a_writeFromFile (ViSession instrSession, ViString filename, ViUInt32 writeBytes, ViPUInt32 retCount);
ViStatus hp34401a_defaultInstrSetup (ViSession openInstrSession);
ViInt16 hp34401a_checkInstrStatus (ViStatus instrSession);
ViInt16 hp34401a_stringToInt (ViChar *array_of_strings[],ViInt16 start, ViInt16 stop,
                                ViChar *string,ViInt16 * index);

/*****************************************************************************/
/*====== USER-CALLABLE FUNCTIONS (Exportable Functions) =====================*/
/*****************************************************************************/

/*===========================================================================*/
/* Function: Initialize                                                      */
/* Purpose:  This function opens the instrument, queries the instrument      */
/*           for its ID, and initializes the instrument to a known state.    */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_init (ViRsrc resourceName, ViBoolean IDQuery,
                    ViBoolean reset, ViPSession instrSession)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte rdBuffer[BUFFER_SIZE];
    ViSession rmSession = 0;

    /*- Check input parameter ranges ----------------------------------------*/
    if (hp34401a_invalidViBooleanRange (IDQuery))
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViBooleanRange (reset))
        return VI_ERROR_PARAMETER3;

    /*- Open instrument session ---------------------------------------------*/
    if ((hp34401a_status = viOpenDefaultRM (&rmSession)) < 0)
        return hp34401a_status;

    if ((hp34401a_status = viOpen (rmSession, resourceName, VI_NULL, VI_NULL, instrSession)) < 0) {
        viClose (rmSession);
        return hp34401a_status;
    }

    /*- Configure VISA Formatted I/O ----------------------------------------*/
    if ((hp34401a_status = viSetAttribute (*instrSession, VI_ATTR_TMO_VALUE, 10000)) < 0)
        return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);
    if ((hp34401a_status = viSetBuf (*instrSession, VI_READ_BUF|VI_WRITE_BUF, 4000)) < 0)
        return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);
    if ((hp34401a_status = viSetAttribute (*instrSession, VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS)) < 0)
        return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);
    if ((hp34401a_status = viSetAttribute (*instrSession, VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS)) < 0)
        return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);

    /*- Identification Query ------------------------------------------------*/
    if (IDQuery) {
        if ((hp34401a_status = viWrite (*instrSession, "*IDN?", 5, &retCnt)) < 0)
            return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);
        if ((hp34401a_status = viRead (*instrSession, rdBuffer, BUFFER_SIZE, &retCnt)) < 0)
            return hp34401a_status;

        Scan (rdBuffer, "HEWLETT-PACKARD,34401A");
        if (NumFmtdBytes () != 22) 
            return hp34401a_initCleanUp (rmSession, instrSession, VI_ERROR_FAIL_ID_QUERY);
    }

    /*- Reset instrument ----------------------------------------------------*/
    if (reset) {
        if ((hp34401a_status = hp34401a_reset (*instrSession)) < 0)
            return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);
    }       
    else  /*- Send Default Instrument Setup ---------------------------------*/
        if ((hp34401a_status = hp34401a_defaultInstrSetup (*instrSession)) < 0)
            return hp34401a_initCleanUp (rmSession, instrSession, hp34401a_status);
                
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: hp34401a_conf                                                   */
/* Purpose: Configure hp34401 Multimeter.                                    */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_conf (ViSession instrSession, ViInt16 func,
                        ViBoolean autorange, ViReal64 range, ViInt16 resol)
{
    ViStatus    hp34401a_status = VI_SUCCESS;
    ViUInt32    retCnt = 0;
    ViChar      wrtBuf[256];

    if (hp34401a_invalidViInt16Range (func, 0, 10) )
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViInt16Range (autorange, 0, 1) )
        return VI_ERROR_PARAMETER3;
    if (autorange == VI_OFF)
        if (func < 9 && func != 2)
            if (hp34401a_invalidViReal64Range (range, funLowRange[func], funHighRange[func]))
                return VI_ERROR_PARAMETER4;
    if (hp34401a_invalidViInt16Range (resol, 0, 2))
        return VI_ERROR_PARAMETER5;
        
    /*  Configure the test  */
    if (func == 9 || func == 10)  {
        Fmt (wrtBuf, "%s<:CONF:%s\r\n", funcStr[func]);
        if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
            return hp34401a_status;
    }
    else  {
        /*  Configure the measurement  */
        if (autorange == VI_ON)
            Fmt (wrtBuf, "%s<:CONF:%s DEF,%s\r\n", funcStr[func], resolStr[resol]);
        else
            Fmt (wrtBuf, "%s<:CONF:%s %f,%s\r\n", funcStr[func], range, resolStr[resol]);
        if ((hp34401a_status = viWrite(instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
            return hp34401a_status;
    }
    
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Trigger configuration                                           */
/* Purpose: Configure Trigger                                                */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confTrig (ViSession instrSession, ViInt16 trig_srce,
                             ViBoolean auto_delay, ViReal64 trig_delay,
                             ViInt32 trig_cnt, ViInt32 samp_cnt)
{
    ViStatus    hp34401a_status = VI_SUCCESS;
    ViUInt32    retCnt = 0;
    ViChar      wrtBuf[256];

    if (hp34401a_invalidViInt16Range (trig_srce, 0, 2))
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViInt16Range (auto_delay, 0, 1))
        return VI_ERROR_PARAMETER3;
    if (hp34401a_invalidViReal64Range (trig_delay, 0.0, 3600.0))
        return VI_ERROR_PARAMETER4;
    if (hp34401a_invalidViInt32Range (trig_cnt, 1L, 50000L))
        return VI_ERROR_PARAMETER5;
    if (hp34401a_invalidViInt32Range (samp_cnt, 1L, 50000L))
        return VI_ERROR_PARAMETER6;
        
    if (!auto_delay)
        /*  Auto-delay off  */
        Fmt (wrtBuf, "%s<:TRIG:SOUR %s;DEL %f;COUN %d[b4];:SAMP:COUN %d[b4]\r\n", trigSrceStr[trig_srce], trig_delay,
        trig_cnt, samp_cnt);
    else
        Fmt (wrtBuf, "%s<:TRIG:SOUR %s;COUN %d[b4];DEL:AUTO ON;:SAMP:COUN %d[b4]\r\n", trigSrceStr[trig_srce], trig_cnt,
        samp_cnt);
    if ((hp34401a_status = viWrite(instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)  
        return hp34401a_status;

    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Aperture Time                                                   */
/* Purpose: Configure aperture time                                          */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confAperTime (ViSession instrSession, ViInt16 func,
                                  ViReal64 aper_time)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte rdBuf[BUFFER_SIZE], wrtBuf[BUFFER_SIZE] ;

    if (hp34401a_invalidViInt16Range (func, 7, 8))
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViReal64Range (aper_time, 0.00001, 1.0))
        return VI_ERROR_PARAMETER3;
        
    Fmt (wrtBuf, "%s<:%s:APER %f\r\n", funcStr[func], aper_time);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Intergration Time Configuration                                 */
/* Purpose: Configure intergration time                                      */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confIntegratTime (ViSession instrSession, ViInt16 func,
                                      ViReal64 integrat_time)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte wrtBuf[BUFFER_SIZE];

    if (func != 1 && func != 4 && func != 5 && func != 6)  
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViReal64Range (integrat_time, 0.02, 100.0))
        return VI_ERROR_PARAMETER3;
        
    Fmt (wrtBuf, "%s<:%s:NPLC %f\r\n", funcStr[func], integrat_time);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
 
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Misc. Configuration                                             */
/* Purpose: Performs other configuraion not in the above funcitons.          */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confMisc (ViSession instrSession, ViInt16 auto_zero,
                            ViReal64 bandwidth, ViBoolean auto_imped)

{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte wrtBuf[BUFFER_SIZE] ;
     
    if (hp34401a_invalidViInt16Range (auto_zero, 0, 2))
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViReal64Range (bandwidth, 3.0,200))
        return VI_ERROR_PARAMETER3;
    if (hp34401a_invalidViBooleanRange (auto_imped))
        return VI_ERROR_PARAMETER4;
        
    Fmt (wrtBuf, "%s<:ZERO:AUTO %s\r\n", autoZeroStr[auto_zero]);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    Fmt (wrtBuf, "%s<:INP:IMP:AUTO %s\r\n", autoImpedStr[auto_imped]);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    Fmt (wrtBuf, "%s<:DET:BAND %f\r\n", bandwidth);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;

    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Wait for trigger                                                */
/* Purpose: Waiting for trigger                                              */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_waitForTrigger (ViSession instrSession)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte wrtBuf[BUFFER_SIZE] ;

    if ((hp34401a_status = viWrite (instrSession, ":INIT\r\n", 7,&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Software trigger                                                */
/* Purpose: Software triggers the instrument                                 */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_softTrig (ViSession instrSession)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte rdBuf[BUFFER_SIZE], wrtBuf[BUFFER_SIZE] ;

    if ((hp34401a_status= viWrite (instrSession, "*TRG\r\n", 6, &retCnt)) < 0 )
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Abort measurement                                               */
/* Purpose: Abort measurement                                                */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_abortMeas (ViSession instrSession)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte rdBuf[BUFFER_SIZE], wrtBuf[BUFFER_SIZE] ;

    if ((hp34401a_status= viWrite (instrSession, ":ABOR\r\n", 7, &retCnt)) < 0 )
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Beeper                                                          */
/* Purpose: Configure beeper                                                 */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_beeper (ViSession instrSession, ViBoolean on_off,
                          ViBoolean instr_beep)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE];

    if (hp34401a_invalidViBooleanRange (on_off))
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViInt16Range (instr_beep, 0, 1))
        return VI_ERROR_PARAMETER3;
        
    if (instr_beep == 1)
        Fmt (wrtBuf, "%s<SYST:BEEP:STAT %s;:SYST:BEEP\r\n", beeperState[on_off]);
    else
        Fmt (wrtBuf, "%s<SYST:BEEP:STAT %s\r\n", beeperState[on_off]);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Single Measurement                                              */
/* Purpose: Configure single measurement                                     */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_singleMeas (ViSession instrSession, ViPReal64 reading)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte wrtBuf[BUFFER_SIZE],rdBuf[BUFFER_SIZE];
      
    if ((hp34401a_status = viWrite (instrSession, ":INIT;:FETC?\r\n", 14,&retCnt)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf, MAX_CMD_LENGTH,&retCnt)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%f", reading) != 1)  {
        hp34401a_status = VI_ERROR_INTERPRETING_RESPONSE;
        return hp34401a_status;
    }

    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Multiple Measurement                                            */
/* Purpose: Configure multiple measurement                                   */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_multiMeas (ViSession instrSession, ViInt32 timeout,
                              ViPInt16 num_readings, ViReal64 _VI_FAR readings[])
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte rdBuf[BUFFER_SIZE], wrtBuf[BUFFER_SIZE] ;
    ViReal64 trig_cnt = 0;
    ViInt16 samp_cnt = 0;

    if (hp34401a_invalidViInt32Range (timeout, 0, 1000000))
        return VI_ERROR_PARAMETER2;
        
    if ((hp34401a_status = viWrite (instrSession, ":TRIG:COUN?;:SAMP:COUN?\r\n", 25,&retCnt)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf, MAX_CMD_LENGTH, &retCnt)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%f[x]%d[b2]", &trig_cnt, &samp_cnt) != 2) {  
        hp34401a_status = VI_ERROR_INTERPRETING_RESPONSE;
        return hp34401a_status;
    }
    *num_readings = (ViInt16)((ViReal64)samp_cnt * trig_cnt);
    if ((hp34401a_status = viWrite (instrSession, ":INIT;:FETC?\r\n", 14,&retCnt)) < 0 )
        return hp34401a_status;
    if ((hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,timeout)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf, MAX_CMD_LENGTH, &retCnt)) < 0)  {
        if ((hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,timeout)) < 0)
            return hp34401a_status;
        return hp34401a_status;
    }
    if ((hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,timeout)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%*f[x]", *num_readings, readings) != 1)  {
        hp34401a_status = VI_ERROR_INTERPRETING_RESPONSE;
        return hp34401a_status;
    }

    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Active math operation                                           */
/* Purpose: Activates the selected math operation.                           */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_actMathOp (ViSession instrSession, ViInt16 math_op,
                               ViBoolean state)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE] ;

    if (hp34401a_invalidViInt16Range (math_op, 0, 4))
        return VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViInt16Range (state, 0, 1))
        return VI_ERROR_PARAMETER3;
        
    Fmt (wrtBuf, "%s<:CALC:FUNC %s;STAT %d[b2]\r\n", mathOpStr[math_op], state);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Fetch Measurement                                               */
/* Purpose: Send command to fetch results                                    */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_fetchMeas (ViSession instrSession,ViInt32 timeout, 
        ViPInt16 num_readings, ViReal64 _VI_FAR readings[])
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte rdBuf[BUFFER_SIZE], wrtBuf[BUFFER_SIZE] ;
    ViInt16 samp_cnt;
    ViReal64 trig_cnt;

    if (hp34401a_invalidViInt16Range (timeout, 0, 1000000))
        return VI_ERROR_PARAMETER2;
    if ((hp34401a_status = viWrite (instrSession, ":TRIG:COUN?;:SAMP:COUN?\r\n", 25, &retCnt)) < 0 )
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf,MAX_CMD_LENGTH, &retCnt)) < 0 )
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%f[x]%d[b2]", &trig_cnt, &samp_cnt) != 2)  {
        hp34401a_status = VI_ERROR_INTERPRETING_RESPONSE;
        return hp34401a_status;
    }
    *num_readings = (ViInt16)((ViReal64)samp_cnt * trig_cnt);
    if ((hp34401a_status = viWrite (instrSession, ":FETC?\r\n", 8, &retCnt)) < 0 )
        return hp34401a_status;
    if ((hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,timeout)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf,MAX_CMD_LENGTH, &retCnt)) < 0 )  {
            if ((hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,timeout)) < 0)
                return hp34401a_status;
            else hp34401a_status = VI_ERROR_TMO;
        return hp34401a_status;
    }
    if ((hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,timeout)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%*f[x]", *num_readings, readings) != 1) 
        return VI_ERROR_INTERPRETING_RESPONSE;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Configure null measurement                                      */
/* Purpose: Making null measurement                                          */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confNull (ViSession instrSession, ViReal64 null_val)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE] ;

    Fmt (wrtBuf, "%s<:CALC:NULL:OFFS %f\r\n", null_val);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: dB measurement                                                  */
/* Purpose: Making dB measurement                                            */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confDbMeas (ViSession instrSession, ViReal64 db_ref)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE] ;

    if (hp34401a_invalidViReal64Range (db_ref, 0.0, 200.0))
        return VI_ERROR_PARAMETER2;
        
    Fmt (wrtBuf, "%s<:CALC:DB:REF %f\r\n", db_ref);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: dBm measurement                                                 */
/* Purpose: Making dB measurement                                            */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confDbmMeas (ViSession instrSession, ViReal64 dbm_ref)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE] ;

    if (hp34401a_invalidViReal64Range (dbm_ref, 0.0, 8000.0))
        return VI_ERROR_PARAMETER2;

    Fmt (wrtBuf, "%s<:CALC:DBM:REF %f\r\n", dbm_ref);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Limit test                                                      */
/* Purpose: Perform pass/fail test on the limits specified                   */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_confLimitTest (ViSession instrSession, ViReal64 upper_lim,
                                   ViReal64 lower_lim)
{
ViStatus hp34401a_status = VI_SUCCESS;
ViUInt32 retCnt = 0;
ViByte  wrtBuf[BUFFER_SIZE] ;

    Fmt (wrtBuf, "%s<:CALC:LIM:UPP %f;LOW %f\r\n", upper_lim, lower_lim);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}
 
/* ========================================================================= */
/* Function: Display                                                         */
/* Purpose: Configure the front panel                                        */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_display (ViSession instrSession, ViBoolean on_off,
                           ViChar _VI_FAR message[], ViBoolean clear)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE];

    if (hp34401a_invalidViInt16Range (on_off, 0, 1))
        return VI_ERROR_PARAMETER2;
    if (StringLength (message) > 12)
        return VI_ERROR_PARAMETER3;
    if (hp34401a_invalidViInt16Range (clear, 0, 1))
        return VI_ERROR_PARAMETER4;
        
    if (clear == 1)
        Fmt (wrtBuf, "%s<:DISP:TEXT:CLE;:DISP:STAT %d[b2]\r\n", on_off);
    else
        Fmt (wrtBuf, "%s<:DISP:TEXT \"%s\";:DISP:STAT %d[b2]\r\n", message, on_off);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Check terminals                                                 */
/* Purpose: Check whether the front terminal are being used                  */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_checkTerminals (ViSession instrSession, ViPInt16 terminals)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE],rdBuf[BUFFER_SIZE];
    ViChar terminals_resp[5];

    if ((hp34401a_status= viWrite (instrSession, ":ROUTE:TERM?\r\n", 14, &retCnt)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf, MAX_CMD_LENGTH, &retCnt)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%s", terminals_resp) != 1)
        return VI_ERROR_INTERPRETING_RESPONSE;
    /*  Convert the string response to an integer.  */
    if (hp34401a_stringToInt (terminalsStr, 0, 1, terminals_resp, terminals) != 0)
        return hp34401a_status;

    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Check SCPI                                                      */
/* Purpose: Query SCPI vertion                                               */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_checkScpiVersion (ViSession instrSession, ViPInt16 year,
                                             ViPInt16 version)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE],rdBuf[BUFFER_SIZE];

    if ((hp34401a_status= viWrite (instrSession, ":SYST:VERS?\r\n", 13,&retCnt)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf, MAX_CMD_LENGTH,&retCnt)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%d[xb2]%d[b2]", year, version) != 2)  
        return VI_ERROR_INTERPRETING_RESPONSE;

    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Write To Instrument                                             */
/* Purpose:  This function writes a command string to the instrument.        */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_writeInstrData (ViSession instrSession, ViString writeBuffer)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    
    if ((hp34401a_status = viPrintf (instrSession, "%s", writeBuffer)) < 0)
        return hp34401a_status;

    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Read Instrument Buffer                                          */
/* Purpose:  This function reads the output buffer of the instrument.        */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_readInstrData (ViSession instrSession, ViInt16 numBytes,
                    ViChar _VI_FAR rdBuf[], ViPInt32 bytesRead)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    *bytesRead = 0L;
        
    if ((hp34401a_status = viRead (instrSession, rdBuf, numBytes, bytesRead)) < 0)
        return hp34401a_status;

    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Reset                                                           */
/* Purpose:  This function resets the instrument.  If the reset function     */
/*           is not supported by the instrument, this function returns       */
/*           the warning VI_WARN_NSUP_RESET.                                 */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_reset (ViSession instrSession)
{
    ViUInt32 retCnt = 0;
    ViStatus hp34401a_status = VI_SUCCESS;

    /*  Initialize the instrument to a known state.  */
    if ((hp34401a_status = viWrite (instrSession, "*CLS\r\n", 6, &retCnt)) < 0)
        return hp34401a_status;

    if ((hp34401a_status = hp34401a_defaultInstrSetup (instrSession)) < 0)  
        return hp34401a_status;
        
     /*  Set timeout to 10 seconds  */
    hp34401a_status = viSetAttribute (instrSession, VI_ATTR_TMO_VALUE,10000);
   
    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Self-Test                                                       */
/* Purpose:  This function executes the instrument self-test and returns     */
/*           the result. If the self test function is not supported by the   */
/*           instrument, this function returns the warning                   */
/*           VI_WARN_NSUP_SELF_TEST.                                         */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_selfTest (ViSession instrSession, ViPInt16 testResult,
                    ViChar _VI_FAR testMessage[])
{
    ViUInt32 retCnt = 0;
    ViStatus hp34401a_status = VI_SUCCESS;
    
    if ((hp34401a_status = viWrite (instrSession, "*TST?\r\n", 7, &retCnt)) < 0)
        return hp34401a_status;

    if ((hp34401a_status = viScanf (instrSession, "%hd", testResult)) < 0)
        return hp34401a_status;
    Fmt (testMessage, "%s<%d[b2]", *testResult);
    
    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Error Query                                                     */
/* Purpose:  This function queries the instrument error queue, and returns   */
/*           the result. If the error query function is not supported by the */
/*           instrument, this function returns the warning                   */
/*           VI_WARN_NSUP_ERROR_QUERY.                                       */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_errorQuery (ViSession instrSession, ViPInt32 errCode,
                    ViChar _VI_FAR errMessage[])
{
    ViUInt32 retCnt = 0;
    ViStatus hp34401a_status = VI_SUCCESS;

    if ((hp34401a_status = viWrite (instrSession, ":SYST:ERR?\r\n", 12, &retCnt)) < 0)
        return hp34401a_status;
    
    if ((hp34401a_status = viScanf (instrSession, "%ld,\"%[^\"]", errCode, errMessage)) < 0)
        return hp34401a_status;


    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Error Message                                                   */
/* Purpose:  This function translates the error return value from the        */
/*           instrument driver into a user-readable string.                  */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_errorMessage (ViSession instrSession, ViStatus errorCode,
                    ViChar _VI_FAR errMessage[])
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViInt16 i;
    static hp34401a_tStringValPair statusDescArray[] = {
        {VI_WARN_NSUP_ID_QUERY,     "WARNING: ID Query not supported"},
        {VI_WARN_NSUP_RESET,        "WARNING: Reset not supported"},
        {VI_WARN_NSUP_SELF_TEST,    "WARNING: Self-test not supported"},
        {VI_WARN_NSUP_ERROR_QUERY,  "WARNING: Error Query not supported"},     
        {VI_WARN_NSUP_REV_QUERY,    "WARNING: Revision Query not supported"},
        {VI_ERROR_PARAMETER1,   "ERROR: Parameter 1 out of range"},
        {VI_ERROR_PARAMETER2,   "ERROR: Parameter 2 out of range"},
        {VI_ERROR_PARAMETER3,   "ERROR: Parameter 3 out of range"},
        {VI_ERROR_PARAMETER4,   "ERROR: Parameter 4 out of range"},
        {VI_ERROR_PARAMETER5,   "ERROR: Parameter 5 out of range"},
        {VI_ERROR_PARAMETER6,   "ERROR: Parameter 6 out of range"},
        {VI_ERROR_PARAMETER7,   "ERROR: Parameter 7 out of range"},
        {VI_ERROR_PARAMETER8,   "ERROR: Parameter 8 out of range"},
        {VI_ERROR_FAIL_ID_QUERY,"ERROR: Identification query failed"},
        {VI_ERROR_INV_RESPONSE, "ERROR: Interpreting instrument response"},
        {VI_ERROR_FILE_OPEN,    "ERROR: Opening the specified file"},
        {VI_ERROR_FILE_WRITE,   "ERROR: Writing to the specified file"},
        {VI_ERROR_INTERPRETING_RESPONSE, "ERROR: Interpreting the instrument's response"},
        {VI_ERROR_SECURITY_CODE,    "ERROR: Security code too long"},
        {VI_ERROR_STAMP,    "ERROR: STAMP TOO LONG"},
        {VI_ERROR_OUTOFF_RANGE, "ERROR: Data outoff range."},
        {VI_NULL, VI_NULL}
    };

    hp34401a_status = viStatusDesc (instrSession, errorCode, errMessage);
    if (hp34401a_status == VI_WARN_UNKNOWN_STATUS) {
        for (i=0; statusDescArray[i].stringName; i++) {
            if (statusDescArray[i].stringVal == errorCode) {
                strcpy (errMessage, statusDescArray[i].stringName);
                return (VI_SUCCESS);
            }
        }
        sprintf (errMessage, "Unknown Error 0x%08lX", errorCode);
        return (VI_WARN_UNKNOWN_STATUS);
    }
    
    hp34401a_status = VI_SUCCESS;
    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Revision Query                                                  */
/* Purpose:  This function returns the driver and instrument revisions.      */
/*           If the revision query function is not supported by the          */ 
/*           instrument, this function returns the warning                   */
/*           VI_WARN_NSUP_REV_QUERY.                                         */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_revisionQuery (ViSession instrSession,
                    ViChar _VI_FAR driverRev[], ViChar _VI_FAR instrRev[])
{
    ViUInt32 retCnt = 0;
    ViStatus hp34401a_status = VI_SUCCESS;

    if ((hp34401a_status = viWrite (instrSession, "*IDN?", 5, &retCnt)) < 0)
        return hp34401a_status;

    if ((hp34401a_status = viScanf (instrSession, "%*[^,],%*[^,],%*[^,],%[^\n]", instrRev)) < 0)
        return hp34401a_status;

    strcpy (driverRev, hp34401a_REVISION);
    
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Secure/unsecure calibration                                     */
/* Purpose: Switch to secure/insecure calibration                            */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_calSecure (ViSession instrSession, ViChar _VI_FAR security_code[], 
                                    ViBoolean secure)
{
ViStatus hp34401a_status = VI_SUCCESS;
ViUInt32 retCnt = 0;
ViByte  wrtBuf[BUFFER_SIZE] ;

    if (StringLength (security_code) > 12)
        return  VI_ERROR_PARAMETER2;
    if (hp34401a_invalidViBooleanRange (secure))
        return VI_ERROR_PARAMETER3;
        
    Fmt (wrtBuf, "%s<:CAL:SEC:STAT %d[b2],%s\r\n", secure, security_code);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}


/* ========================================================================= */
/* Function: Calibrate code                                                  */
/* Purpose: Allow user to change the security code                           */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_calCode (ViSession instrSession, ViChar _VI_FAR new_cal_code[])
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE],rdBuf[BUFFER_SIZE] ;

    if (StringLength (new_cal_code) > 12)
        return  VI_ERROR_PARAMETER2;
        
    Fmt (wrtBuf, "%s<:CAL:SEC:CODE %s\r\n", new_cal_code);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Calibrate stamp                                                 */
/* Purpose: Allow user to store in nonvolital memory                         */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_calStamp (ViSession instrSession, ViChar _VI_FAR stamp[])
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE],rdBuf[BUFFER_SIZE]  ;

    if (StringLength (stamp) > 40)
        return  VI_ERROR_PARAMETER2;
        
    Fmt (wrtBuf, "%s<:CAL:STR \"%s\"\r\n", stamp);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    /*  Check the Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/* ========================================================================= */
/* Function: Full calibration                                                */
/* Purpose: Making full calibration                                          */
/* ========================================================================= */
ViStatus _VI_FUNC hp34401a_calibrate (ViSession instrSession, ViReal64 cal_val,
                             ViPInt16 cal_code)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    ViByte  wrtBuf[BUFFER_SIZE], rdBuf[BUFFER_SIZE]  ;

    Fmt (wrtBuf, "%s<:CAL:VAL %f;:CAL?\r\n", cal_val);
    if ((hp34401a_status = viWrite (instrSession, wrtBuf, NumFmtdBytes (),&retCnt)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession, rdBuf, MAX_CMD_LENGTH,&retCnt)) < 0)
        return hp34401a_status;
    if (Scan (rdBuf, "%s>%d[b2]", cal_code) != 1) 
        return VI_ERROR_INTERPRETING_RESPONSE;
    /*  Check the Event Status Byte of the instrument for proper execution.  */
    if (hp34401a_checkInstrStatus (instrSession) != 0)
        return hp34401a_status;
        
    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Close                                                           */
/* Purpose:  This function closes the instrument.                            */
/*===========================================================================*/
ViStatus _VI_FUNC hp34401a_close (ViSession instrSession)
{
    ViSession rmSession;
    ViStatus hp34401a_status = VI_SUCCESS;

    if ((hp34401a_status = viGetAttribute (instrSession, VI_ATTR_RM_SESSION, &rmSession)) < 0)
        return hp34401a_status;
    
    hp34401a_status = viClose (instrSession);
    viClose (rmSession);

    return hp34401a_status;
}

/*****************************************************************************/
/*= UTILITY ROUTINES (Non-Exportable Functions) =============================*/
/*****************************************************************************/

/*===========================================================================*/
/* Function: Boolean Value Out Of Range - ViBoolean                          */
/* Purpose:  This function checks a Boolean to see if it is equal to VI_TRUE */
/*           or VI_FALSE. If the value is out of range, the return value is  */
/*           VI_TRUE, otherwise the return value is VI_FALSE.                */
/*===========================================================================*/
ViBoolean hp34401a_invalidViBooleanRange (ViBoolean val)
{
    return ((val != VI_FALSE && val != VI_TRUE) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Short Signed Integer Value Out Of Range - ViInt16               */
/* Purpose:  This function checks a short signed integer value to see if it  */  
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range, the return value is VI_TRUE, otherwise the return     */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean hp34401a_invalidViInt16Range (ViInt16 val, ViInt16 min, ViInt16 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Long Signed Integer Value Out Of Range - ViInt32                */
/* Purpose:  This function checks a long signed integer value to see if it   */  
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range,  the return value is VI_TRUE, otherwise the return    */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean hp34401a_invalidViInt32Range  (ViInt32 val, ViInt32 min, ViInt32 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Short Unsigned Integer Value Out Of Range - ViUInt16            */
/* Purpose:  This function checks a short unsigned integer value to see if it*/  
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range,  the return value is VI_TRUE, otherwise the return    */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean hp34401a_invalidViUInt16Range  (ViUInt16 val, ViUInt16 min, ViUInt16 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Long Unsigned Integer Value Out Of Range - ViUInt32             */
/* Purpose:  This function checks a long unsigned integer value to see if it */  
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range,  the return value is VI_TRUE, otherwise the return    */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean hp34401a_invalidViUInt32Range  (ViUInt32 val, ViUInt32 min, ViUInt32 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Real (Float) Value Out Of Range - ViReal32                      */
/* Purpose:  This function checks a real (float) value to see if it lies     */  
/*           between a minimum and maximum value.  If the value is out of    */
/*           range, the return value is VI_TRUE, otherwise the return value  */
/*           is VI_FALSE.                                                    */
/*===========================================================================*/
ViBoolean hp34401a_invalidViReal32Range  (ViReal32 val, ViReal32 min, ViReal32 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Real (Double) Value Out Of Range - ViReal64                     */
/* Purpose:  This function checks a real (ViReal64) value to see if it lies  */  
/*           between a minimum and maximum value.  If the value is out of    */
/*           range, the return value is VI_TRUE, otherwise the return value  */
/*           is VI_FALSE.                                                    */
/*===========================================================================*/
ViBoolean hp34401a_invalidViReal64Range  (ViReal64 val, ViReal64 min, ViReal64 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Initialize Clean Up                                             */
/* Purpose:  This function is used only by the hp34401a_init function.  When */
/*           an error is detected this function is called to close the       */
/*           open resource manager and instrument object sessions and to     */
/*           set the instrSession that is returned from hp34401a_init to     */
/*           VI_NULL.                                                        */
/*===========================================================================*/
ViStatus hp34401a_initCleanUp (ViSession openRMSession,
                    ViPSession openInstrSession, ViStatus currentStatus)
{
    viClose (*openInstrSession);
    viClose (openRMSession);
    *openInstrSession = VI_NULL;
    
    return currentStatus;
}

/*===========================================================================*/
/* Function: Read To File From Instrument                                    */
/* Purpose:  This function is used to read data from the instrument and      */
/*           write it to a user specified file.                              */
/*===========================================================================*/
ViStatus hp34401a_readToFile (ViSession instrSession, ViString filename,
                    ViUInt32 readBytes, ViPUInt32 retCount)
{
    ViStatus  hp34401a_status = VI_SUCCESS;
    ViByte    buffer[BUFFER_SIZE];
    ViUInt32  bytesReadInstr = 0, bytesWrittenFile = 0;
    FILE     *targetFile;

    *retCount = 0L;
    if ((targetFile = fopen (filename, "wb")) == VI_NULL)
        return VI_ERROR_FILE_OPEN; /* not defined by VTL */

    for (;;) {
        if (readBytes > BUFFER_SIZE)
            hp34401a_status = viRead (instrSession, buffer, BUFFER_SIZE, &bytesReadInstr);
        else
            hp34401a_status = viRead (instrSession, buffer, readBytes, &bytesReadInstr);

        bytesWrittenFile = fwrite (buffer, sizeof (ViByte), (size_t)bytesReadInstr, targetFile);
        *retCount += bytesWrittenFile;
        if (bytesWrittenFile < bytesReadInstr)
            hp34401a_status = VI_ERROR_FILE_WRITE; /* not defined by VTL */

        if ((readBytes <= BUFFER_SIZE) || (hp34401a_status <= 0) || (hp34401a_status == VI_SUCCESS_TERM_CHAR))
            break;

        readBytes -= BUFFER_SIZE;
    }

    fclose (targetFile);
    return hp34401a_status;
}

/*===========================================================================*/
/* Function: Write From File To Instrument                                   */
/* Purpose:  This function is used to read data from a user specified file   */
/*           and write it to the instrument.                                 */
/*===========================================================================*/
ViStatus hp34401a_writeFromFile (ViSession instrSession, ViString filename,
                    ViUInt32 writeBytes, ViPUInt32 retCount)
{
    ViStatus  hp34401a_status = VI_SUCCESS;
    ViByte    buffer[BUFFER_SIZE];
    ViUInt32  bytesRead = 0, bytesWritten = 0;
    FILE     *sourceFile;
    ViBoolean sendEnd = VI_FALSE;

    *retCount = 0L;
    if ((sourceFile = fopen (filename, "rb")) == VI_NULL)
        return VI_ERROR_FILE_OPEN; /* not defined by VTL */

    while (!feof (sourceFile)) {
        bytesRead = (ViUInt32)fread (buffer, sizeof (ViByte), BUFFER_SIZE, sourceFile);
        if ((writeBytes > BUFFER_SIZE) && (bytesRead == BUFFER_SIZE)) {
            viGetAttribute (instrSession, VI_ATTR_SEND_END_EN, &sendEnd);
            viSetAttribute (instrSession, VI_ATTR_SEND_END_EN, VI_FALSE);
            hp34401a_status = viWrite (instrSession, buffer, BUFFER_SIZE, &bytesWritten);
            viSetAttribute (instrSession, VI_ATTR_SEND_END_EN, sendEnd);
            writeBytes -= BUFFER_SIZE;
            *retCount += bytesWritten;
            if (hp34401a_status < 0)
                break;
        }
        else {
            hp34401a_status = viWrite (instrSession, buffer, ((bytesRead < writeBytes) ? bytesRead : writeBytes), &bytesWritten);
            *retCount += bytesWritten;
            break;
        }
    }

    fclose (sourceFile);
    return hp34401a_status;
}

/* ========================================================================= */
/*  Function Name:     Check Instrument Status                               */
/*  Description:       Checks the status of the Instrument                   */
/*                     and sets hp34401a Error accordingly.                  */
/*  Return Value:      hp34401a Error (Instrument Driver Status)             */
/* ========================================================================= */
ViInt16 hp34401a_checkInstrStatus (ViStatus instrSession)
{
ViStatus hp34401a_status = VI_SUCCESS;
ViUInt32 retCnt = 0;
ViByte  wrtBuf[BUFFER_SIZE],rdBuf[BUFFER_SIZE];
ViInt16 event_status;

    if ((viWrite (instrSession,"*ESR?\r\n",7,&retCnt)) < 0)
        return hp34401a_status;
    if ((hp34401a_status = viRead (instrSession,rdBuf,MAX_CMD_LENGTH,&retCnt)) < 0)
        return hp34401a_status;

    if (Scan (rdBuf, "%s>%d[b2]", &event_status) != 1)  
        return VI_ERROR_INTERPRETING_RESPONSE;
                    
    return hp34401a_status;
}

/* ========================================================================= */
/*  Function Name: String to Integer                                         */
/*  Description:   Compares a string to an array of strings and if a match   */
/*                 is found returns the array index of the match.            */
/*  Return Value:  Error (Instr. Driver Status)                              */
/* ========================================================================= */
ViInt16 hp34401a_stringToInt (ViChar *array_of_strings[],ViInt16 start, ViInt16 stop,
                                ViChar *string,ViInt16 * index)
{
ViStatus    hp34401a_status = VI_SUCCESS;
    ViInt16 i;
    ViInt16 found;

    hp34401a_status = 0;
    found = 0;
    for (i = start; i <= stop && !found; i++)
        if (!CompareStrings (array_of_strings[i], 0, string, 0, 0))  {
            *index = i;
            found = 1;
        }
    if (!found)
        hp34401a_status =  VI_ERROR_INTERPRETING_RESPONSE;
        
    return hp34401a_status;
}

/*****************************************************************************/
/*----------- INSERT INSTRUMENT-DEPENDENT UTILITY ROUTINES HERE -------------*/
/*****************************************************************************/

/*===========================================================================*/
/* Function: Default Instrument Setup                                        */
/* Purpose:  This function sends a default setup to the instrument.  This    */
/*           function is called by the hp34401a_reset operation and by the   */
/*           hp34401a_init function if the reset option has not been         */
/*           selected.  This function is useful for configuring any          */
/*           instrument settings that are required by the rest of the        */
/*           instrument driver functions such as turning headers ON or OFF   */
/*           or using the long or short form for commands, queries, and data.*/                                    
/*===========================================================================*/
ViStatus hp34401a_defaultInstrSetup (ViSession instrSession)
{
    ViStatus hp34401a_status = VI_SUCCESS;
    ViUInt32 retCnt = 0;
    
    return hp34401a_status;
}

/*****************************************************************************/
/*=== END INSTRUMENT DRIVER SOURCE CODE =====================================*/
/*****************************************************************************/
