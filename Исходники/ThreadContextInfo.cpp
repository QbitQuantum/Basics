void
ThreadContextInfo::SetValidCallTargetForCFG(PVOID callTargetAddress, bool isSetValid)
{
#ifdef _CONTROL_FLOW_GUARD
    if (IsCFGEnabled())
    {
#ifdef _M_ARM
        AssertMsg(((uintptr_t)callTargetAddress & 0x1) != 0, "on ARM we expect the thumb bit to be set on anything we use as a call target");
        AssertMsg(IS_16BYTE_ALIGNED((uintptr_t)callTargetAddress & ~0x1), "callTargetAddress is not 16-byte page aligned?");
#else
        AssertMsg(IS_16BYTE_ALIGNED(callTargetAddress), "callTargetAddress is not 16-byte page aligned?");
#endif

        // If SetProcessValidCallTargets is not allowed by global policy (e.g.
        // OOP JIT is in use in the client), then generate a fast fail
        // exception as state has been corrupted and attempt is being made to
        // illegally call SetProcessValidCallTargets.
        if (!GlobalSecurityPolicy::IsSetProcessValidCallTargetsAllowed())
        {
            RaiseFailFastException(nullptr, nullptr, FAIL_FAST_GENERATE_EXCEPTION_ADDRESS);
        }

        PVOID startAddressOfPage = (PVOID)(PAGE_START_ADDR(callTargetAddress));
        size_t codeOffset = OFFSET_ADDR_WITHIN_PAGE(callTargetAddress);

        CFG_CALL_TARGET_INFO callTargetInfo[1];

        callTargetInfo[0].Offset = codeOffset;
        callTargetInfo[0].Flags = (isSetValid ? CFG_CALL_TARGET_VALID : 0);

        AssertMsg((size_t)callTargetAddress - (size_t)startAddressOfPage <= AutoSystemInfo::PageSize - 1, "Only last bits corresponding to PageSize should be masked");
        AssertMsg((size_t)startAddressOfPage + (size_t)codeOffset == (size_t)callTargetAddress, "Wrong masking of address?");

        BOOL isCallTargetRegistrationSucceed = GetWinCoreMemoryLibrary()->SetProcessCallTargets(GetProcessHandle(), startAddressOfPage, AutoSystemInfo::PageSize, 1, callTargetInfo);

        if (!isCallTargetRegistrationSucceed)
        {
            DWORD gle = GetLastError();
            if (gle == ERROR_COMMITMENT_LIMIT)
            {
                //Throw OOM, if there is not enough virtual memory for paging (required for CFG BitMap)
                Js::Throw::OutOfMemory();
            }
            else if (gle == ERROR_ACCESS_DENIED)
            {
                // When this error is set, the target process may be exiting and thus cannot proceed with
                // JIT output. Throw this exception to safely abort this call.
                throw Js::OperationAbortedException();
            }
            else
            {
                Js::Throw::InternalError();
            }
        }
#if DBG
        if (isSetValid && !JITManager::GetJITManager()->IsOOPJITEnabled())
        {
            _guard_check_icall((uintptr_t)callTargetAddress);
        }

        if (PHASE_TRACE1(Js::CFGPhase))
        {
            if (!isSetValid)
            {
                Output::Print(_u("DEREGISTER:"));
            }
            Output::Print(_u("CFGRegistration: StartAddr: 0x%p , Offset: 0x%x, TargetAddr: 0x%x \n"), (char*)startAddressOfPage, callTargetInfo[0].Offset, ((size_t)startAddressOfPage + (size_t)callTargetInfo[0].Offset));
            Output::Flush();
        }
#endif
    }
#endif // _CONTROL_FLOW_GUARD
}