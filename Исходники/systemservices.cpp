/*!
Mandatory call to be inserted in derived constructor.
This method tries to establish communications with printer and identify it.
The derived SystemServices constructor must call this base-class routine.
*/
DRIVER_ERROR SystemServices::InitDeviceComm()
// Must be called from derived class constructor.
// (Base class must be constructed before system calls
//  below can be made.)
// Opens the port, looks for printer and
// dialogues with user if none found;
// then attempts to read and parse device ID string --
// if successful, sets IOMode.bDevID to TRUE (strings stored
// for retrieval by PrintContext).
// Returns an error only if user cancelled. Otherwise
// no error even if unidi.
//
// Calls: OpenPort,PrinterIsAlive,DisplayPrinterStatus,BusyWait,
//   GetDeviceID,DeviceRegistry::ParseDevIDString.
// Sets:    hPort,IOMode, strModel, strPens
{
    DRIVER_ERROR err = NO_ERROR;
    BOOL ErrorDisplayed = FALSE;
    BYTE temp;

    // Check whether this system supports passing back a status-byte
    if( GetStatusInfo(&temp) == FALSE )
    {
        DBG1("InitDeviceComm:  No Status-Byte Available\n");
    }
    else IOMode.bStatus = TRUE;

    // Check whether we can get a DeviceID - this may
    // still fail if the device is just turned off
    err = GetDeviceID(strDevID, DevIDBuffSize, TRUE);

    if ( err == NO_ERROR )
    {
        DBG1("InitDeviceComm:  DevID request successful\n");
        IOMode.bDevID = TRUE;
    }


    // PrinterIsAlive is arbitrary if we can't get the status-byte.
    // This check is also critical so a true uni-di system does not sit
    // in a loop informing the user to turn on the printer.
    if ( IOMode.bStatus == TRUE )
    {
        // Make sure a printer is there, turned on and connected
        // before we go any further.  This takes some additional checking
        // due to the fact that the 895 returns a status byte of F8 when
        // it's out of paper, the same as a 600 when it's turned off.
        // 895 can get a devID even when 'off' so we'll key off that logic.
        if ( (err != NO_ERROR) && (PrinterIsAlive() == FALSE) )
        {
            // Printer is actually turned off
            while(PrinterIsAlive() == FALSE)
            {
                DBG1("PrinterIsAlive returned FALSE\n");
                ErrorDisplayed = TRUE;
                DisplayPrinterStatus(DISPLAY_NO_PRINTER_FOUND);

                if(BusyWait(500) == JOB_CANCELED)
                    return JOB_CANCELED;
            }
            if(ErrorDisplayed == TRUE)
            {
                DisplayPrinterStatus(DISPLAY_PRINTING);
                // if they just turned on/connected the printer,
                // delay a bit to let it initialize
                if(BusyWait(2000) == JOB_CANCELED)
                    return JOB_CANCELED;

                err = GetDeviceID(strDevID, DevIDBuffSize, TRUE);
                if ( err == NO_ERROR )
                {
                    DBG1("InitDeviceComm:  DevID request successful\n");
                    IOMode.bDevID = TRUE;
                }
            }
        }
        // else... we have 8xx/9xx with an out-of-paper error
        // which we will catch in the I/O handling

    }

    if (err!=NO_ERROR)
    {
        DBG1("InitDeviceComm:  No DeviceID Available\n");
        return NO_ERROR;
    }

    err = DR->ParseDevIDString((const char*)strDevID, strModel, &VIPVersion, strPens);

    if (err!=NO_ERROR)
    {
        // The DevID we got is actually garbage!
        DBG1("InitDeviceComm:  The DevID string is invalid!\n");
        IOMode.bDevID=FALSE;
    }

    return NO_ERROR;
}