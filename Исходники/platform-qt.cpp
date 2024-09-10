void setKeepAwake(bool awake)
{
    if (awake){
        #if defined(Q_OS_WIN)
            SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_CONTINUOUS);
            
        #elif defined(Q_OS_MAC)
            if(success == kIOReturnSuccess) {
            	
            }else{
                success = IOPMAssertionCreateWithName(kIOPMAssertionTypeNoDisplaySleep, 
                                                    kIOPMAssertionLevelOn, reasonForActivity, &assertionID);
            }
        #endif
    }else{
        #if defined(Q_OS_WIN)
            SetThreadExecutionState(ES_CONTINUOUS);
            
        #elif defined(Q_OS_MAC)
            if(success == kIOReturnSuccess) {
                IOPMAssertionRelease(assertionID);
                success = kIOReturnError;
                
            }else{
            	
            }
        #endif
    }
}