void PDataManager::UnregisterPdata(RUNTIME_FUNCTION* pdata)
{
    if (AutoSystemInfo::Data.IsWin8OrLater())
    {
        NtdllLibrary::Instance->DeleteGrowableFunctionTable(pdata);
    }
    else
    {
        BOOLEAN success = RtlDeleteFunctionTable(pdata);
        Assert(success);
    }
}