
                        HP 34401A Multimeter (VISA I/O)
________________________________________________________________________________

  Introduction:

  This instrument driver provides programming support for the HP 34401A Multimeter
  (VISA I/O).  It contains functions for opening, configuring, taking measurements from,
  and closing the instrument.

________________________________________________________________________________

  Assumptions:

  To successfully use this module, the following conditions must be met:

         -  the instrument is connected to the GPIB.
         -  the GPIB address supplied to the initialize function must match the
            GPIB address of the instrument.

________________________________________________________________________________

  Error Codes:

  Error codes are returned as the return value of each instrument driver
  function. A program should examine this value after each call to an instrument
  driver function to determine if any error occurred. Possible error codes and
  their meanings are listed with the corresponding instrument driver function.

________________________________________________________________________________

  How To Use This Document:

  This document is intended to be used as a programming reference manual.
  It describes each function in the HP 34401A Multimeter (VISA I/O)
  instrument driver. The functions are listed in alphabetical order with a
  description of the function, C syntax of the function, a description of each
  parameter, and possible error codes.

________________________________________________________________________________

Function Tree Layout:

   HP 34401A Multimeter (VISA I/O)        Function Name:

      Initialize                                  hp34401a_init
      Configuration Functions
         Configure                                hp34401a_conf
         Trigger                                  hp34401a_confTrig
         Low Level Configure
            Aperture Time                         hp34401a_confAperTime
            Integration Time                      hp34401a_confIntegratTime
            Miscellaneous                         hp34401a_confMisc
      Action/Status Functions:
         Wait for Trigger                         hp34401a_waitForTrigger
         Software Trigger                         hp34401a_softTrig
         Abort Measurement                        hp34401a_abortMeas
         Beeper                                   hp34401a_beeper
      Data Functions
         Single Measurement                       hp34401a_singleMeas
         Multiple Measurements                    hp34401a_multiMeas
         Active Math Operation                    hp34401a_actMathOp
         Fetch Measurements                       hp34401a_fetchMeas
         Null Operation                           hp34401a_confNull
         dB Measurements                          hp34401a_confDbMeas
         dBm Measurements                         hp34401a_confDbmMeas
         Limit Testing                            hp34401a_confLimitTest
      Utility Functions
         Display                                  hp34401a_display
         Query Terminals                          hp34401a_checkTerminals
         Query SCPI Version                       hp34401a_checkScpiVersion
         Write To Instrument                      hp34401a_writeInstrData
         Read Instrument Data                     hp34401a_readInstrData
         Reset                                    hp34401a_reset
         Self-Test                                hp34401a_selfTest
         Error-Query                              hp34401a_errorQuery
         Error Message                            hp34401a_errorMessage
         Revision Query                           hp34401a_revisionQuery
         Calibration
            Secure/Unsecure                       hp34401a_calSecure
            Security Code                         hp34401a_calCode
            Stamp                                 hp34401a_calStamp
            Calibrate                             hp34401a_calibrate
      Close                                       hp34401a_close
________________________________________________________________________________

  HP 34401A Multimeter (VISA I/O)

      This instrument module provides programming support for the HP 34401A.
      The module is divided into the following functions:
      
      Functions/Classes:
      
      (1) Initialize:
      This function initializes the instrument and sets it to a default
      configuration.
      
      (2) Configuration Functions: (Class)
      This class of functions configures the instrument by setting acquisition
      and system configuration parameters.
      
      (3) Action/Status Functions: (Class)
      This class of functions begins or terminates an acquisition. It also
      provides functions which allow the user to determine the current status
      of the instrument.
      
      (4) Data Functions: (Class)
      This class of functions transfers data to or from the instrument.
      
      (6) Utility Functions: (Class)
      This class of functions provides lower level functions to communicate
      with the instrument, and change instrument parameters.
      
      (7) Close:
      This function takes the instrument offline.
      
________________________________________________________________________________

              The following functions are in alphabetical order.

