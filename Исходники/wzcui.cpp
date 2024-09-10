static HRESULT PopulateNetworkList(PWLAN_INFO psInfo)
{
    HRESULT hr = S_OK;
    LPCTSTR pszConnected, pszConnecting, pszAvailable, pszUnavailable;
    LV_ITEM lv = { 0 };
    UINT    i, cConfigs;
    BOOL    fNetAvailable = FALSE;

    CBREx(psInfo, E_INVALIDARG);

    // Load strings
    pszConnected = (LPCTSTR)LoadString(HINST_RESDLL, IDS_WZC_ACTIVE, NULL, 0);
    CBRA(NULL != pszConnected);

    pszConnecting = (LPCTSTR)LoadString(HINST_RESDLL, IDS_WZC_CONNECTING, NULL, 0);
    CBRA(NULL != pszConnecting);

    pszAvailable = (LPCTSTR)LoadString(HINST_RESDLL, IDS_WZC_AIRING, NULL, 0); 
    CBRA(NULL != pszAvailable);

    pszUnavailable = (LPCTSTR)LoadString(HINST_RESDLL, IDS_WZC_SILENT, NULL, 0); 
    CBRA(NULL != pszUnavailable);

    // Add the first setting item
    hr = InsertFirstSettingsItem(psInfo);
    CHR(hr);

    // Get the network list
    hr = SHWZCGetAllNetworks(psInfo->hshwzc, &psInfo->hdsaNetworks);
    CHR(hr);

    // Are there any items?
    cConfigs = DSA_GetItemCount(psInfo->hdsaNetworks);
    CBREx(0 != cConfigs, S_FALSE);
    ListView_SetItemCount(psInfo->hwndNetList, cConfigs + 1);

    // Add the networks to the list
    for (i = 0; i != cConfigs; ++i)
    {
        PCSHWZCNET pwzcnet = (PSHWZCNET)DSA_GetItemPtr(psInfo->hdsaNetworks, i);
        BOOL       fAdhoc = (SHWZCF_NET_ADHOC & pwzcnet->dwFlags);
        BOOL       fSecure;
        LPCTSTR    pszDesc;
        int        nIndex;
        BOOL       fUseSignalStrength = FALSE;

        // If this network is AP, mark it
        if (FALSE == fAdhoc)
        {
            psInfo->fAPAir = TRUE;
            fUseSignalStrength = TRUE;
        }

        // network is considered secure if it's 802.1x, or not OPEN and without
        // encryption enabled
        fSecure = BOOLIFY(pwzcnet->dwFlags & SHWZCF_NET_8021X) ||
            !( ( (Ndis802_11Encryption1Enabled != pwzcnet->dwEncryptionType) &&
            (Ndis802_11Encryption2Enabled != pwzcnet->dwEncryptionType) &&
            (Ndis802_11Encryption3Enabled != pwzcnet->dwEncryptionType) ) &&
            (Ndis802_11AuthModeOpen == pwzcnet->dwAuthentication) );

        // Get the icon and the description for the network
        if (SHWZCF_NET_CONNECTED & pwzcnet->dwFlags)
        {
            lv.iImage = fAdhoc ? WZCIMG_ADHOC_ACTIVE : 0;
            pszDesc = pszConnected;
        }
        else if (SHWZCF_NET_CONNECTING & pwzcnet->dwFlags)
        {
            lv.iImage = fAdhoc ? WZCIMG_ADHOC_AIRING : 0;
            pszDesc = pszConnecting;
        }
        else if (SHWZCF_NET_BROADCAST & pwzcnet->dwFlags)
        {
            lv.iImage = fAdhoc ? WZCIMG_ADHOC_AIRING : 0;
            pszDesc = pszAvailable;
        }
        else
        {
            ASSERT(SHWZCF_NET_PREFERRED & pwzcnet->dwFlags);
            lv.iImage = fAdhoc ? WZCIMG_ADHOC_SILENT : WZCIMG_INFRA_SILENT;

            pszDesc = pszUnavailable;
            // no need to get signal strength
            fUseSignalStrength = FALSE;
        }

        if (SHWZCF_NET_BROADCAST & pwzcnet->dwFlags)
        {
            fNetAvailable = TRUE;
        }

        // Update the icon to have signal strength if we're in Infrastructure mode
        if (fUseSignalStrength)
        {
            UINT uiStrength = pwzcnet->nRssi;

            if (uiStrength)
            {
                lv.iImage = WZCIMG_SIGNAL_1 + uiStrength - 1;
                if (fSecure)
                {
                    lv.iImage += WZCIMG_SIGNAL_SECURE_1 - WZCIMG_SIGNAL_1;
                }
            }
            else
            {
                lv.iImage = WZCIMG_INFRA_SILENT;
            }
        }

        ASSERT(lv.iImage);

        // Insert the item into the listview
        lv.mask     = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
        lv.iItem    = i;
        lv.iSubItem = 0;
        lv.pszText  = (LPTSTR)pwzcnet->szName;
        lv.lParam   = (LPARAM)pwzcnet;

        nIndex = ListView_InsertItem(psInfo->hwndNetList, &lv);
        CBR(0 <= nIndex);

        // Set the state text
        lv.mask     = LVIF_TEXT;
        lv.iItem    = nIndex;
        lv.iSubItem = 1;
        lv.pszText  = (LPTSTR)pszDesc;

        CBR(ListView_SetItem(psInfo->hwndNetList, &lv));
    }

    // Sort the networks
    CBREx(ListView_SortItems(psInfo->hwndNetList, CompareNetworks, NULL), E_OUTOFMEMORY);

Error:

    if(psInfo)
    {
        SetCursor(psInfo->hOldCursor);
        psInfo->hOldCursor = NULL;

        // We just turned power on, but didn't find any broadcasting networks
        if((psInfo->bUserInitiatedSearch) && (!fNetAvailable) && (psInfo->dwHWFlags & SHWZCF_HW_ON))
        {
            psInfo->bUserInitiatedSearch = FALSE;
            SH_BOXEX sbex = {0};
            sbex.cbSize = sizeof(sbex);
            sbex.dwStyle = SHBEXF_CLOSE_ON_ACTIVATION_LOSS|SHBEXF_SUPRESS_DEFAULT_SOUND;
            sbex.nTimeOut = 0;
            sbex.hwndOwner = psInfo->hDlg;
            sbex.sbextype = sbextTextBox;
            sbex.info.ti.pszText = LoadStringEtc(HINST_RESDLL, IDS_WZC_WIFI_SEARCH_ERROR, NULL);
            sbex.info.ti.bi.cButtons = 1;
            
            SHBoxEx(&sbex);
        }

        psInfo->bUserInitiatedSearch = FALSE;
    }
    
    return hr;
}