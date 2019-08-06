
                    CoolTerm

       Copyright (c) 2007-2019 Roger Meier,
              All rights reserved

         http://freeware.the-meiers.org



WHAT IS IT?
===========

CoolTerm is an easy-to-use terminal for communication with hardware connected to serial ports.

CoolTerm is a simple serial port terminal application (no terminal emulation) that is geared towards hobbyists and professionals with a need to exchange data with hardware connected to serial ports such as servo controllers, robotic kits, GPS receivers, microcontrollers, etc.
The features of CoolTerm include:
- Capability of multiple concurrent connections if multiple serial ports are available.
- Display of received data in plain text or hexadecimal format.
- Sending data via keypresses as well as a "Send String" dialog that supports data entry in plain text or hexadecimal format.
- Sending data via copy-paste of text into the terminal window.
- Sending of text files.
- Capability of capturing received data to text files.
- Local echo of transmitted data.
- Local echo of received data (loop back to sender).
- Hardware (CTS, DTR) and software flow control (XON).
- Visual line status indicators.
- Capability of manually toggling line states of certain handshaking signals when hardware flow control is disabled.
- Configurable character and line delays.
- Capability of saving and retrieving connection options.
- and more...



INSTALLATION
============
CoolTerm comes without an installer and can be placed anywhere on the hard-drive as long as the correct folder structure is maintained. I.e. for the Windows version the "CoolTerm Libs" folder must reside in the same location as the "CoolTerm.exe" executable.


SYSTEM REQUREMENTS
==================
Please refer to the platform specific "*** System Requirements.txt" document included with the download


HOW TO USE IT
=============
Please refer to the built-in help.



VERSION HISTORY
===============
1.6.0: 05/19/2019 (exactly 10 years since the initial public release!)
-----------------

NEW/CHANGED FEATURES:
- Added "Open Recent" menu item. Recent items are saved between sessions.
- Added "Close All" menu to close all open window.
- Added capability to restore the previous sessions. If enabled via the Preferences, the current session is saved if CoolTerm is quit via File/Quit (macOS/Linux) or File/Exit (Windows). CoolTerm will attempt to restore all the open terminal windows from the previous session at the next start.
- Added context menu for Copy/Paste operations to plain text display.
- Replaced option to stop Autoscrolling with option to pause the display instead. When enabled, the display contents are not updated until pausing the display is disabled again. Opening and closing the port automatically un-pauses the display.
- Added baud rate selector in the connections to allow setting a custom baudrate. The custom baudrate can be saved as part of the connection settings.
- The font size for text input fields (line mode input field "Send String" input field) can now be set independently via the preferences.
- Added preferences option to automatically refresh the list of serial ports when opening the connection options.
- Added preferences option to check for development releases when checking for updates.
- [Mac] Added the following AppleScript commands:
       - WindowIDfromName(WindowName as string) as integer
       - SaveSetting(ID as integer, FilePath as String) as boolean
       - CoolTermVersion as string
       - RescanSerialPorts
       - SerialPortCount as integer
       - SerialPortName(SerialPortIndex as integer) as string
       - GetCurrentSerialPort(ID as integer) as integer
       - SetCurrentSerialPort(ID as integer, SerialPortIndex as integer) as boolean
       - GetParameter(ID as integer, ParameterName as string) as string
       - SetParameter(ID as integer, ParameterName as string, Value as string) as boolean
       - GetAllParameters(ID as integer) as string
- Added support for dark mode on platforms that support it (such as macOS Mojave).
- Supporting Raspberry Pi
- Default is now 64-bit for all platforms (except Raspberry Pi)

IMPROVEMENTS:
- File/Save menu item is now permanently enabled. Selecting File/Save when settings have not previously been saved will present the user with a "Save As..." dialog.
- Connection Settings saved as default no longer contain the selected serial port and window position. New windows using the default settings will select the first available port rather than trying to force a port that may or may not be available.
- The text and background color settings for the text display are now also applied ot the line mode input text field.

BUG FIXES AND STABILITY IMRPOVEMENTS:
- Fixed bug where the receive buffer size wouldn't be set upon loading of connection settings.
- Fixed bug that causes setting to not be properly loaded on Mac when starting CoolTerm for the command line with a settings file as argument or when starting CoolTerm by double-clicking a settings file or dragging it onto the CoolTerm icon.
- [Mac] Disabled splash window for macOS Sierra and newer



