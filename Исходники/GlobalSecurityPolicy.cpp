void
GlobalSecurityPolicy::DisableSetProcessValidCallTargets()
{
    // One-way transition from allowing SetProcessValidCallTargets to disabling
    // the API.
    if (!s_ro_disableSetProcessValidCallTargets)
    {
        AutoCriticalSection autocs(&s_policyCS);
        DWORD oldProtect;

        BOOL res = VirtualProtect((LPVOID)&s_ro_disableSetProcessValidCallTargets, sizeof(s_ro_disableSetProcessValidCallTargets), PAGE_READWRITE, &oldProtect);
        if ((res == FALSE) || (oldProtect != PAGE_READONLY))
        {
            RaiseFailFastException(nullptr, nullptr, FAIL_FAST_GENERATE_EXCEPTION_ADDRESS);
        }
    
        s_ro_disableSetProcessValidCallTargets = true;
    
        res = VirtualProtect((LPVOID)&s_ro_disableSetProcessValidCallTargets, sizeof(s_ro_disableSetProcessValidCallTargets), PAGE_READONLY, &oldProtect);
        if ((res == FALSE) || (oldProtect != PAGE_READWRITE))
        {
            RaiseFailFastException(nullptr, nullptr, FAIL_FAST_GENERATE_EXCEPTION_ADDRESS);
        }
    }
}