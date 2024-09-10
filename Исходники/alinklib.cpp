////////////////////////////////////////////////////////////////////////////////
// GetMesageDll -- find and load the message DLL. Returns 0 if the message
// DLL could not be located or loaded. The message DLL should be either in a 
// subdirectory whose name is a language id, or in the current directory. We have
// a complex set of rules to figure out which language ids to try.
HINSTANCE WINAPI GetALinkMessageDll ()
{
    LANGID langid;

    if (! hModuleMessages) {
        HINSTANCE hModuleMessagesLocal = 0;


        // Next try current locale.
        if (!hModuleMessagesLocal) {
            langid = LANGIDFROMLCID(GetThreadLocale());
            hModuleMessagesLocal = FindMessageDll(langid);
            if (!hModuleMessagesLocal)
                hModuleMessagesLocal = FindMessageDll(MAKELANGID(PRIMARYLANGID(langid), SUBLANG_DEFAULT));
        }

        // Next try user and system locale.
        if (!hModuleMessagesLocal) {
            langid = GetUserDefaultLangID();
            hModuleMessagesLocal = FindMessageDll(langid);
        }
        if (!hModuleMessagesLocal) {
            langid = GetSystemDefaultLangID();
            hModuleMessagesLocal = FindMessageDll(langid);
        }

        // Next try current directory.
        if (!hModuleMessagesLocal) 
            hModuleMessagesLocal = FindMessageDll((LANGID)-1);

        // Try a fall-back list of locales.
        if (!hModuleMessagesLocal) {
            for (unsigned int i = 0; i < lengthof(g_fallbackLangs); ++i) {
                langid = g_fallbackLangs[i];
                hModuleMessagesLocal = FindMessageDll(langid);
                if (hModuleMessagesLocal)
                    break;
            }
        }

        if (hModuleMessagesLocal)
        {
            if (InterlockedCompareExchangePointer( (void**)&hModuleMessages, hModuleMessagesLocal, NULL)) {
                ASSERT(hModuleMessages != hModuleMessagesLocal);
                PAL_FreeSatelliteResource(hModuleMessagesLocal);
            } else
                ASSERT(hModuleMessagesLocal == hModuleMessages);
        }

    }
    return hModuleMessages;
}