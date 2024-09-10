bool ot_unlockPage(void* addr, int len)
{
    static bool bWarned = false;

#ifdef _WIN32
	return VirtualUnlock(addr, len);
#elif defined(PREDEF_PLATFORM_UNIX)
	if (munlock(addr, len) && !bWarned)
    {
        bWarned = true;
        OTLog::Error("ot_unlockPage: WARNING: unable to unlock memory used for storing secrets.\n");
    }
    return true;        
#else
	OT_ASSERT_MSG(false, "ASSERT: ot_unlockPage unable to unlock secret memory.");
#endif
    return false;
}