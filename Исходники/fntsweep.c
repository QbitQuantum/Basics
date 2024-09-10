VOID vMoveFileFromSystemToFontsDir(WCHAR *pwcFile)
{
    WCHAR awcTmpBuf[MAX_PATH];
    WCHAR awcTmp[MAX_PATH];
    FLONG fl;
    WCHAR *pwcTmp;

#if DBG
    BOOL  bOk;
#endif

    if (bMakePathNameW(awcTmp, pwcFile,NULL, &fl))
    {
    // If the font is in the system subdirectory we will just move it
    // to the fonts subdirectory. The path in the registry is relative
    // and we will leave it alone.

        if
        (
            (fl & (FONT_IN_SYSTEM_DIR | FONT_RELATIVE_PATH)) ==
            (FONT_IN_SYSTEM_DIR | FONT_RELATIVE_PATH)
        )
        {
        // find the bare file part, this is what will be written
        // in the registry

            pwcTmp = &awcTmp[wcslen(awcTmp) - 1];
            while ((pwcTmp >= awcTmp) && (*pwcTmp != L'\\') && (*pwcTmp != L':'))
                pwcTmp--;

            if (pwcTmp > awcTmp)
                pwcTmp++;

        // need to move the font to fonts dir, can reuse the
        // buffer on the stack to build the full destination path

            wcscpy(awcTmpBuf, gpwcFontsDir);
            lstrcatW(awcTmpBuf, L"\\");
            lstrcatW(awcTmpBuf, pwcTmp);

        // note that MoveFile should succeed, for if there was
        // a font file of the same file name in %windir%\fonts dir
        // we would not have been in this code path.

            #if DBG
                bOk =
            #endif
                MoveFileW(awcTmp, awcTmpBuf);

            RIPMSG3(RIP_VERBOSE,
                    "move %ws to %ws %s",
                    awcTmp,
                    awcTmpBuf,
                    (bOk) ? "succeeded" : "failed");
        }
        #if DBG
        else
        {
            RIPMSG2(RIP_WARNING,
                    "File %ws not in system directory, fl = 0x%lx\n",
                    awcTmp, fl);
        }
        #endif

    }
    #if DBG
    else
    {
        RIPMSG1(RIP_WARNING, "Could not locate %ws", pwcFile);
    }
    #endif
}