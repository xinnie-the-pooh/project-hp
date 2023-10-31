
/*= HP 34401 Multimeter =====================================================*/

/*===========================================================================*/
/*  Please do not use global variables or arrays in the include file of      */
/*  instrument drivers that will be submitted for inclusion into the         */
/*  LabWindows Instrument Driver Library.                                    */
/*===========================================================================*/

#ifndef __hp34401a_HEADER
#define __hp34401a_HEADER

#include <vpptype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************/
/*= Define Instrument Specific Error Codes Here =============================*/
/*****************************************************************************/
#define VI_ERROR_FILE_OPEN              (_VI_ERROR+0x3FFC0800L)
#define VI_ERROR_FILE_WRITE             (_VI_ERROR+0x3FFC0801L)
#define VI_ERROR_SECURITY_CODE          (_VI_ERROR+0x3FFC0802L)
#define VI_ERROR_INTERPRETING_RESPONSE  (_VI_ERROR+0x3FFC0803L)
#define VI_ERROR_STAMP                  (_VI_ERROR+0x3FFC0805L) 
#define VI_ERROR_OUTOFF_RANGE           (_VI_ERROR+0x3FFC0806L) 

/*****************************************************************************/
/*= GLOBAL USER-CALLABLE FUNCTION DECLARATIONS (Exportable Functions) =======*/
/*****************************************************************************/
ViStatus _VI_FUNC hp34401a_init (ViRsrc resourceName, ViBoolean IDQuery,
                                 ViBoolean resetDevice, ViPSession instrumentHandle);
ViStatus _VI_FUNC hp34401a_conf (ViSession instrumentHandle, ViInt16 function,
                                 ViBoolean autorange, ViReal64 range,
                                 ViInt16 resolution);
ViStatus _VI_FUNC hp34401a_confTrig (ViSession instrumentHandle,
                                     ViInt16 triggerSource,
                                     ViBoolean autoTriggerDelay,
                                     ViReal64 triggerDelay, ViInt32 triggerCount,
                                     ViInt32 sampleCount);
ViStatus _VI_FUNC hp34401a_confAperTime (ViSession instrumentHandle,
                                         ViInt16 function, ViReal64 apertureTime);
ViStatus _VI_FUNC hp34401a_confIntegratTime (ViSession instrumentHandle,
                                             ViInt16 function,
                                             ViReal64 integrationTime);
ViStatus _VI_FUNC hp34401a_confMisc (ViSession instrumentHandle, ViInt16 autozero,
                                     ViReal64 detectorBandwidth,
                                     ViBoolean autoImpedance);
ViStatus _VI_FUNC hp34401a_waitForTrigger (ViSession instrumentHandle);
ViStatus _VI_FUNC hp34401a_softTrig (ViSession instrumentHandle);
ViStatus _VI_FUNC hp34401a_abortMeas (ViSession instrumentHandle);
ViStatus _VI_FUNC hp34401a_beeper (ViSession instrumentHandle,
                                   ViBoolean beeperState, ViBoolean beep);
ViStatus _VI_FUNC hp34401a_singleMeas (ViSession instrumentHandle,
                                       ViPReal64 measurement);
ViStatus _VI_FUNC hp34401a_multiMeas (ViSession instrumentHandle,
                                      ViInt32 timeOutmsec, ViPInt16 ofMeasurements,
                                      ViReal64 _VI_FAR measurements[]);
ViStatus _VI_FUNC hp34401a_actMathOp (ViSession instrumentHandle,
                                      ViInt16 mathOperation, ViBoolean state);
ViStatus _VI_FUNC hp34401a_fetchMeas (ViSession instrumentHandle,
                                      ViInt32 timeOutmsec,
                                      ViPInt16 ofMeasurements,
                                      ViReal64 _VI_FAR measurements[]);
ViStatus _VI_FUNC hp34401a_confNull (ViSession instrumentHandle, ViReal64 nullValue);
ViStatus _VI_FUNC hp34401a_confDbMeas (ViSession instrumentHandle,
                                       ViReal64 dBReference);
ViStatus _VI_FUNC hp34401a_confDbmMeas (ViSession instrumentHandle,
                                        ViReal64 dBmReference);
ViStatus _VI_FUNC hp34401a_confLimitTest (ViSession instrumentHandle,
                                          ViReal64 highLimit, ViReal64 lowLimit);
ViStatus _VI_FUNC hp34401a_display (ViSession instrumentHandle,
                                    ViBoolean displayState,
                                    ViChar _VI_FAR displayMessage[],
                                    ViBoolean clearMessage);
ViStatus _VI_FUNC hp34401a_checkTerminals (ViSession instrumentHandle,
                                           ViPInt16 terminals);
ViStatus _VI_FUNC hp34401a_checkScpiVersion (ViSession instrumentHandle,
                                             ViPInt16 year, ViPInt16 versionNumber);
ViStatus _VI_FUNC hp34401a_writeInstrData (ViSession instrumentHandle,
                                           ViString writeBuffer);
ViStatus _VI_FUNC hp34401a_readInstrData (ViSession instrumentHandle,
                                          ViInt16 numberBytesToRead,
                                          ViChar _VI_FAR readBuffer[],
                                          ViPInt32 numBytesRead);
ViStatus _VI_FUNC hp34401a_reset (ViSession instrumentHandle);
ViStatus _VI_FUNC hp34401a_selfTest (ViSession instrumentHandle,
                                     ViPInt16 selfTestResult,
                                     ViChar _VI_FAR selfTestMessage[]);
ViStatus _VI_FUNC hp34401a_errorQuery (ViSession instrumentHandle,
                                       ViPInt32 errorCode,
                                       ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC hp34401a_errorMessage (ViSession instrumentHandle,
                                         ViStatus errorCode,
                                         ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC hp34401a_revisionQuery (ViSession instrumentHandle,
                                          ViChar _VI_FAR instrumentDriverRevision[],
                                          ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC hp34401a_calSecure (ViSession instrumentHandle,
                                      ViChar _VI_FAR securityCode[],
                                      ViBoolean calibration);
ViStatus _VI_FUNC hp34401a_calCode (ViSession instrumentHandle,
                                    char newSecurityCode[]);
ViStatus _VI_FUNC hp34401a_calStamp (ViSession instrumentHandle,
                                     ViChar _VI_FAR stamp[]);
ViStatus _VI_FUNC hp34401a_calibrate (ViSession instrumentHandle,
                                      ViReal64 calibrationValue,
                                      ViPInt16 calibrationCode);
ViStatus _VI_FUNC hp34401a_close (ViSession instrumentHandle);


#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

/*****************************************************************************/
/*=== END INCLUDE FILE ======================================================*/
/*****************************************************************************/

#endif