________________________________________________________________________________

  hp34401a_abortMeas

      ViStatus hp34401a_abortMeas (ViSession instrumentHandle);

  Purpose

      Takes the instrument from the wait-for-trigger state to the idle
      state. This function can be used to abort a measurement.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_actMathOp

      ViStatus hp34401a_actMathOp (ViSession instrumentHandle, ViInt16 mathOperation,
                                   ViBoolean state);

  Purpose

      Activates the selected math operation.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      mathOperation

          Variable Type       ViInt16

          Activates the selected Math Operation.
          
          Valid Range:
          0 = Null Operation (Default)
          1 = Min-Max Operation
          2 = dB Measurements
          3 = dBm Measurements
          4 = Limit Testing
          
          

      state

          Variable Type       ViBoolean

          Enables/Disables the specified operation.
          
          Valid Range:
          VI_OFF (0) = Off (Default)
          VI_ON  (1) = On
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Math Operation out of range
          BFFC0003  State out of range
          
          BFFC0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_beeper

      ViStatus hp34401a_beeper (ViSession instrumentHandle, ViBoolean beeperState,
                                ViBoolean beep);

  Purpose

      Configures the beeper on the instrument.
      
      Notes:
      (1) When you disable the beeper, the instrument will not emit a tone
      when:
      
        1) A new min or max is found in a min-max test
        2) A stable reading is captured in the reading
           hold mode
        3) A limit is exceeded in a limit test
        4) A forward biased diode is measured in diode
           test
      
      Disabling the beeper has no effect on the tone generated when:
        1) An error is generated
        2) The continuity threshold is exceeded
        3) You turn off the front panel menu
      
      (2) The state of the beeper is stored in non-volatile, and does not
      change when power has been off or after a reset.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      beeperState

          Variable Type       ViBoolean

          Enables/Disables the beeper on the instrument.
          
          Valid Range:
          VI_OFF (0) - Off
          VI_ON  (1) - On (Default)
          
          

      beep

          Variable Type       ViBoolean

          Instructs the instrument to emit a
          
          Valid Range:
          VI_OFF (0) - No (Default)
          VI_ON  (1) - Yes
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Beeper State) out of range.
          BFFC0003  Parameter 3 (Beep) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF0002  Beeper State out of range
          BFFF0003  Beep out of range
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_calCode

      ViStatus hp34401a_calCode (ViSession instrumentHandle, char newSecurityCode[]);

  Purpose

      Allows the user to change the security code to prevent accidental or
      unauthorized calibrations of the instrument.
      The security code is stored in non-volatile memory, and does not change
      when power has been off or after a reset.
      
      Notes:
      (1) The instrument must first be unsecured before entering the new
      security code.
      
      (2) If the user forgets the security code, the security feature can be
      disabled by adding a jumper inside the multimeter, and then entering a
      new code. See the Instrument Service Guide for more information.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      newSecurityCode

          Variable Type       char []

          Configures the new security code.The security code can be up to 12
          alphanumeric characters. If calibration is going to be secured and
          unsecured from the remote interface only, then the first character
          must be a letter, but the remaining characters can be letters or
          numbers. You do not have to use all 12 characters. If calibration is
          going to be secured and unsecured from the remote interface and the
          front panel of the instrument, then an eight character security code
          should be used. The first two characters must be "HP" and the
          remaining characters must be numbers. Only the last six characters
          are recognized from the front panel, but all eight characters are
          required. (To unsecure the multimeter from the front panel, omit the
          "HP" and enter the remaining numbers.)
          
          Note: The security code is set to "HP034401" when the instrument is
          shipped from the factory. Only the last six characters ("034401") are
          recognized from the front panel.

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (New Security Code) too long
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_calSecure

      ViStatus hp34401a_calSecure (ViSession instrumentHandle, ViChar securityCode[],
                                   ViBoolean calibration);

  Purpose

      Secures\Unsecures the instrument for calibration.
      
      Notes:
      (1) When the instrument is shipped from the factory it is secured against
      calibrations. Before it can be calibrated, it must first be unsecured by
      entering the correct security code.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      securityCode

          Variable Type       ViChar[]

          Accepts the security code to secure or unsecure the instrument.
          
          Note:
          The security code is set to "HP034401" when the instrument is shipped
          from the factory. Only the last six characters ("034401") are
          recognized from the front panel.
          
          

      calibration

          Variable Type       ViBoolean

          Secures or Unsecures the instrument against calibrations.
          
          Valid Range:
          VI_OFF (0) - Unsecure
          VI_ON  (1) - Secure (Default)
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Security Code) too long
          BFFC0003  Parameter 3 (Cal Secure/Unsecure) out of range
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_calStamp

      ViStatus hp34401a_calStamp (ViSession instrumentHandle, ViChar stamp[]);

  Purpose

      Allows the user to store a string in nonvolatile calibration memory of
      the instrument. This string can be used for any application the user
      desires. One useful application is to store a calibration stamp
      specifying the date of the last calibration.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      stamp

          Variable Type       ViChar[]

          String to be saved in nonvolatile calibration memory of the
          instrument.  The calibration stamp can be up to 40 characters, but
          the front panel will only display the first 12. All forty characters
          can be read by the remote interface.
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Stamp) too long.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_calibrate

      ViStatus hp34401a_calibrate (ViSession instrumentHandle,
                                   ViReal64 calibrationValue,
                                   ViInt16 *calibrationCode);

  Purpose

      Performs a full calibration of the instrument. For the user the actual
      value of the calibration result is of minor interest. The main
      distinction here is 'zero or non-zero'. However, the actual value should
      be reported to the service people.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      calibrationValue

          Variable Type       ViReal64

          The voltage connected to the  instrument is used as a reference for
          calibration. The value of this voltage must be entered in this
          control.
          
          Default:       0.0
          

      calibrationCode

          Variable Type       ViInt16 (passed by reference)

          Returns the result of the calibration.
          
          Valid Range:
          
          0 - No error detected during calibration
          
          (See Instrument Manual for non-zero codes)
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0803  Error Scanning Response
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_checkScpiVersion

      ViStatus hp34401a_checkScpiVersion (ViSession instrumentHandle, ViInt16 *year,
                                          ViInt16 *versionNumber);

  Purpose

      Checks the Standard Commands for Programmable Instruments (SCPI) language
      version.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      year

          Variable Type       ViInt16 (passed by reference)

          Returns the year of the SCPI Version.
          

      versionNumber

          Variable Type       ViInt16 (passed by reference)

          Returns the SCPI version number. This version number and the year
          uniquely identify the SCPI Release.
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0803  Error Scanning Response.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_checkTerminals

      ViStatus hp34401a_checkTerminals (ViSession instrumentHandle,
                                        ViInt16 *terminals);

  Purpose

      Checks whether the front or rear terminals on the instrument are being
      used. Any measurement made using the front terminals can also be made
      using the input terminals on the rear panel.
      
      Notes:
      (1) The input terminals can only be configured from the front panel; the
      user cannot select the front or rear terminals from the remote interface,
      but can query the present setting.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      terminals

          Variable Type       ViInt16 (passed by reference)

          Returns whether the front or rear input terminals are presently being
          used.
          
          Valid Range:
          0 = Rear
          1 = Front

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0803  Error Scanning Response.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_close

      ViStatus hp34401a_close (ViSession instrumentHandle);

  Purpose

      This function performs the following operations:
      viClose (instrSession) and viClose (rmSession).
      
      Notes:
      
      (1) The instrument must be reinitialized to use it again.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_conf

      ViStatus hp34401a_conf (ViSession instrumentHandle, ViInt16 function,
                              ViBoolean autorange, ViReal64 range, ViInt16 resolution);

  Purpose

      This function configures the instrument, but does not put the instrument
      in the wait-for-trigger state or take a reading. All instrument settings
      not explicitly set by these functions are configured to the default
      settings pertaining to the specific measurement. These settings can be
      adjusted by the Low-Level Configure functions. Measurements can then be
      taken using the Measure Class functions.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      function

          Variable Type       ViInt16

          Sets the type of measurement to be configured.
          
          Valid Range:
          0 = Voltage AC
          1 = Voltage DC        (Default)
          2 = Voltage DC Ratio
          3 = Current AC
          4 = Current DC
          5 = 2-wire Resistance
          6 = 4-wire Resistance
          7 = Frequency
          8 = Period
          9 = Continuity test
          10 = Diode test
          
          

      autorange

          Variable Type       ViBoolean

          The range can be selected by either using autorange or manually
          selecting a fixed range.
          
          Valid Range:
          VI_OFF (0) - Off
          VI_ON  (1) - On (Default)
          
          Notes:
          Autoranging thresholds are: Down range at < 10% of range Up range at
          < 120% of range
          
          
          
          

      range

          Variable Type       ViReal64

          Configures a fixed measurement range. This control is ignored if
          autorange is enabled. The value entered in this control is used to
          select between the ranges listed below.
          
          Valid Range:
          The multimeter will accept ranges:
          
          Voltage AC          0 - 1000 V
          Voltage DC          0 - 1000 V
          Voltage DC Ratio    0 - Infinite
          Current AC          0 - 3 A
          Current DC          0 - 3 A
          2-wire Resistance   0 - 100M OHMs
          4-wire Resistance   0 - 100M OHMs
          Frequency           3 - 300k   Hz
          Period              0.33 - 3.3æ sec
          
          Default Value: 0.0
          
          Notes:
          (1) If the input signal is greater than the present range can
          measure, the instrument will return a measurement of 9.9e+37 and
          generate an instrument error.
          

      resolution

          Variable Type       ViInt16

          Resolution is expressed in terms of number of digits the instrument
          can measure or display. You can set the resolution to 4, 5, or 6 full
          digits, plus a 1/2 digit (leftmost digit on the display) which can
          only be a "0" or "1". To increase measurement accuracy and improve
          noise rejection, select 6 1/2 digits. To increase measurement speed,
          select 4 1/2 digits.
          
          Valid Range:
          0 = 4 1/2 digits
          1 = 5 1/2 digits (Default)
          2 = 6 1/2 digits
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Function) out of range.
          BFFC0003  Parameter 3 (Auto Range) out of range.
          BFFC0004  Parameter 4 (Range) out of range.
          BFFC0005  Parameter 5 (Resolution) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confAperTime

      ViStatus hp34401a_confAperTime (ViSession instrumentHandle, ViInt16 function,
                                      ViReal64 apertureTime);

  Purpose

      Configures the aperture time for frequency and period measurements.
      Aperture time for frequency and period is analogous to integration time
      for DC and resistance measurements.

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      function

          Variable Type       ViInt16

          Specifies the measurement function for which the aperture time will
          be configured.
          
          Valid Range:
          7 - Frequency (Default)
          8 - Period
          
          
          

      apertureTime

          Variable Type       ViReal64

          Configures the aperture time.
          
          Valid Range:
           10.0e-3 -  10 msec
          100.0e-3 - 100 msec (Default)
            1.0e+0 -   1 sec

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Measurement Function) out of range.
          BFFC0003  Parameter 3 (Aperture Time) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confDbMeas

      ViStatus hp34401a_confDbMeas (ViSession instrumentHandle, ViReal64 dBReference);

  Purpose

      Each dB measurement is the difference between a stored relative value and
      the input signal converted to dBm.
      dB = reading in dBm - dB relative value
      
      Notes
      (1) This operation applies to DC voltage and AC voltage measurements
      only.
      
      (2) The db reference value is cleared when you change measurement
      functions, turn dB off, turn off the power, or perform a reset.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      dBReference

          Variable Type       ViReal64

          Sets the dB Reference value.
          
          Valid Range: 0.0 to +- 200.0 dBm
          
          Default Value: 0.0

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (dB Reference) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confDbmMeas

      ViStatus hp34401a_confDbmMeas (ViSession instrumentHandle, ViInt16 dBmReference);

  Purpose

      The dBm operation calculates the power delivered to a resistance
      referenced to 1 milliwatt.
      dBm = 10 * Log(reading^2/reference resistance/1mW)
      
      Notes
      (1) This operation applies to DC voltage and AC voltage measurements
      only.
      
      (2) The reference resistance is stored in non-volatile memory, and does
      not change when power has been off or after a reset.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      dBmReference

          Variable Type       ViInt16

          Control Name:  dBm Reference Resistance
          
          Description:   Sets the dBm Reference value.
          
          Valid Range:
          50.0   -   50
          75.0   -   75
          93.0   -   93
          110.0  -  110
          124.0  -  124
          125.0  -  125
          135.0  -  135
          150.0  -  150
          250.0  -  250
          300.0  -  300
          500.0  -  500
          600.0  -  600 (Default)
          800.0  -  800
          900.0  -  900
          1000.0 - 1000
          1200.0 - 1200
          8000.0 - 8000 ohms
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (dBm Reference) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confIntegratTime

      ViStatus hp34401a_confIntegratTime (ViSession instrumentHandle,
                                          ViInt16 function, ViReal64 integrationTime);

  Purpose

      Integration time is the period of time the instrument's A/D converter
      samples the input signal for a measurement. Integration time affects the
      measurement resolution and
      measurement speed. For better resolution, use a longer integration time.
      For faster measurements use
      a shorter integration time.
      
      Note: Applies to all measurement functions except AC voltage, AC current,
      frequency, and period. The integration time for the math operations
      (null, min-max, dB,dBm, limit test) is the same as the integration time
      for the measurement function in use.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      function

          Variable Type       ViInt16

          Specifies the measurement function for which the integration time
          will be configured.
          
          Valid Range:
          1 = Voltage DC (Default)
          4 = Current DC
          5 = 2-wire Resistance
          6 = 4-wire Resistance
          
          
          

      integrationTime

          Variable Type       ViReal64

          Sets the integration time in Number of Power Line Cycles (NPLCs).
          
          Valid Range:
          0.02  - 0.02 PLCs
          0.2   - 0.2 PLCs
          1.0   - 1 PLC
          10.0  - 10 PLC  (Default)
          100.0 - 100 PLC
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Function) out of range.
          BFFC0003  Parameter 3 (Integration Time) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confLimitTest

      ViStatus hp34401a_confLimitTest (ViSession instrumentHandle, ViReal64 highLimit,
                                       ViReal64 lowLimit);

  Purpose

      The limit test operation enables you to perform pass/fail testing to
      upper and lower limits that you specify.
      
      Note
      (1) This operation applies to all measurement functions, except
      continuity and diode tests.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      highLimit

          Variable Type       ViReal64

          Sets the upper test limit.
          
          Valid Range:
          0.0 to +- 120% of the highest range for the present function.
          
          Default Value: 0.0
          

      lowLimit

          Variable Type       ViReal64

          Sets the lower test limit.
          
          Valid Range:
          0.0 to +- 120% of the highest range for the present function.
          
          Default Value: 0.0
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confMisc

      ViStatus hp34401a_confMisc (ViSession instrumentHandle, ViInt16 autozero,
                                  ViReal64 detectorBandwidth, ViBoolean autoImpedance);

  Purpose

      Configure input resistance, detector bandwidth and autozero.
      
      - Configures the input resistance of the instrument for noise reduction
      and loading. Normally, the input resistance is fixed at 10 Mohm for all
      DC voltage ranges to minimize noise pickup. To reduce the effects of
      measurement loading errors, the user can set input resistance to greater
      than 10 Gohm for the 100 mV DC, 1 V DC, and 10 V DC ranges.
      
      Notes:
      Applies to DC voltage measurements and is disabled for all other
      functions.
      
      (1) Configure detector bandwidth which enable the user to either optimize
      low frequency accuracy or achieve faster AC settling times.
      
      Applies to AC voltage and AC current measurements only.
      
      (2) Configure autozero. When autozero is enabled, the instrument
      internally disconnects the input signal following every measurement, and
      takes a zero reading. It then subtracts the zero reading from the
      preceding reading.
      This prevents offset voltages present on the instrument input circuitry
      from affecting measurement accuracy.
      
      When autozero is disabled, the instrument takes one zero reading and
      subtracts it from all subsequent measurements. It takes a new zero
      reading each time you change the function, range, or integration time.
      
      (3)Applies to DC voltage, DC current, and resistance measurements only.
      
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      autozero

          Variable Type       ViInt16

          Enables/Disables Autozero If Once is selected, a zero reading is
          immediately taken, then autozero is disabled.
          
          Valid Range:
          0 - Off
          1 - On (Default)
          2 - Once
          
          

      detectorBandwidth

          Variable Type       ViReal64

          Selects the AC filter. Selection should be based on the lowest
          frequency expected.
          
          Valid Range:
          3.0   - 3 Hz = Slow
          20.0  - 20 Hz = Medium (Default)
          200.0 - 200 Hz = Fast
          
          

      autoImpedance

          Variable Type       ViBoolean

          Enables or disables automatic  input impedance for DC voltage
          measurements. With Auto Impedance disabled, the instrument maintains
          its input impedance of 10 Mê for all DC voltage ranges. With Auto
          Impedance enabled, the input impedance is set to > 10 Gê for the
          three lowest DC voltage ranges (100 mV, 1 V, and 10 V) and 10 Mê for
          the other ranges (100 V and 1000 V).
          
          Valid Range:
          VI_OFF (0) - Disabled
          VI_ON  (1) - Enabled (Default)
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Auto Zero) out of range.
          BFFC0003  Parameter 3 (Detector Bandwidth) out of range.
          BFFC0004  Parameter 4 (Auto Impedance) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confNull

      ViStatus hp34401a_confNull (ViSession instrumentHandle, ViReal64 nullValue);

  Purpose

      When making null measurements, also called relative, each reading is the
      difference between a stored null value and the input signal. One possible
      application is in making more accurate two-wire resistance measurements
      by nulling the test lead resistance.
      RESULT = reading - null value
      
      Notes:
      (1) This operation applies to all measurement functions, except
      continuity and diode test.
      
      (2) The null register is cleared when you change measurement functions,
      turn null off, turn off the power, or perform a reset.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      nullValue

          Variable Type       ViReal64

          xSets the null value.
          
          Valid Range:
          0.0 to +- 120% of the highest range of the present function.
          
          Default Value: 0.0

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_confTrig

      ViStatus hp34401a_confTrig (ViSession instrumentHandle, ViInt16 triggerSource,
                                  ViBoolean autoTriggerDelay, ViReal64 triggerDelay,
                                  ViInt32 triggerCount, ViInt32 sampleCount);

  Purpose

      Configures the parameters of the Trigger Subsystem.
      If the functions contained in this driver are being used to initiate and
      return measurements, then the maximum number of readings which can be
      taken is 512. Therefore; the trigger count
      times the sample count must be 512.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      triggerSource

          Variable Type       ViInt16

          Configures the selected source as the trigger source.
          
          Valid Range:
          0 - Internal  (Default)
          1 - External
          2 - Software
          
          Notes:
          (1): If Internal is selected, trigger conditions are always true.
          This is the method used for the high-level configure functions.
          
          (2): If External is selected, the multimeter's "EXT TRIG" connector
          is the trig source. If Software is selected, the Execute Software
          Trigger function will trigger the instrument.
          
          
          

      autoTriggerDelay

          Variable Type       ViBoolean

          Enables/Disables automatic trigger delay. If disabled, the user must
          input a delay value which will be the delay between receipt of
          trigger and the start of the measurement. If enabled, an internal
          delay is used. The internal delay is dependent on the settling time
          of the instrument for the particular settings.
          
          Valid Range:
          VI_OFF (0) - Off
          VI_ON  (1) - On (Default)
          
          

      triggerDelay

          Variable Type       ViReal64

          If auto delay is disabled, then this value will be the delay between
          receipt of trigger and the actual measurement.  If auto delay is
          enabled, then this value will be ignored.
          
          Valid Range: 0.0 - 3600.0 secs
          
          Default Value: 0.000001
          

      triggerCount

          Variable Type       ViInt32

          Sets the number of triggers which will occur before the multimeter
          returns to its idle state.
          
          Valid Range: 1 - 50000
          
          Default Value: 1
          
          

      sampleCount

          Variable Type       ViInt32

          Configures the number of samples taken for each trigger received.
          
          Valid Range: 1 - 50,000
          
          Default Value: 1
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Trigger Source) out of range.
          BFFC0003  Parameter 3 (Auto Trigger Delay) out of range.
          BFFC0004  Parameter 4 (Trigger Delay) out of range.
          BFFC0005  Parameter 5 (Trigger Count) out of range.
          BFFC0006  Parameter 6 (Sample Count) out of range.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_display

      ViStatus hp34401a_display (ViSession instrumentHandle, ViBoolean displayState,
                                 ViChar displayMessage[], ViBoolean clearMessage);

  Purpose

      Configures the front panel display of the instrument.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      displayState

          Variable Type       ViBoolean

          Turns on/off the front panel display of the instrument. This may be
          useful to speed up measurement rates.
          If off is selected, readings are not sent to the display and all
          display annunciators except ERROR and Shift are inactive. Front panel
          operation is otherwise unaffected by turning off the display.
          
          Valid Range:
          VI_OFF (0) - Off
          VI_ON  (1) - On (Default)
          
          

      displayMessage

          Variable Type       ViChar[]

          If Clear Message is set to No, then this string is sent to the front
          panel of the instrument.
          
          Valid Range: Up to 12 Alpha-Numeric Characters
          
          Default Value: "Hello"
          
          Notes:
          (1) When a message is displayed, readings are not sent to the
          display.
          
          (2) A Message can be displayed even when the display state is off.
          
          

      clearMessage

          Variable Type       ViBoolean

          If Yes is selected, this control clears the message from the front
          panel of the display and disables the present message from being
          sent.
          
          Valid Range:
          VI_OFF (0) - No
          VI_ON  (1) - Yes (Default)
          
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0002  Parameter 2 (Display State) out of range
          BFFF0003  Parameter 3 (Display Message) too long
          BFFF0004  Parameter 4 (Clear Message) out of range
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_errorMessage

      ViStatus hp34401a_errorMessage (ViSession instrumentHandle, ViStatus errorCode,
                                      ViChar errorMessage[]);

  Purpose

      This function takes the Status Code returned by the instrument driver
      functions, interprets it and returns it as a user readable string.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  VI_NULL

      errorCode

          Variable Type       ViStatus

          This control accepts the Status Code returned from the instrument
          driver functions.
          
          Default Value:
          0 - VI_SUCCESS

      errorMessage

          Variable Type       ViChar[]

          This control returns the interpreted Status Code as a user readable
          message string.
          
          Notes:
          
          (1) The array must contain at least 256 elements ViChar[256].

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          3FFF0085 VI_WARN_UNKNOWN_STATUS
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_errorQuery

      ViStatus hp34401a_errorQuery (ViSession instrumentHandle, ViInt32 *errorCode,
                                    ViChar errorMessage[]);

  Purpose

      This function reads an error code from the instrument's error queue.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      errorCode

          Variable Type       ViInt32 (passed by reference)

          This control returns the error code read from the instrument's error
          queue.
          

      errorMessage

          Variable Type       ViChar[]

          This control returns the error message string read from the
          instrument's error message queue.
          
          Notes:
          
          (1) The array must contain at least 256 elements ViChar[256].

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_fetchMeas

      ViStatus hp34401a_fetchMeas (ViSession instrumentHandle,
                                   ViInt16 *ofMeasurements, ViReal64 measurements[],
                                   ViInt16 timeOutmsec);

  Purpose

      If the Wait For Trigger function is used to initiate measurements then
      this function must be used to retrieve the measurements.
      
      Note :
      Upon completion of this function, time out is reset to 10 seconds.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      ofMeasurements

          Variable Type       ViInt16 (passed by reference)

          Returns the number of measurements taken.
          # of Measurements = Sample Cnt * Trigger Cnt
          
          Default: None

      measurements

          Variable Type       ViReal64[]

          Returns an array of measurements.The trigger and sample count can be
          determined using the Check Trigger function.
          
          Units:
          Voltage - Volts
          Resistance - Ohms
          Current - Amps
          Frequency - Hertz
          Period - Seconds
          
          

      timeOutmsec

          Variable Type       ViInt16

          Sets the maximum amount of time (in milli seconds) that the
          controller will wait for the instrument to respond before it times
          out.
          
          Valid Range
          0 - Disable
          1 - 1000000 (1000 sec)
          
          Default Value 10000 (10 sec)
          
          Notes:
          (1) A value of zero (0) disables the time-out.  Therefore if zero is
          selected the function will never time-out, and never return if the
          measurements are not completed.
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Time Out value) out of range.
          BFFC0803  Error Scanning Response.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF0002  Time outoff range.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_init

      ViStatus hp34401a_init (ViRsrc resourceName, ViBoolean IDQuery,
                              ViBoolean resetDevice, ViSession *instrumentHandle);

  Purpose

      This function performs the following initialization actions:
      
      - Opens a session to the Default Resource Manager resource and a session
      to the specified device using the interface and address specified in the
      Resource_Name control.
      
      - Performs an identification query on the Instrument.
      
      - Resets the instrument to a known state.
      
      - Sends initialization commands to the instrument that set any necessary
      programmatic variables such as Headers Off, Short Command form, and Data
      Transfer Binary to the state necessary for the operation of the
      instrument driver.
      
      - Returns an Instrument Handle which is used to differentiate between
      different sessions of this instrument driver.
      
      - Each time this function is invoked a Unique Session is opened.  It is
      possible to have more than one session open for the same resource.
      

  Parameter List

      resourceName

          Variable Type       ViRsrc

          This control specifies the interface and address of the device that
          is to be initialized (Instrument Descriptor). The exact grammar to be
          used in this control is shown in the note below.
          
          Default Value:  "GPIB::22"
          
          Notes:
          
          (1) Based on the Instrument Descriptor, this operation establishes a
          communication session with a device.  The grammar for the Instrument
          Descriptor is shown below.  Optional parameters are shown in square
          brackets ([]).
          
          Interface   Grammar
          ------------------------------------------------------
          GPIB        GPIB[board]::primary address[::secondary address]
                      [::INSTR]
          
          The GPIB keyword is used with GPIB instruments.
          
          The default value for optional parameters are shown below.
          
          Optional Parameter          Default Value
          -----------------------------------------
          board                       0
          secondary address           none - 31
          

      IDQuery

          Variable Type       ViBoolean

          This control specifies if an ID Query is sent to the instrument
          during the initialization procedure.
          
          Valid Range:
          VI_OFF (0) - Skip Query
          VI_ON  (1) - Do Query (Default Value)
          
          Notes:
          
          (1) Under normal circumstances the ID Query ensures that the
          instrument initialized is the type supported by this driver. However
          circumstances may arise where it is undesirable to send an ID Query
          to the instrument.  In those cases; set this control to "Skip Query"
          and this function will initialize the selected interface, without
          doing an ID Query.

      resetDevice

          Variable Type       ViBoolean

          This control specifies if the instrument is to be reset to its
          power-on settings during the initialization procedure.
          
          Valid Range:
          VI_OFF (0) - Don't Reset
          VI_ON  (1) - Reset Device (Default Value)
          
          Notes:
          
          (1) If you do not want the instrument reset. Set this control to
          "Don't Reset" while initializing the instrument.

      instrumentHandle

          Variable Type       ViSession (passed by reference)

          This control returns an Instrument Handle that is used in all
          subsequent function calls to differentiate between different sessions
          of this instrument driver.
          
          Notes:
          
          (1) Each time this function is invoked a Unique Session is opened.
          It is possible to have more than one session open for the same
          resource.
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (ID Query) out of range.
          BFFC0003  Parameter 3 (Reset Device) out of range.
          BFFC0011  Instrument returned invalid response to ID Query
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_multiMeas

      ViStatus hp34401a_multiMeas (ViSession instrumentHandle, ViInt16 timeOutmsec,
                                   ViInt16 *ofMeasurements, ViReal64 measurements[]);

  Purpose

      Puts the instrument into the wait-for-trigger state and waits
      until all triggers have been received and all samples taken, then returns
      the readings.This function uses synchronous
      techniques to determine when the measurements are complete. Using this
      method the function will wait while the measurements are in progress. The
      advantage of this method is that the user can use one function to enter
      the wait-for-trigger state and also return the readings. The disadvantage
      is that no other operation can be performed while measurements are in
      progress.
      
      Note: Upon completion of this function, timeout is reset to 10 seconds.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      timeOutmsec

          Variable Type       ViInt16

          Sets the maximum amount of time (in milli seconds) that the
          controller will wait for the instrument to respond before it times
          out.
          
          Valid Range
          0 - Disable
          1 - 1000000 (1000 sec)
          
          Default Value 10000 (10 sec)
          
          Notes:
          (1) A value of zero (0) disables the time-out.  Therefore if zero is
          selected the function will not time-out and return if the
          measurements are not completed.

      ofMeasurements

          Variable Type       ViInt16 (passed by reference)

          Returns the number of measurements taken.
          # of Measurements = Sample Cnt * Trigger Cnt
          
          Default Value:
          0

      measurements

          Variable Type       ViReal64[]

          Returns an array of measurements.(Dimension >= sample count * trigger
          count) The trigger and sample count can be determined using the Check
          Trigger function.
          
          Units:
          Voltage - Volts
          Resistance - Ohms
          Current - Amps
          Frequency - Hertz
          Period - Seconds
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0002  Parameter 2 (Time Out value) out of range.
          BFFC0803  Error Scanning Response.
          
          BFFF0000  Miscellaneous or system error occurred.
          
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_readInstrData

      ViStatus hp34401a_readInstrData (ViSession instrumentHandle,
                                       ViInt16 numberBytesToRead, ViChar readBuffer[],
                                       ViInt32 *numBytesRead);

  Purpose

      This function reads data from the instrument's output buffer and returns
      it to the specified variable in memory.
      
      Notes:
      
      (1) Because the instrument may return both numeric and text data in
      response to queries this function returns the data in string format.
      
      (2) If valid data is not available at the instrument's output buffer when
      this function is called the instrument will hang up and the function will
      not return until it times out.  If the time-out is disabled this function
      will hang indefinitely and it may be necessary to reboot the computer to
      break out.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      numberBytesToRead

          Variable Type       ViInt16

          The number of bytes specified by this control should be greater than
          or equal to the number of bytes which are to be read from the
          instrument. If the actual number of bytes to be read is greater than
          the number this control specifies then multiple reads will be
          required to empty the instrument's output buffer.
          
          If the instrument's output buffer is not emptied the instrument may
          return invalid data when future reads are performed.
          
          Default Value:  50 (See NOTE 2)
          
          Notes:
          
          (1) If NO DATA is available at the instrument's output buffer when
          this function is called the instrument will hang up and the function
          will not return until it times out.  If the time-out is disabled,
          this function will hang indefinitely and it may be necessary to
          reboot the computer.
          
          (2) If the number of bytes expected is greater than 50 the value of
          this control may be increased. If the actual number of bytes read is
          larger than the declared size of the read buffer a run-time error
          will be generated.
          

      readBuffer

          Variable Type       ViChar[]

          The incoming data from the instrument is placed into this variable.
          
          Notes:
          
          (1) Because the instrument may return both numeric and text data in
          response to queries this function returns the data in string format.
          
          (2) This function does not overwrite any old data left in the string
          variable from the last time the function was called. String data in
          LabWindows/CVI is terminated with an ASCII null(0x0) and string
          manipulation functions will only recognize data before the ASCII
          null.
          
          (3) The declared size of the string variable must be greater than the
          actual number of bytes read from the instrument if it is not a
          run-time error will be generated.
          

      numBytesRead

          Variable Type       ViInt32 (passed by reference)

          This variable contains the actual number of bytes read from the
          instrument. This is the value which is returned by the read function.
          
          Notes:
          
          (1) If the actual number of bytes read is less than the number of
          bytes specified in the Number Bytes To Read control then the output
          buffer has probably been emptied. If the read function fails and the
          number of bytes read is 0, the most probable cause for the failure is
          there was no data available at the instrument's output buffer.

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_reset

      ViStatus hp34401a_reset (ViSession instrumentHandle);

  Purpose

      This function resets the instrument to a known state and sends
      initialization commands to the instrument that set any necessary
      programmatic variables such as Headers Off, Short Command form, and Data
      Transfer Binary to the state necessary for the operation of the
      instrument driver.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_revisionQuery

      ViStatus hp34401a_revisionQuery (ViSession instrumentHandle,
                                       ViChar instrumentDriverRevision[],
                                       ViChar firmwareRevision[]);

  Purpose

      This function returns the revision numbers of the instrument driver and
      instrument firmware, and tells the user what firmware the driver is
      compatible with; this instrument driver's Revision Number is "Rev 1.0b,
      9/95, CVI 3.1" and is compatible with Instrument Firmware Revision
      "6-4-1".
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      instrumentDriverRevision

          Variable Type       ViChar[]

          This control returns the Instrument Driver Software Revision.
          
          Notes:
          
          (1) The array must contain at least 256 elements ViChar[256].

      firmwareRevision

          Variable Type       ViChar[]

          This control returns the Instrument Firmware Revision.
          
          Notes:
          
          (1) The array must contain at least 256 elements ViChar[256].

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_selfTest

      ViStatus hp34401a_selfTest (ViSession instrumentHandle, ViInt16 *selfTestResult,
                                  ViChar selfTestMessage[]);

  Purpose

      This function runs the instrument's self test routine and returns the
      test result.
      
      Notes:
      (1) The Self-Test routine will take approximately 7 seconds.
      
      (2) This instrument does not return a self-test result string so the
      numerical result is copied into the string parameter and returned.

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      selfTestResult

          Variable Type       ViInt16 (passed by reference)

          This control contains the value returned from the instrument self
          test.  Zero means success.  One means the self-test failed.  For any
          other code, see the device's operator's manual.
          

      selfTestMessage

          Variable Type       ViChar[]

          This control contains the string returned from the self test. See the
          device's operation manual for an explanation of the string's
          contents.
          
          Notes:
          
          (1) The array must contain at least 256 elements ViChar[256].
          
          (2) This instrument does not return a self-test result string so the
          numerical result is copied into the string parameter and returned.

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_singleMeas

      ViStatus hp34401a_singleMeas (ViSession instrumentHandle, ViReal64 *measurement);

  Purpose

      Puts the instrument into the wait-for-trigger state and waits until the
      trigger has been received, then returns a single reading. This function
      uses synchronous techniques to determine when the measurement is
      complete. Using this method the function will wait while the measurement
      is in progress. The advantage of this method is that the user can use one
      function to enter the wait-for-trigger state and also return the reading.
      The disadvantage is that no other operation can be performed while
      measurement is in progress.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      measurement

          Variable Type       ViReal64 (passed by reference)

          Triggers and returns a measurement.
          
          Units:
          Voltage - Volts
          Resistance - Ohms
          Current - Amps
          Frequency - Hertz
          Period - Seconds
          
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFC0803  Error Scanning Response.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_softTrig

      ViStatus hp34401a_softTrig (ViSession instrumentHandle);

  Purpose

      When the instrument trigger source is configured for software trigger,
      this panel triggers the instrument once.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_waitForTrigger

      ViStatus hp34401a_waitForTrigger (ViSession instrumentHandle);

  Purpose

      Puts the instrument into the wait-for-trigger state. The user must use
      the Fetch Measurements function to return the readings. This method of
      taking measurements uses asynchronous techniques to determine when the
      measurements are  complete. Using this method the measurements are
      initiated by this function, but the readings must be returned upon
      completion by the Fetch Measurements function.The advantage of this
      method is that while the measurements are being taken, the user can
      perform other tasks, such as triggering the instrument via software
      trigger or the user can be sending commands to other instruments. The
      disadvantage of this method is that the user is burdened with determining
      when the measurements are complete.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
