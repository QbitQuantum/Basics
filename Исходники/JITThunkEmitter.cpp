template <typename TAlloc> inline
void
JITThunkEmitter<TAlloc>::FreeThunk(uintptr_t thunkAddress)
{
    AutoCriticalSection autoCs(&this->cs);
    BVIndex thunkIndex = GetThunkIndexFromAddress(thunkAddress);
    if (thunkIndex >= this->freeThunks.Length() || this->freeThunks.TestAndSet(thunkIndex))
    {
        Assert(UNREACHED);
        this->firstBitToCheck = 0;
        return;
    }

    if (thunkIndex < firstBitToCheck)
    {
        this->firstBitToCheck = thunkIndex;
    }

    if (CONFIG_FLAG(OOPCFGRegistration))
    {
#if ENABLE_OOP_NATIVE_CODEGEN
        if (JITManager::GetJITManager()->IsJITServer())
        {
            HANDLE fileHandle = nullptr;
            PVOID baseAddress = nullptr;
            bool found = this->codeAllocator->GetFileInfo((PVOID)thunkAddress, &fileHandle, &baseAddress);
            AssertOrFailFast(found);
            this->threadContext->SetValidCallTargetFile((PVOID)thunkAddress, fileHandle, baseAddress, false);
        }
        else
#endif
        {
            this->threadContext->SetValidCallTargetForCFG((PVOID)thunkAddress, false);
        }
    }

    uintptr_t pageStartAddress = GetThunkPageStart(thunkAddress);
    if (IsThunkPageEmpty(pageStartAddress))
    {
        this->codeAllocator->Free((PVOID)pageStartAddress, AutoSystemInfo::PageSize, MEM_DECOMMIT);
    }
    else
    {
        char * localAddress = (char *)this->codeAllocator->AllocLocal((PVOID)thunkAddress, ThunkSize);
        if (localAddress == nullptr)
        {
            return;
        }
        UnprotectPage(localAddress);
        memset(localAddress, 0xCC, ThunkSize);
        ProtectPage(localAddress);
        this->codeAllocator->FreeLocal(localAddress);
    }
    FlushInstructionCache(this->processHandle, (PVOID)thunkAddress, ThunkSize);
}