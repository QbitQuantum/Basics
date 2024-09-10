TInt CFloggerTest002_01::executeStepL( )
{
    INFO_PRINTF1(_L("Step 002.01 called "));

    RFileLogger theFlogger;
    TPtrC8 ptrSubSystem;
    TPtrC8 ptrComponent;
    ptrSubSystem.Set(_L8("SubSystem"));
    ptrComponent.Set(_L8("Component"));

    TInt result = theFlogger.Connect();
    CleanupClosePushL(theFlogger);
    theFlogger.SetLogTags(ptrSubSystem, ptrComponent);
    CleanupStack::PopAndDestroy();	//logger
    return result;
}