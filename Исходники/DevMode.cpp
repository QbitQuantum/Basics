HRESULT hrOEMDevMode(DWORD dwMode, POEMDMPARAM pOemDMParam)
{
    HRESULT hResult     = S_OK;
    POEMDEV pOEMDevIn   = NULL;
    POEMDEV pOEMDevOut  = NULL;


    // Verify parameters.
    if( (NULL == pOemDMParam)
        ||
        ( (OEMDM_SIZE != dwMode)
          &&
          (OEMDM_DEFAULT != dwMode)
          &&
          (OEMDM_CONVERT != dwMode)
          &&
          (OEMDM_MERGE != dwMode)
        )
      )
    {
        ERR(DLLTEXT("DevMode() ERROR_INVALID_PARAMETER.\r\n"));

        SetLastError(ERROR_INVALID_PARAMETER);
        return E_FAIL;
    }

    // Cast generic (i.e. PVOID) to OEM private devomode pointer type.
    pOEMDevIn = (POEMDEV) pOemDMParam->pOEMDMIn;
    pOEMDevOut = (POEMDEV) pOemDMParam->pOEMDMOut;

    switch(dwMode)
    {
        case OEMDM_SIZE:
            pOemDMParam->cbBufSize = sizeof(OEMDEV);
            break;

        case OEMDM_DEFAULT:
            pOEMDevOut->dmOEMExtra.dwSize       = sizeof(OEMDEV);
            pOEMDevOut->dmOEMExtra.dwSignature  = OEM_SIGNATURE;
            pOEMDevOut->dmOEMExtra.dwVersion    = OEM_VERSION;
            pOEMDevOut->bEnabled                = WATER_MARK_DEFAULT_ENABLED;
            pOEMDevOut->dfRotate                = WATER_MARK_DEFAULT_ROTATION;
            pOEMDevOut->dwFontSize              = WATER_MARK_DEFAULT_FONTSIZE;
            pOEMDevOut->crTextColor             = WATER_MARK_DEFAULT_COLOR;
            hResult = StringCbCopyW(pOEMDevOut->szWaterMark, sizeof(pOEMDevOut->szWaterMark), WATER_MARK_DEFAULT_TEXT);
            break;

        case OEMDM_CONVERT:
            ConvertOEMDevmode(pOEMDevIn, pOEMDevOut);
            break;

        case OEMDM_MERGE:
            ConvertOEMDevmode(pOEMDevIn, pOEMDevOut);
            MakeOEMDevmodeValid(pOEMDevOut);
            break;
    }

    return hResult;
}