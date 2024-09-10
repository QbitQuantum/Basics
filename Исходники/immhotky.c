VOID CliGetPreloadKeyboardLayouts(FE_KEYBOARDS* pFeKbds)
{
    UINT  i;
    WCHAR szPreLoadee[4];   // up to 999 preloads
    WCHAR lpszName[KL_NAMELENGTH];
    UNICODE_STRING UnicodeString;
    HKL hkl;

    for (i = 1; i < 1000; i++) {
        wsprintf(szPreLoadee, L"%d", i);
        if ((GetPrivateProfileStringW(
                 L"Preload",
                 szPreLoadee,
                 L"",                            // default = NULL
                 lpszName,                       // output buffer
                 KL_NAMELENGTH,
                 L"keyboardlayout.ini") == -1 ) || (*lpszName == L'\0')) {
            break;
        }
        RtlInitUnicodeString(&UnicodeString, lpszName);
        RtlUnicodeStringToInteger(&UnicodeString, 16L, (PULONG)&hkl);

        RIPMSG2(RIP_VERBOSE, "PreLoaded HKL(%d): %08X\n", i, hkl);

        //
        // Set language flags. By its definition, LOWORD(hkl) is LANGID
        //
        SetFeKeyboardFlags(LOWORD(HandleToUlong(hkl)), pFeKbds);
    }
}