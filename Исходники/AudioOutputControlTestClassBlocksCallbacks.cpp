//Devsound initialization is completed.Configure devsound capabilities.
void CAudioOutputControlTestClass::InitializeComplete(TInt aError)
{
    FTRACE(FPrint(_L("CAudioOutputControlTestClass::InitializeComplete")));

    iLog->Log(_L("InitializeComplete, return code =%d!!!"),aError);
    ProcessEvent(EInitializeComplete, aError);

}