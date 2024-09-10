/**
 Change the debugport to port KDebugPort(3)

 This function is optional and specific to variant. Incase of H4 variant,
 default debugport is 1. However since this tutorial driver tests both
 unit1(port1) and unit2(port2), default port is being changed to port3
 to avoid conflict

 @post	Debugport changed to COM port3
 */
TInt TestExDriver::ChangeDebugPort(TInt aNewPort)
{
    TInt muid;
    TInt val=-1;
    TInt newval;

    // HAL API provides interface to read and set some system attributes
    // specified by HALData. Here, HAL::EMachineUid gives the machine uid
    // on which this test is being executed.
    //
    const TInt r = HAL::Get(HAL::EMachineUid, muid);
    if (r==KErrNone)
    {
        // If the board is H4, we would like to change the debugport to 3
        // to enable testing unit1. If unit1 is not being tested, then
        // no need to change the debugport
        //
        if (muid == HAL::EMachineUid_OmapH4)
        {
            // Get the deugport that is set currently using HAL API
            HAL::Get(HALData::EDebugPort,val);
            if (val!=aNewPort)
            {
                // Set the debugport to KDebugPort
                HAL::Set(HALData::EDebugPort,aNewPort);
                // Read again and verify
                HAL::Get(HALData::EDebugPort,newval);
                // Here, test() macro is not used to check as we dont want
                // to panic or exit if the check fails. test() macro check
                // panics and exits on the condition cheked being false
                //
                if(newval!=aNewPort)
                {
                    // Failed changing debugport, we'll not be able to view
                    // log messages on the debug port, but can see on display
                    //
                    iTest.Printf(_L("\nChanging DebugPort Failed\n"));
                }

                // Debugport changed to KDebugPort
                iTest.Printf(_L("\nDebugPort Changed to (%d))\n"),newval);

                // Let the user know the current debug port
                iTest.Printf(_L("\nPlease use COM port%d to view the debug messages on PC's hyperterminal\n"), newval);

                // User::After() suspends the current thread until a specified time
                // interval has expired. Time is given in microseconds.
                // This is added here to give the user view the above messages before
                // continuing
                //
                User::After(2000000); // 2 secs, in units of microseconds
            }
        }
    }

    // return the initial debug port
    return val;
}