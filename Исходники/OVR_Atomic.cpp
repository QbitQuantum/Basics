// Constructors
Lock::Lock(unsigned spinCount)
{
    #if defined(NTDDI_WIN8) && (NTDDI_VERSION >= NTDDI_WIN8)
       // On Windows 8 we use InitializeCriticalSectionEx due to Metro-Compatibility
       InitializeCriticalSectionEx(&cs, (DWORD)spinCount,
                                   OVR_DEBUG_SELECT(NULL, CRITICAL_SECTION_NO_DEBUG_INFO));
    #else
        ::InitializeCriticalSectionAndSpinCount(&cs, (DWORD)spinCount); // This is available with WindowsXP+.
    #endif
}