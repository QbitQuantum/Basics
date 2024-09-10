HRESULT STDMETHODCALLTYPE CBandSiteMenu::QueryContextMenu(
    HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
    CComPtr<IPersist> pBand;
    CLSID BandCLSID;
    DWORD dwBandID;
    UINT idMax;

    TRACE("CBandSiteMenu::QueryContextMenu(%p, %p, %u, %u, %u, 0x%x)\n", this, hmenu, indexMenu, idCmdFirst, idCmdLast, uFlags);

    /* First Merge the menu with the available bands */
    idMax = Shell_MergeMenus(hmenu, m_hmenu, indexMenu, idCmdFirst, idCmdLast, MM_DONTREMOVESEPS | MM_SUBMENUSHAVEIDS);

    HMENU hmenuToolbars = GetSubMenu(hmenu, indexMenu);

    /* Enumerate all present bands and mark them as checked in the menu */
    for (UINT uBand = 0; SUCCEEDED(m_BandSite->EnumBands(uBand, &dwBandID)); uBand++)
    {
        if (FAILED(m_BandSite->GetBandObject(dwBandID, IID_PPV_ARG(IPersist, &pBand))))
            continue;

        if (FAILED_UNEXPECTEDLY(pBand->GetClassID(&BandCLSID)))
            continue;

        UINT menuID;
        if (IsEqualGUID(BandCLSID, CLSID_ISFBand))
        {
            menuID = _GetMenuIdFromISFBand(pBand);
            if (menuID == UINT_MAX)
            {
                HRESULT hr;
                hr = _AddISFBandToMenu(hmenuToolbars, 0, idCmdFirst, idCmdLast, pBand, dwBandID, &menuID);
                if (SUCCEEDED(hr) && menuID > idMax)
                    idMax = menuID;
                menuID -= idCmdFirst;
            }
        }
        else
        {
            int i = m_ComCatGuids.Find(BandCLSID);
            menuID = (i == -1 ? UINT_MAX : i + FIRST_COMCAT_MENU_ID);
        }

        if (menuID != UINT_MAX)
            CheckMenuItem(hmenuToolbars, menuID + idCmdFirst, MF_CHECKED);
    }

    return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(idMax - idCmdFirst +1)); 
}