1.5.0: 01/07/2018

-----------------
NEW/CHANGED FEATURES:

- Added configuration option for software supported flow control.
- Added configuration option for blocking keystrokes while transmit data flow is halted.
- Added printing for plain text and hex views.
- Added proxy settings to preferences (for update check).
- Changed preferences window to multi-tab concept.
- Made formatting of captured hex data configurable.
- It is now possible to use the 'Wait for termination string' option when capturing in hex format as long as formatting of hex data is disabled.
- Added "Packet Delay" option, which allows inserting a delay after the transmission of each packet, the size of which can now be specified via the connection settings GUI.
- The "Line Delay" option now supports matching all of the specified delay characters in addition to matching any of them. This allows for entire strings to be specified as line delay characters.

IMPROVEMENTS:

- Changed text encoding in "Send String" window to use system default encoding.
- Improved GUI for flow control settings to prevent hardware and software flow control from being enabled at the same time.
- Enhanced the behavior of the TX LED. When flow control is enabled and transmission is halted by the remote target, the color of the TX LED is changed to red to indicate that no data is being sent (select platforms only).
- The reception of break signals or framing errors now flashes the RX LED red when "Ignore receive errors" is enabled (select platforms only).
- Changed code to prevent the transmit progress from being displayed when "loop back receive data" is enabled and larger amounts of data are being looped back.
- [Win/Linux] Changed behavior of modal windows such as connection options and send progress windows so that only the parent terminal window is blocked as opposed to all open windows.
- [Mac] Added the following ApplesScript command:
		LookAheadHex(ID as integer) as String
- [Mac] Removed the following AppleScript commands:
		Str2Hex(PlainStr as String) as String
		Hex2Str(HexStr as String) as String
- [Mac] Universal Builds for Mac are no longer supported.

BUG FIXES AND STABILITY IMRPOVEMENTS:

- [Mac] Disabled SmartQuotes, SmartDashes, and SmartTextReplacement in TextArea
- Added handling of OutOfMemoryExceptions in transmit thread
- revised code to exclude text input line used in "Line Mode" from text size changes.




1.4.7: 02/11/17
---------------
NEW/CHANGED FEATURES:
- Added option to specify a custom file name for auto capture files when "Append to auto capture file" is enabled.
- CoolTerm will now save default settings to the application data directory, regardless of where CoolTerm is installed.
These locations are as follows
          Mac: /Users/UserName/Library/Application Support/CoolTerm/
          Win: \Users\UserName\AppData\Roaming\CoolTerm\
          Linux: /home/UserName/CoolTerm/.
However, a default.stc file placed in the same location as the CoolTerm executable will take precedence over the one in the application data location. This is useful for portable installations of CoolTerm.
- baudrates.ini and ports.ini files can now also be placed in the application data directory (see platforms specific locations above). However, files placed in the same location as the CoolTerm executable will take precedence over the files placed in the application data directory. This is useful for portable installations of CoolTerm.
- Made text wrapping in plain text view a configurable option.
- Added option to format TAB separated data for the plain text display. If enabled, text will be aligned on a specified column width.
- Added option to handle a specified minimum number of consecutive received spaces for the ASCII display. If enabled, such occurrences will be replaced by a TAB character.
IMPROVEMENTS:
- Clicking 'Cancel' in the transmit progress window will now dismiss the window even if when transmission is halted by the target when flow control is enabled.
- NUL characters are now ignored in ASCII view mode if "Handle non-print characters" is disabled to prevent the ASCII viewer from behaving erratically on certain platforms.
- Changed code to optimize CPU consumption in plain text view mode.
- Changed the default name of new terminals from "CoolTerm" to "Untitled" to better conform with common practice.
- Changed Capture File Save dialog to use .txt as file extension by default.
- [Mac] Added code to prevent App Nap when CoolTerm is running in the background.
- [Mac] Changed encoding of strings returned by Apple Script from ASCII to the system default to ensure compatibility with the full 8-bit character set.
- [Mac] New AppleScript commands:
        - WriteHex(ID as integer, HexData as String)
	- ReadHex(ID as integer, NumChars as Integer) as String
	- ReadAllHex(ID as integer) as String
