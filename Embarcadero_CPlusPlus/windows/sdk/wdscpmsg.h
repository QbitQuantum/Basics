#pragma option push -b -a8 -pc -A- -w-pun /*P_O_Push*/
//-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 2006
//
//--------------------------------------------------------------------------
// CLog::LogEvent compares the error level of the HRESULT with the error
// level of the module attempting to log the HRESULT's message (which is
// set during CLog::InitLogInstance).  If the HRESULT's error level <=
// the module's error level, then the error is logged.
//
// ADDING AND REMOVING MESSAGES
//
// Note that the MessageId is actually broken up into two parts.  The
// high 4 bits is actually an error level indicating the severity of
// the error.  The rest of the bit number indicates the actual event
//    message id.  The error level can be used to filter out event
// messages that you don't want logged all the time, unless the
// administrator is actively diagnosing something.  Also note the
// message id's are limited to a 16-bit number.
//
// The messages in this file are explicitly numbered. Do not renumber
// existing messages so as to make space to add your message.
// You should always add you message in the end of the file.
// The reason is that it often desirable to be able to read an event
// log with a message file that is from a different build, so renumbering
// existing messages should be avoided.
//
// If you want to remove a message, do NOT simply delete it from the file.
// Instead change its symbolic name to BIGLOG_UNUSED_xxx (where xxx is a
// sequential number just used to uniquify the names) and its text to
//  "Unused message".
//
// If you want to set the log level of the message, you need to OR the
// message ID with the following constants, to get log level of 0, 1, 2, 3
// 0x0000 , 0x4000, 0x8000, 0xc000
//
// For example:
//     MessageId=0x8100
//     Facility=MyFacility
//     Severity=Error
//     SymbolicName=ERROR_ID_100
//     Language=English
//     This is the text for error ID 0x101, with error level 8
//     .
//     MessageId=0x4101
//     Facility=MyFacility
//     Severity=Error
//     SymbolicName=ERROR_ID_101
//     Language=English
//     This is the text for error ID 0x101, with error level 1
//     .
//     .
//     MessageId=0x10000
//     Facility=MyFacility
//     Severity=Error
//     SymbolicName=ERROR_ID_10000
//     Language=English
//     DONT' DO THIS!!!  Message ID is > 0xFFFF.  This won't EVER work
//     .
//
// IMPORTANT NOTES
//
// NOTE THAT YOU MUST NOT DELETE OR RE-USE EVENTS THAT WERE MEANINGFUL IN
// PREVIOUSLY RELEASED VERSIONS OF THE PRODUCT.  Why?  Consider an app running
// on Win2k+1 that scans the event logs of all DCs (Win2k and Win2k+1) in an
// enterprise.  The scanner should be able to retrieve the text asociated
// with the Win2k event on the Win2k+1 box (since the event log does not
// provide this service -- text must always be looked up locally).  Also
// consider that watchdog tools often cue off of certain event IDs appearing
// in the event log (e.g., to page an admin when something particularly bad
// happens), so you don't want event 893 to mean one thing on Win2k and
// something completely different on Win2k+1.
//
// By the same token, YOU MUST NOT CHANGE THE ORDER OF INSERTION STRINGS OF
// EVENTS THAT WERE MEANINGFUL IN PREVIOUSLY RELEASED VERSIONS OF THE PRODUCT.
// It's okay to add new insertion strings to existing event log messages (they
// just won't be filled in when looking at the event generated by an older
// program), just add them at the end.  (E.g., if %1 %2 and %3 are already used,
// add new insertion strings at %4, *don't* put the new one as %2 and bump
// the old %2 to %3 and the old %3 to %4.)  Whether an insertion string is
// %1 or %4 or whatever of course doesn't restrict where it can be placed in
// the message text, it only provides a mapping to the order of parameters
// given to LogEvent.
//
// To add a new message, first see if there is an existing unused message
// that you can recycle.  If so, do so.  If no more unused messages remain,
// then you must be sure to add new messages only at the very end of the
// file.
//
// Dev Note:
//     If you add new facilities here, remember to update the registry setup
//     for event logging in the manifest to correctly reflect the new category
//     count.
//
// Define the severities
//
// Define the facility names
//
//
// Category Names Used for Event Logging
//
//
// These message id's are names for categories, which are equivalent to
// to facilities - 0x100.  LogEvent extracts the facility from the HRESULT,
// and logs that as the Category.  These message IDs allow that category
// to appear as the textual facility name in the event viewer
//
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_WDSCP                   0x125


//
// Define the severity codes
//
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: WDSCP_CATEGORY
//
// MessageText:
//
// WdsCp
//
#define WDSCP_CATEGORY                   ((HRESULT)0x00000001L)

///////////////////////////////////////////////////////////////////
//
//                WDSCP Facility Messages
//
///////////////////////////////////////////////////////////////////
//
// Error Messages
// These start at ID 100
//
//
// MessageId: WDSCP_E_INVALID_CONFIGURATION
//
// MessageText:
//
// The configuration string was invalid or empty.
//
#define WDSCP_E_INVALID_CONFIGURATION    ((HRESULT)0xC1250100L)

//
// MessageId: WDSCP_E_NOT_A_DIRECTORY
//
// MessageText:
//
// The path specified in the configuration string was not a directory.
//
#define WDSCP_E_NOT_A_DIRECTORY          ((HRESULT)0xC1250101L)

//
// MessageId: WDSCP_E_CONFIG_STRING_REQUIRED
//
// MessageText:
//
// The WDS Content Provider requires that a configuration string be provided.
//
#define WDSCP_E_CONFIG_STRING_REQUIRED   ((HRESULT)0xC1250102L)

#pragma option pop /*P_O_Pop*/
