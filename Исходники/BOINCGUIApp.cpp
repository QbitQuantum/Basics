// Set s_bSkipExitConfirmation to true if cancelled because of logging out or shutting down
OSErr QuitAppleEventHandler( const AppleEvent *appleEvt, AppleEvent* reply, UInt32 refcon ) {
        DescType            senderType;
        Size                actualSize;
        ProcessSerialNumber SenderPSN;
        ProcessInfoRec      pInfo;
        FSSpec              fileSpec;
        OSStatus            anErr;

        // Refuse to quit if a modal dialog is open.  
        // Unfortunately, I know of no way to disable the Quit item in our Dock menu
        if (wxGetApp().IsModalDialogDisplayed()) {
            SysBeep(4);
            return userCanceledErr;
        }
                
        anErr = AEGetAttributePtr(appleEvt, keyAddressAttr, typeProcessSerialNumber,
                                    &senderType, &SenderPSN, sizeof(SenderPSN), &actualSize);

        if (anErr == noErr) {
            pInfo.processInfoLength = sizeof( ProcessInfoRec );
            pInfo.processName = NULL;
            pInfo.processAppSpec = &fileSpec;

            anErr = GetProcessInformation(&SenderPSN, &pInfo);

            // Consider a Quit command from our Dock menu as coming from this application
            if ( (pInfo.processSignature != 'dock') && (pInfo.processSignature != 'BNC!') ) {
                s_bSkipExitConfirmation = true; // Not from our app, our dock icon or our taskbar icon
                wxGetApp().ExitMainLoop();  // Prevents wxMac from issuing events to closed frames
            }
        }
    
    return wxGetApp().MacHandleAEQuit((AppleEvent*)appleEvt, reply);
}