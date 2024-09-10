//
// FUNCTION: GetSettings()
//
// PURPOSE: Query all the related settings, and present them to the user.
//
void GetSettings(_In_ HWND hwndDlg)
{
    float  magnificationLevel;
    int    xOffset;
    int    yOffset;
    LPWSTR pszColorStatus = NULL;
    BOOL   fInputTransformEnabled = FALSE;
    RECT   rcInputTransformSource;
    RECT   rcInputTransformDest;

    // If any unexpected errors occur trying to get the current settings, present no settings data.
    bool fSuccess = true;

    // Get the current magnification level and offset.
    if (!MagGetFullscreenTransform(&magnificationLevel, &xOffset, &yOffset))
    {
        fSuccess = false;
    }

    if (fSuccess)
    {
        // Get the current color effect.
        MAGCOLOREFFECT magEffect;
        if (MagGetFullscreenColorEffect(&magEffect))
        {
            // Present friendly text relating to the color effect.
            if (memcmp(&g_MagEffectIdentity, &magEffect, sizeof(magEffect)) == 0)
            {
                pszColorStatus = L"Identity";
            }
            else if (memcmp(&g_MagEffectGrayscale, &magEffect, sizeof(magEffect)) == 0)
            {
                pszColorStatus = L"Grayscale";
            }
            else
            {
                // This would be an unexpected result from MagGetDesktopColorEffect()
                // given that the sample only sets the identity or grayscale effects.
                pszColorStatus = L"Unknown";
            }
        }
        else
        {
            fSuccess = false;
        }
    }

    if (fSuccess)
    {
        // Get the current input transform.
        if (!MagGetInputTransform(&fInputTransformEnabled, &rcInputTransformSource, &rcInputTransformDest))
        {
            fSuccess = false;
        }
    }

    // Present the results of all the calls above.
    WCHAR szMessage[256];

    if (fSuccess)
    {
        StringCchPrintf(szMessage, ARRAYSIZE(szMessage),
                        L"The current settings are:\r\n\r\nMagnification level: %f\r\nColor effect: %s\r\nInput transform state: %d",
                        magnificationLevel, pszColorStatus, fInputTransformEnabled);
    }
    else
    {
        DWORD dwErr = GetLastError();
        StringCchPrintf(szMessage, ARRAYSIZE(szMessage), L"Failed to get magnification setting. Error was %d", dwErr);
    }

    MessageBox(hwndDlg, szMessage, g_pszAppTitle, MB_OK);
}