BOOL RtlWCSMessageWParamCharToMB(DWORD msg, WPARAM *pWParam)
{
    DWORD dwAnsi;
    NTSTATUS Status;
    WORD CodePage;
    int nbWch;

#ifdef FE_SB // RtlWCSMessageWParamCharToMB()
    //
    // Format of *pWParam here...
    //
    // LOWORD(*pWParam) = Unicode CodePoint...
    // HIWORD(*pWParam) = Has some information for DBCS messaging
    //                    (ex. WPARAM_IR_DBCSCHAR)
    //
    // Then we need to convert ONLY loword of wParam to Unicode...
    //
#endif // FE_SB
#ifndef FE_SB
    // NtBug #3135 (Closed 02/04/93)
    // Publisher Posts WM_CHAR messages with wParam > 0xFF (not a valid ANSI char)!
    //
    // It does this to disable TranslateAccelerator for that char.
    // MSPub's winproc must get the non-ANSI 'character' value, so PostMessage must
    // translate *two* characters of wParam for character messages, and PeekMessage
    // must translate *two* Unicode chars of wParam for ANSI app.
#endif

    /*
     * Only these messages have CHARs: others are passed through
     */

    switch(msg) {
#ifdef FE_IME // RtlWCSMessageWParamCharToMB()
    case WM_IME_CHAR:
    case WM_IME_COMPOSITION:
#endif // FE_IME
    case WM_CHAR:
    case WM_CHARTOITEM:
    case EM_SETPASSWORDCHAR:
    case WM_DEADCHAR:
    case WM_SYSCHAR:
    case WM_SYSDEADCHAR:
    case WM_MENUCHAR:

        CodePage = THREAD_CODEPAGE();
        dwAnsi = 0;

        nbWch = IS_DBCS_ENABLED() ? 1 * sizeof(WCHAR) : 2 * sizeof(WCHAR);

        if (IS_ACP(CodePage)) {
            // HACK HACK HACK HACK (for NtBug #3135)
            // to allow applications that store data in high word of wParam
            // Jan/06/96 hiroyama
            Status = RtlUnicodeToMultiByteN((LPSTR)&dwAnsi, sizeof(dwAnsi),
                    NULL, (LPWSTR)pWParam, nbWch);
            if (!NT_SUCCESS(Status)) {
                // LATER IanJa: returning FALSE makes GetMessage fail, which
                // terminates the app.  We should use some default 'bad character'
                // I use 0x00 for now.
                *pWParam = 0x00;
                return TRUE;
            }
        } else {
            int cwch;
            // assuming little endian
#ifdef _USERK_
            cwch = EngWideCharToMultiByte(CodePage,
                    (LPWSTR)pWParam, nbWch,
                    (LPSTR)&dwAnsi, sizeof(dwAnsi));
#else
            cwch = WideCharToMultiByte(CodePage, 0,
                    (LPCWSTR)pWParam, nbWch / sizeof(WCHAR),
                    (LPSTR)&dwAnsi, sizeof(dwAnsi), NULL, NULL);
#endif // _USERK_
            // KdPrint(("0x%04x -> 0x%02x (%d)\n", *pWParam, dwAnsi, CodePage));
            if (cwch == 0) {
                *pWParam = 0x00;
                return TRUE;
            }
        }
        if (IS_DBCS_ENABLED()) {
            WORD wAnsi = LOWORD(dwAnsi);
            //
            // From:
            //   HIBYTE(wAnsi)            = Dbcs TrailingByte.
            //   LOBYTE(wAnsi)            = Dbcs LeadingByte or Sbcs character.
            //
            // To:
            //   HIWORD(*pWParam)         = Original Data (information for DBCS messgaing).
            //   HIBYTE(LOWORD(*pWParam)) = Dbcs LeadingByte Byte.
            //   LOBYTE(LOWORD(*pWParam)) = Dbcs TrailingByte or Sbcs character.
            //
            if (IS_DBCS_MESSAGE(wAnsi)) {
                //
                // It's a DBCS character.
                //
                *pWParam = MAKEWPARAM(MAKEWORD(HIBYTE(wAnsi),LOBYTE(wAnsi)),HIWORD(*pWParam));
            } else {
                //
                // It's a SBCS character.
                //
                *pWParam = MAKEWPARAM(MAKEWORD(LOBYTE(wAnsi),0),0);
            }
        } else {
#if DBG
            if ((dwAnsi == 0) || (dwAnsi > 0xFF)) {
                RIPMSG1(RIP_VERBOSE, "msgW -> msgA: char = 0x%.4lX\n", dwAnsi);
            }
#endif
            *pWParam = dwAnsi;
        }
        break;
    }

    return TRUE;
}