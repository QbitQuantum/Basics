bool StWinHandles::unregisterClass(StStringUtfWide& theName) {
    HMODULE aModule = GetModuleHandleW(NULL);
    if(!theName.isEmpty()) {
        if(UnregisterClassW(theName.toCString(), aModule) == 0) {
            ST_DEBUG_LOG("WinAPI, FAILED to unregister Class= '" + theName.toUtf8() + "'");
            return false;
        }
        ST_DEBUG_LOG("WinAPI, Unregistered Class= " + theName.toUtf8());
        theName.clear();
    }
    return true;
}