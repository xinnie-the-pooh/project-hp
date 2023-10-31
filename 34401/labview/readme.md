Agilent 34401 Instrument Driver Readme
To rate this driver, go to the driver download page on the Instrument Driver Network.

1. Overview
Instrument Driver Technology:
LabVIEW Plug and Play (project-style)
Manufacturer:
Agilent Technologies
Supported Language(s):
LabVIEW 8.0
Supported Model(s):
Agilent Technologies 34401A, 34410A, 34411A, L4411A
Model(s) Tested:
Agilent Technologies 34401A, 34410A, 34411A
Interface(s):
GPIB, Serial (34401A); GPIB, USB, Ethernet (34410A, 34411A, L4411A)
Firmware Revision Tested:
8.5.2, 11.5.2, 2.03-2.03-0.09-43-6
Certified:
Yes
NI Supported:
Yes
Source Code Available:
Yes
Driver Revision:
6.4.3
Original Release Date:
6/29/2005
Current Revision Date:
1/2/2014
2. Required Software
Some software components need to be installed before using this instrument driver. The minimum versions of these components are listed below, and can be downloaded from the Download Site.

VISA 5.0 or later
Refer to the LabVIEW Help for more information about software requirements. You access the LabVIEW Help by selecting Help»LabVIEW Help.

3. Known Issues
To report issues or provide feedback about this instrument driver, please contact technical support.

In older firmware, the instruments did not support a VXI-11 abort for Ethernet. This type of abort is sent by NI-VISA when the Abort button is selected in LabVIEW. If the abort is not acknowledged by the instrument, the VI will appear to hang. It is always best to terminate a VI using a stop button provided in the user interface.
In the 34410, using a manual trigger delay with a software trigger may take longer than the configured timing.
On the 34410 and 34411, when software triggering is used for taking multiple samples, a manual trigger delay is set, and a sample time interval is used, a timing violation error will occur.
Buffer overflow errors can occur if data is not read from the instrument's memory buffer fast enough. This issue can be resolved by increasing the trigger delay or sample interval to reduce the measurement speed, or by using a different interface bus.
Using the 34401 on an operating system that does not support DTR/DSR flow control (ex. Linux) requires the user to modify the connection from the PC to the instrument. Basically, this requires the user to tie a pin to logic true and lower the baud rate. See the 34401 manual for more details.
4. Revision History
The latest version of this and other LabVIEW and LabWindows/CVI instrument drivers can be downloaded at the Instrument Driver Network.
REV 5.0.0, 6/29/05
Modified by: Rob Hammond, NI
Created new driver from hp34401a version 4.4.5 to be shipped with LabVIEW 8.0.

REV 5.0.1, 10/28/05
Read (Math).vi - Added Error Query VI
Read (Math).vi, Configure Integration.vi, Configure Aperture.vi - Updated format string to include decimal point specifier (%.;)