- [Mac] Deprecating the Str2Hex and Hex2Str AppleScript functions. Future versions of CoolTerm will not implement these functions anymore
- Added dialog to prompt for user's e-mail when sending crash reports.
BUG FIXES AND STABILITY IMRPOVEMENTS
- Changed code so that port enumeration continues if an exception occurs with a certain port during operation. This should allow all valid ports to be enumerated.
- improved code to properly handle multiple instances (Windows and Linux).
- improved code for line condensing in ASCII view mode
- improved code to properly handle initial instance when new connection settings are opened.
- Fixed bug that resets the formatting of the plain text view after clearing the data in the receive buffer.


1.4.6: 02/16/16
---------------
NEW/CHANGED FEATURES:
- Added the option to automatically start file capture upon loading connection settings.
- Added option to append new data to auto capture files.
- Added option to filter ANSI escape sequences. If this option is enabled, ANSI sequence characters will be filtered in ASCII view mode.
- Added preference option to enable condensing the line spaces in plain text view mode (not available in Universal Binary builds).
- [Win][Linux] Added code to ensure that only one instance of CoolTerm is running on the system at the same time
- Added code to ensure that a connection settings file can only be opened once.
- Added preference option to show or hide the toolbar.
- Added UTF-8 support for plain text view.
- Updated preferences dialog to display extended character set.
- [Win] Added support for AltGr key combinations on certain international keyboards.
- Added shortcut (Mac: CMD-I, Win/Linux: CTRL-I) to Connection/Options... menu.
- Changed relative timestamp format from HH:MM:SS:sss to HH:MM:SS.sss to be consistent with established timestamp conventions.
IMPROVEMENTS:
- Removed CTRL+Alt+S short cut for "File/Save as default" to avoid AltGr+S triggering the short cut.
- [Win][Linux] Changed code to use platform specific default text encoding for the plain text window to allow displaying bytes larger than 0x7f.
- UI Tweaks to harmonize the look of the GUI between platforms.
- Updated Help Text with instructions on how to remove the serial port name from settings files.
BUG FIXES AND STABILITY IMRPOVEMENTS
- [Linux] Updated AutoScroll code to behave the same as it does on Mac and Windows.
- Fixed bug that didn't properly update the text of the Connection/Connect_Disconnect menu when switching between terminal windows.
- [Mac] Fixed bug where the text encoding of strings returned from AppleScript commands was not defined.


1.4.5: 02/14/15
---------------
NEW/CHANGED FEATURES:
- Added new option to handle Form Feed (FF, ASCII code 12) characters. When enabled, the reception of a FF character will clear the receive buffer and thus clear the screen.
- Added new option to handle End Of Text (EOT, ASCII code 4) characters. Enabling this feature will prevent the display from updating until a EOT character is received, at which time the display is updated with the contents from the receive buffer.
- Added code to present the user with the option to select a serial port if a loaded settings file includes an empty string for the port name. This allows the creation of generic settings files. 
- [MAC] Additional retina support.
BUG FIXES AND STABILITY IMRPOVEMENTS
- Code improvement to avoid ThreadAccessingUIException

NOTE TO MAC USERS:
Version 1.4.x will be the last release of CoolTerm available as Universal Binary. Starting with version 1.5.x, CoolTerm will only be deployed for Intel based Macs.


1.4.4: 09/21/14
---------------
NEW/CHANGED FEATURES:
- Added feature that shows the path to the current capture file (if a capture is currently active) when the mouse is hovered over the serial port status label at the bottom left of the CoolTerm window.
- changed Enter key emulation settings to use popup menu and added the option use a custom sequence to emulate the enter key.
- Added additional font sizes to preferences dialog.
- Added option to reduce the terminal refresh rate to once per second in order to reduce the CPU load on systems where power consumption is critical.
- Added text the the built in help to explain that reducing the size of the receive buffer can be used to reduce CPU power consumption.
- [MAC] Compiling for Cocoa from now on (intel based Macs only). The universal binary still uses Carbon.
- [MAC] Added basic retina support.
IMPROVEMENTS
- CoolTerm now properly remembers the last used folders (individually) for opening connection settings, capturing to text files, as well as sending text files.
- Added DEL character (ASCII 127) to the routine that handles BS characters in ASCII view.
- optimized code to reduce CPU load while sending text files.
- stability improvement to the code of the circular receive buffer.
BUG FIXES AND STABILITY IMRPOVEMENTS
- fixed code that could cause extended ASCII characters to sometimes be incorrectly translated from hexadecimal format to plain text.


