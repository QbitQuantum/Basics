////////////////////////////////////////////////////////////////////////////////
//
// OptItems call back for OEM device or document property UI.
//
LONG APIENTRY OEMUICallBack(PCPSUICBPARAM pCallbackParam, POEMCUIPPARAM pOEMUIParam)
{
    LONG    lReturn = CPSUICB_ACTION_NONE;
    POEMDEV pOEMDev = (POEMDEV) pOEMUIParam->pOEMDM;


    VERBOSE(DLLTEXT("OEMUICallBack() entry.\r\n"));

    switch(pCallbackParam->Reason)
    {
        case CPSUICB_REASON_APPLYNOW:
            // Store OptItems state in DEVMODE.
            pOEMDev->bEnabled = !pOEMUIParam->pOEMOptItems[0].Sel;
            if(FAILED(StringCbCopyW(pOEMDev->szWaterMark, sizeof(pOEMDev->szWaterMark), (LPWSTR)pOEMUIParam->pOEMOptItems[1].pSel)))
            {
                ERR(DLLTEXT("OEMUICallBack() failed to copy water mark text\r\n"));
            }
            pOEMDev->dwFontSize = FontIndexToSize(pOEMUIParam->pOEMOptItems[2].Sel);
            pOEMDev->dfRotate = (DOUBLE) pOEMUIParam->pOEMOptItems[3].Sel;
            pOEMDev->crTextColor = IndexToTextColor(pOEMUIParam->pOEMOptItems[4].Sel);
            break;

        default:
            break;
    }

    return lReturn;
}