REV 6.0.0, 5/09/06
Modified by: Michael Lin, NI
New VIs:
Configure Offset Compensation.vi
Configure Temperature.vi
Configure Temperature (RTD).vi
Configure Temperature (Thermistor).vi
Read (Transient).vi
Initiate Measurement.vi
Fetch Measurement.vi
Fetch Measurement (Fetch).vi
Fetch Measurement (Read).vi
Fetch Measurement (Fast Read).vi
Save-Recall Instrument Settings.vi
Query Questionable Data Register.vi
Agilent 34401 Read Transient Measurement.vi
Agilent 34401 Acquire and Chart - Pretriggered.vi
Agilent 34401 Acquire and Chart - External Triggered.vi
Agilent 34401 Read Temperature Measurement (RTD).vi
Modified VIs:
Initialize.vi: updated VI to support the Agilent 34410/34411.
Configure Measurement.vi: updated VI to include temperature and capacitance configurations; expanded ranges for the Agilent 34410/34411; added custom error handling.
Configure Aperture.vi: updated VI to include temperature configuration for the Agilent 34410/34411; the VI will now provide a custom error if an invalid selection is made.
Configure Integration.vi: updated VI to include temperature configuration; expanded ranges for the Agilent 34410/34411; the VI will now provide an error if an invalid selection is made.
Configure Math.vi: now stores math buffer settings to extended user data.
Configure Multipoint.vi: updated VI to include sample interval option for the Agilent 34410/34411; added pretrigger sample option for the Agilent 34411.
Configure Trigger.vi: updated VI to include options to set trigger level and trigger slope for the Agilent 34410/34411; added custom error handling; now stores trigger source settings to extended user data.
Read.vi: added Read (Transient).vi to polymorphic VI.
Read (Single Point).vi: updated to use the Initiate Measurement and Fetch Measurement VIs.
Read (Multiple Points).vi: updated to use the Initiate Measurement and Fetch Measurement VIs.
Read (Math).vi: updated VI to include standard deviation and peak-to-peak outputs for the Agilent 34410/34411; updated VI to use the Initiate Measurement and Fetch Measurement VIs
System Options.vi: added support to display custom message text to the instrument front panel display.
Control Mode.vi: now only supports serial interface.
Error Query.vi: added logic to query for errors in the event of max time error.
Close.vi: added Query Questionable Data.vi to check the questionable data register.
VI Tree.vi: updated Tree to include new VIs and exclude obsolete VIs.
Agilent 34401 Acquire and Graph - SW Triggered.vi: added enable auto range and manual range controls; added stop button to allow user to halt triggering.
Agilent 34401 Acquire and Chart - Triggered.vi: added enable auto range and manual range controls; added stop button to allow user to halt execution.
Obsoleted VIs:
Initiate.vi
Initiate (Internal Buffer).vi
Initiate (Output Buffer).vi
Fetch.vi
Fetch (Internal Buffer).vi
Fetch (Output Buffer).vi

REV 6.1.0, 6/21/06
Modified by: Jim Piotrowski, NI
New VIs:
Query Questionable Data Register.vi: moved from Private to Public\Data\Low Level and is now available to users.
Read STB.vi: private VI to workaround issue with USB interface not working with VISA Read STB primitive.
Modified VIs:
Error Query.vi: now calls new private Read STB.vi to workaround issue with USB.
Read (Single).vi: calls Query Questionable Data Register to check for questionable data warnings from instrument
Read (Multiple).vi: calls Query Questionable Data Register to check for questionable data warnings from instrument
Read (Transient).vi: calls Query Questionable Data Register to check for questionable data warnings from instrument
Read (Math).vi: calls Query Questionable Data Register to check for questionable data warnings from instrument
Default Instrument Setup.vi: updated to enable appropriate Questionable Data Register flags.
Configure Multipoint.vi: Updated format string to include decimal point specifier (%.;)
Initialize.vi: added logic to set Flow Control to None in event of an error setting it to DTR/DSR; this is needed for some operating systems (ex. Linux).

REV 6.1.1, 9/4/06
Modified by: Jim Piotrowski, National Instruments
Extended User Data.vi: fixed so that errors going into the VI aren't overwritten

REV 6.2, 4/1/07
Modified by: NI
Initialize.vi: added Error Query to the Default Instrument Setup case when Reset is disabled. Updated ID Query logic to support L4411 model.
REV 6.3, 6/20/07
Modified by: NI
Revision Query.vi updated to include a workaround for the issue with Revision Query VI not working with the LabVIEW Run-Time Engine.

REV 6.4, 3/18/08
Modified by: Nathan Tacha, NI
Initialize.vi: removed "Mark" and "Space" parity options from the serial configuration settings

REV 6.4.1, 4/02/08
Modified by: Nathan Tacha, NI
Read Single Measurement.vi & Read Multiple Measurements.vi: removed "Mark" and "Space" parity options from the serial configuration settings

REV 6.4.2, 11/10/10
Modified by: NI
Added example Read Math Measurement

REV 6.4.3, 1/2/2014
Modified by: Stephen Schwahn, National Instruments
Configure Measurement.vi: Multiplied all numbers in the inner case statement by a factor of 10 to fix display issue
Configure Multipoint.vi: Added documentation note about model support regarding pretrigger and multitrigger settings.
Control Mode.vi: Added documentation note about a known hardware issue regarding Remote with Lock to remote transitions.
All Examples had controls regenerated to update documentation/consistency and all Text Ring/Boolean constants that are part of driver has labels showing and digital displays removed.