1.4.3: 09/02/2013
-----------------
NEW/CHANGED FEATURES:
- Added preference setting to select the date and time format used for timestamps. The user can select between the SQL Date/Time format (YYYY-MM-DD HH:MM:SS) or the format determined by the users local system settings.
- Added options to choose the timestamp type and modified the code to fix an bug where the millisecond count and the Date/Time timestamp could get out of sync. It is now only possible to capture timestamps with millisecond resolution when selecting the relative timestamp format.
BUG FIXES AND STABILITY IMPROVEMENTS:
- Made various stability improvements to the code that updates the GUI while data is being sent and received.


1.4.2: 02/17/2013
-----------------
NEW/CHANGED FEATURES:
- Added options to set the initial state of RTS and DTR when the serial port opens. These options will only have an effect if the respective hardware flow control is not enabled.
- Changed the behavior of capturing received data to file when timestamps are enabled. Instead of appending a time stamp at every occurrence of CR and/or LF characters by default, it is now possible to specify the termination string at which to split the data. Furthermore, CoolTerm will now wait until the specified termination string is received until the data is captured to file.
- Added option to convert received data to hex before capturing to a capture file.
- Enabled the "Close Window" short cut for the "Send String" window.
- Added Alt+ENTER short cut for toggling between ASCII and Hex mode in "Send String"
- Added Connection/Reset menu item to provide a way to reset the port and unlock it if XOFF is active.
- Changed the behavior of the text file capturing with regards to the state of the port. It is now possible to start capturing before the port is opened. In addition, capturing is no longer stopped automatically when the port is closed. This allows for capturing to remain enabled even when the connection state of the port changes. 
- Added code to allow canceling of a text file transmission in progress if XOFF is active.
- Added option to the connection settings (Misc. Options) to automatically close the serial port when the window is being closed without showing a warning if the port is still open.
- Updated the built-in help with information on all menu items.

BUG FIXES AND STABILITY IMPROVEMENTS:
- fixed bug that would cause a NilObjectException in the Xmit routine in cases where the serial port is still transmitting or is hung while the port goes out of scope. This hopefully fixes the crash bug some users have experienced on occasion.
- Fixed bug that caused the transmit line delay setting to not properly be saved to connection settings files.
- Made improvements to receive buffer code to avoid resource conflicts.
Windows only:
- Changed file association on windows to work even on systems where the current user may not have administrative privileges.

APPLESCRIPT:
- Changed AppleScript commands to use unique terminal window IDs instead of the names when addressing windows.
- Added the following AppleScript commands
	- WindowCount as integer
	- WindowID(Index as integer) as integer
	- WindowName(index as integer) as String
	- IndexOfWindowID(ID as integer) as integer
	- NewWindow as integer
	- Quit
	- ResetPort(ID as integer)
	- FlushPort(ID as integer)
	- BytesLeftToSend(ID as integer) as integer
	- LastErrorCode(ID as integer) as integer
	- GetCTS(ID as integer) as boolean
	- GetDSR(ID as integer) as boolean
	- GetDCD(ID as integer) as boolean
	- GetRI(ID as integer) as boolean
	- CaptureStart(ID as integer, FilePath as string) as boolean
	- CapturePause(ID as integer)
	- CaptureResume(ID as integer)
	- CaptureStop(ID as integer)
	- SendTextFile(ID as integer, FilePath as string) as boolean
	- SendBreak(ID as integer)
	- SetDTR(ID as integer, Value as boolean)
	- GetDTR(ID as integer) as boolean
	- SetRTS(ID as integer, Value as boolean)
	- GetRTS(ID as integer) as boolean
- Added code to suppress error messages when CoolTerm is controlled by an AppleScript.
- Updated AppleScriptReadme.txt to reflect latest changes.


1.4.1: 11/21/2011
-----------------
- Improved handling of exceptions if preferences or connection settings can not be read or written.
- Checking serial port for nil in the transmit thread to avoid NilObjectException exceptions. Not clear if this fixes the issue a few users have seen.
- Improved exception handling when serial port adapters are added or removed from the system while CoolTerm is running.
- Fixed a bug in the circular receive buffer that could cause an OutOfBoundsException when reading data.
- Improved handing of OutOfMemoryExceptions when attempting to set the receive buffer size to a value larger than the amount of memory available on the user's system.


