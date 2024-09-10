void AppActivate(BOOL fActive)
/****************************************************************************
*
* Function:     AppActivate
* Parameters:   fActive - True if app is activating
*
* Description:  If the application is activating, then swap the system
*               into SYSPAL_NOSTATIC mode so that our palettes will display
*               correctly.
*
****************************************************************************/
{
    HDC hdc = GetDC(NULL);

    if (fActive && (GetSystemPaletteUse(hdc) == SYSPAL_STATIC)) {
        /* Switch to SYSPAL_NOSTATIC */
        SetSystemPaletteUse(hdc, SYSPAL_NOSTATIC);
        }
    else if (!fActive) {
        /* Always switch back to SYSPAL_STATIC */
        SetSystemPaletteUse(hdc, SYSPAL_STATIC);
        }
    ReleaseDC(NULL,hdc);
}