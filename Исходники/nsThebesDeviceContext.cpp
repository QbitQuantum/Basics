nsThebesDeviceContext::nsThebesDeviceContext()
{
#ifdef PR_LOGGING
    if (!gThebesGFXLog)
        gThebesGFXLog = PR_NewLogModule("thebesGfx");
#endif

    PR_LOG(gThebesGFXLog, PR_LOG_DEBUG, ("#### Creating DeviceContext %p\n", this));

    mAppUnitsPerDevPixel = nscoord(-1);
    mAppUnitsPerInch = nscoord(-1);
    mAppUnitsPerDevNotScaledPixel = nscoord(-1);
    mPixelScale = 1.0f;

    mFontCache = nsnull;
    mWidget = nsnull;
    mFontAliasTable = nsnull;

#ifdef NS_DEBUG
    mInitialized = PR_FALSE;
#endif

    mDepth = 0;
    mWidth = 0;
    mHeight = 0;
    mPrintingScale = 1.0f;

#if defined(XP_WIN) && !defined(WINCE)
    SCRIPT_DIGITSUBSTITUTE sds;
    ScriptRecordDigitSubstitution(LOCALE_USER_DEFAULT, &sds);
#endif
}