1.4.0: 9/12/2011
----------------
NEW FEATURES:
- New Connection options window with multiple pages.
- The connection options now display port information for the selected port.
- It is now possible to change baudrate, byte format settings, and flow control settings while the port is open.
- Added the option to specify additional baud rates via a "baudrates.ini" file. E.g. any baud rates that are known to be supported by the hardware that are not listed in the popup menu in the connection settings dialog can be added to a "baudrate.ini" file that resides in the same directory as CoolTerm.
- Added the option to specify additional serial ports via a "ports.ini" file. E.g. any devices such as /dev/tty.xxx devices on OSX and Linux that CoolTerm can not enumerate can be added to a "ports.ini" file that resides in the same directory as CoolTerm.
- Added the option to add timestamps to data captured to text files.
- Added a keyboard shortcut to connect/disconnect.
- Added option to replace TAB key presses with a configurable number of spaces (default = 4).
- Added option to enable/disable capturing of local echo of transmitted data in capture files.
- Added an option to keep the capture file open while capturing is in progress (default) or close it after writing and re-opening when new data arrives. This allows other applications to read the capture file while capturing is in progress.
- Added status LEDs for TX and RX to indicate activity related to sending and receiving data.
- Added preferences option to disable all menu shortcuts (on Windows and Linux only) in order to allow sending CTRL characters via the terminal. On Mac, the keyboard shortcuts use the Command key and thus don't interfere with CTRL characters.
- [MAC] AppleScript BETA: Added basic AppleScript handling for the most important terminal operations such as loading a settings file, opening/closing ports, and reading/writing data. The AppleScript functionality, while included in CoolTerm 1.4.0, is currently in public BETA , to allow a broader audience to beta test this feature and provide feedback. Refer to the attached "AppleScript ReadMe.txt" file for more details.
- [LINUX] Making LINUX version (unsupported) available.

IMPROVEMENTS:
- Made significant improvements to the code that processes received data, including changing architecture of the receive buffer to a circular buffer to improve efficiency and stability.
- Made significant improvements to the code that transmits data, including changing the architecture of the data transmission to be more asynchronous in nature to improve the responsiveness of CoolTerm during transmission of large text files, particularly with XON/XOFF flow control enabled
- CoolTerm now opens a progress window whenever the length of the text to be transmitted exceeds a certain threshold, and not only when text files are sent. 
- Flow control settings are now displayed in the terminal window as part of the port configuration string. For XON/XOFF the state is displayed, i.e. XON or XOFF.
- Added error messages to alert the user of errors that occur while attempting to open the serial port.
- Added check to warn the user if multiple files are dropped onto the CoolTerm window.
- "Send String" windows can now be resized.
- It is now possible to send CTRL characters when the terminal is set to Line Mode.
- Improved code for Line Mode to ensure that a pressed key is captured even if the command line didn't have the focus.
- Changed behavior of the status LEDs to better reflect the state of the signals. A green LED turned on now means that a signal is "active", the LED turned off means that it is "inactive".
- Changed the default state of DTR when a port is opened to "active" to conform with common practice, with the exception of Windows platforms when DTR flow control is enabled, in which case the default is "inactive" in order to avoid serial port errors.
- Improved handling of file IO errors when sending textile or capturing received data to textiles.
- Improved handling of file IO errors when reading and writing settings files.
- Improved error reporting. Crash reports will now include information about all open terminals.
- Slight change to the behavior during setting the break signal in that no characters are being read from the receive buffer. Received characters will be read after the break signal has been cleared.

BUG FIXES:
- Fixed a bug that would show an error message when the user chooses cancel in the capture file save dialog.
- Fixed a bug that threw an exception when opening the connection settings on a system without serial ports installed.
- Fixed a bug the displayed an error message when the user cancelled out of the "Send Textfile" dialog.
- [WIN] Fixed a bug where the removal of a serial port adapter could cause an exception when starting a connection.
- [MAC] Implemented a workaround for a known RB bug where the baudrates 3600, 7200, 14400, and 28800 baud would not be set correctly and default to 57600 baud instead.


1.3.1: 1/11/2011
----------------
Improvements:
- Added a preferences option to automatically check for updates at startup.

