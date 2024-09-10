SCODE
S3C6410Disp::SetMode (INT modeId, HPALETTE *palette)
{
    SCODE scRet = S_OK;
	ULONG *gBitMasks;
	gBitMasks=DrvGetMasks(NULL);
    RETAILMSG(DISP_ZONE_ENTER, (_T("[DISPDRV] ++%s(%d)\n\r"), _T(__FUNCTION__), modeId));

    if (modeId == 0)
    {
        m_dwPhysicalModeID = m_pMode->modeId;

        // Create Palette
        if (palette)
        {
            *palette = EngCreatePalette(PAL_BITFIELDS, 0, NULL, gBitMasks[0], gBitMasks[1], gBitMasks[2]);
        }
    }
    else
    {
        RETAILMSG(DISP_ZONE_ERROR, (_T("[DISPDRV:ERR] %s() : modeId = %d, Driver Support Only Mode 0\n\r"), _T(__FUNCTION__), modeId));
        scRet = E_INVALIDARG;
    }

    RETAILMSG(DISP_ZONE_ENTER,(_T("[DISPDRV] --%s()\n\r"), _T(__FUNCTION__)));

    return scRet;
}