________________________________________________________________________________

  hp34401a_writeInstrData

      ViStatus hp34401a_writeInstrData (ViSession instrumentHandle,
                                        ViString writeBuffer);

  Purpose

      This function writes commands and queries to the instrument to modify
      parameters and query device settings.
      

  Parameter List

      instrumentHandle

          Variable Type       ViSession

          This control accepts the Instrument Handle returned by the Initialize
          function to select the desired instrument driver session.
          
          Default Value:  None

      writeBuffer

          Variable Type       ViString

          The user can use this control to send common commands and queries to
          the instrument. This control can also be used to write any valid
          command to the instrument.
          
          Default Value:  "*RST"
          
          Notes:
          
          (1) The command or query to be sent to the instrument may be a
          literal enclosed in double quotes i.e. "*RST" or may be contained in
          a variable of type string.
          

  Return Value

          This control contains the status code returned by the function call.
          
          Status Codes:
          
          Status    Description
          -------------------------------------------------
                 0  No error (the call was successful).
          
          3FFF0005  The specified termination character was read.
          3FFF0006  The specified number of bytes was read.
          
          BFFF0000  Miscellaneous or system error occurred.
          BFFF000E  Invalid session handle.
          BFFF0015  Timeout occurred before operation could complete.
          BFFF0034  Violation of raw write protocol occurred.
          BFFF0035  Violation of raw read protocol occurred.
          BFFF0036  Device reported an output protocol error.
          BFFF0037  Device reported an input protocol error.
          BFFF0038  Bus error occurred during transfer.
          BFFF003A  Invalid setup (attributes are not consistent).
          BFFF005F  No listeners condition was detected.
          BFFF0060  This interface is not the controller in charge.
          BFFF0067  Operation is not supported on this session.
          