Fixes:
- Fixed a bug that caused a StackOverFlowException when serial port devices were unexpectedly removed from the system, e.g. when a USB serial adapter was unplugged while the terminal was connected to that device. The error handling for this situation has been improved.
- Fixed a bug that caused an OutOfBoundsException when a serial port device failure occurred during enumeration.
- Fixed a bug that resulted in incorrect formatting of long crash reports.


1.3.0: 10/28/2010
-----------------
New features:
- Added a transmit line delay option which adds a specified delay after certain characters such as new line characters (configurable).
- Added a transmit character delay option (configurable).
- Added a "Connection/Send Break" menu item for sending serial breaks.
- Added the option to play a notification sound after a text file has been sent.
- Added auto-connect feature.
- Added the .hex file extension to the "Text Files" file type set (for the "Send Text File" dialog).
- It is now possible to have default settings loaded at startup and when a new terminal window is opened. If a default.stc settings file exists in the application folder of CoolTerm, it will be applied to new terminal windows.
- Added a menu item to save current settings as default settings.

Improvements:
- Pressing ENTER or RETURN in the connection settings dialog now envokes the "Ok" button, even if a textfield is currently selected.
- Pressing ESC in the connection settings dialog now invokes the "Cancel" button, even if a textfield is currently selected.
- Pressing Shift+ENTER or Shift+RETURN now invokes the "Send" button in "Send String" windows.
- Improved handling of command line arguments.
- The values for "Receive Buffer Size" and the character and line delays are now limited to a range from 0 to a maximum value (2,147,483,647 and 10,000, respectively).
- When a "Send String" window is opened, the text field now receives focus automatically.
- Improved exception handling and error reporting.
- Improved behavior of the command history buffer and menu.
- GUI improvements.

Fixes:
- Fixed a bug that allowed opening multiple "Save As..." for the same Terminal window dialogs on Windows.
- Fixed a bug that could cause a StackOverflow on serial port errors due to calling port.flush
- Fixed bug that could cause a crash when sending empty strings via a "Send  String" window.
- (Win) Fixed issue that would allow the terminal window to be activated via the taskbar when the connection options window is open.
- Several minor bug fixes.


1.2.0: 2/19/2010
----------------
- Added "Line Mode" to the communication settings. In "Line Mode" a line of typed text will not be sent to the serial port until the Enter key is pressed.
- Added "History" which is available in "Line Mode" the up and down arrow keys can be used to select previously typed lines.
- Added a receive buffer size limit option.
- Added handling of the bell character (ASCII code 7), which can be enabled through the communication settings.
- It is now possible to open the communication settings and edit certain options while the serial port is open.
- The viewer mode (plain or hex) is now saved as parameter in connection settings files.
- The size and position of terminal windows is now saved with connection settings.
- Fixed bug that converted occurrences CR+CR+LF strings to single spaces on Windows.


1.1.2: 7/17/2009
----------------
- Separated option to handle backspace characters in ASCII view from option to convert non-printable characters.
- Changed character used to display non-printable characters to a period (ASCII code 46) for better compatibility and consistency across platforms.
- Changed short cuts for "View/Autoscroll" and View Mode menu items to avoid conflict with other menu items such as "Edit/Select All".
- Windows build now associates .stc files with CoolTerm.
- Minor bug fixes.


1.1.1: 6/29/2009
----------------
- Added option to handle backspace characters in ASCII view to Connection Settings.
- Fixed bug in SendString that prevented typing 8 in hex mode.
- Fixed bug that printed the wrong character for cursor down key when ConvertNonPrint was enabled.
- Added a "Check for Updates" Menu item.


1.1.0: 6/18/2009
----------------
- Added an option to the connection settings to automatically terminate string sent from "Send String" windows with a configurable "Termination String", such as e.g. a linefeed etc.
- In ASCII view mode, all incoming "New Line" such as CR, LF, CR+LF, are now properly displayed as line breaks.
- Added an option to the connection settings to convert non-printable characters to generic dot characters in ASCII view.
- Added 'View' menu with menu item to switch between Hex and ASCII viewing.
- Moved 'Clear Data' menu item to 'View' menu.
- Added an 'Autoscroll' feature, accessible via the 'View' menu to enable/disable automatic scrolling of received data.
- Changed menu shortcut key for "Cycle through windows" from "0" to "`".
- Added code to produce an audible alert (system beep) when characters are typed while the serial port is not connected.
- Added a 'Help' button to the toolbar


1.0.0: 5/19/2009
----------------
- Initial Public Release




LICENSE
=======

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
