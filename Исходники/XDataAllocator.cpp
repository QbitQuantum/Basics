/* static */
void XDataAllocator::Register(XDataAllocation * xdataInfo, ULONG_PTR functionStart, DWORD functionSize)
{
#ifdef _WIN32
    ULONG_PTR baseAddress = functionStart;
    xdataInfo->pdata.BeginAddress = (DWORD)(functionStart - baseAddress);
    xdataInfo->pdata.EndAddress = (DWORD)(xdataInfo->pdata.BeginAddress + functionSize);
    xdataInfo->pdata.UnwindInfoAddress = (DWORD)((intptr_t)xdataInfo->address - baseAddress);

    BOOLEAN success = FALSE;
    if (AutoSystemInfo::Data.IsWin8OrLater())
    {
        DWORD status = NtdllLibrary::Instance->AddGrowableFunctionTable(&xdataInfo->functionTable,
            &xdataInfo->pdata,
            /*MaxEntryCount*/ 1,
            /*Valid entry count*/ 1,
            /*RangeBase*/ functionStart,
            /*RangeEnd*/ functionStart + functionSize);
        success = NT_SUCCESS(status);
        if (success)
        {
            Assert(xdataInfo->functionTable != nullptr);
        }
    }
    else
    {
        success = RtlAddFunctionTable(&xdataInfo->pdata, 1, functionStart);
    }
    Js::Throw::CheckAndThrowOutOfMemory(success);

#if DBG
    // Validate that the PDATA registration succeeded
    ULONG64            imageBase = 0;
    RUNTIME_FUNCTION  *runtimeFunction = RtlLookupFunctionEntry((DWORD64)functionStart, &imageBase, nullptr);
    Assert(runtimeFunction != NULL);
#endif

#else  // !_WIN32
    Assert(ReadHead(xdataInfo->address));  // should be non-empty .eh_frame
    __register_frame(xdataInfo->address);
#endif
}