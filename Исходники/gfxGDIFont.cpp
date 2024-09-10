static PRBool
UseUniscribe(gfxTextRun *aTextRun,
             const PRUnichar *aString,
             PRUint32 aRunStart,
             PRUint32 aRunLength)
{
    PRUint32 flags = aTextRun->GetFlags();
    PRBool useGDI;

    PRBool isXP = (gfxWindowsPlatform::WindowsOSVersion() 
                       < gfxWindowsPlatform::kWindowsVista);

    // bug 561304 - Uniscribe bug produces bad positioning at certain
    // font sizes on XP, so default to GDI on XP using logic of 3.6

    useGDI = isXP &&
             (flags &
               (gfxTextRunFactory::TEXT_OPTIMIZE_SPEED | 
                gfxTextRunFactory::TEXT_IS_RTL)
             ) == gfxTextRunFactory::TEXT_OPTIMIZE_SPEED;

    return !useGDI ||
        ScriptIsComplex(aString + aRunStart, aRunLength, SIC_COMPLEX) == S_OK;
}