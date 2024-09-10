HRESULT CMenuSFToolbar::FillToolbar(BOOL clearFirst)
{
    HRESULT hr;

    CComPtr<IEnumIDList> eidl;
    hr = m_shellFolder->EnumObjects(GetToolbar(), SHCONTF_FOLDERS | SHCONTF_NONFOLDERS, &eidl);
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    HDPA dpaSort = DPA_Create(10);

    LPITEMIDLIST item = NULL;
    hr = eidl->Next(1, &item, NULL);
    while (hr == S_OK)
    {
        if (m_menuBand->_CallCBWithItemPidl(item, 0x10000000, 0, 0) == S_FALSE)
        {
            DPA_AppendPtr(dpaSort, ILClone(item));
        }

        hr = eidl->Next(1, &item, NULL);
    }

    // If no items were added, show the "empty" placeholder
    if (DPA_GetPtrCount(dpaSort) == 0)
    {
        DPA_Destroy(dpaSort);
        return AddPlaceholder();
    }

    TRACE("FillToolbar added %d items to the DPA\n", DPA_GetPtrCount(dpaSort));

    DPA_Sort(dpaSort, PidlListSort, (LPARAM) m_shellFolder.p);

    for (int i = 0; i<DPA_GetPtrCount(dpaSort);)
    {
        PWSTR MenuString;

        INT index = 0;
        INT indexOpen = 0;

        STRRET sr = { STRRET_CSTR, { 0 } };

        item = (LPITEMIDLIST)DPA_GetPtr(dpaSort, i);

        hr = m_shellFolder->GetDisplayNameOf(item, SIGDN_NORMALDISPLAY, &sr);
        if (FAILED_UNEXPECTEDLY(hr))
        {
            DPA_Destroy(dpaSort);
            return hr;
        }

        StrRetToStr(&sr, NULL, &MenuString);

        index = SHMapPIDLToSystemImageListIndex(m_shellFolder, item, &indexOpen);

        LPCITEMIDLIST itemc = item;

        SFGAOF attrs = SFGAO_FOLDER;
        hr = m_shellFolder->GetAttributesOf(1, &itemc, &attrs);

        DWORD_PTR dwData = reinterpret_cast<DWORD_PTR>(item);

        // Fetch next item already, so we know if the current one is the last
        i++;

        AddButton(i, MenuString, attrs & SFGAO_FOLDER, index, dwData, i >= DPA_GetPtrCount(dpaSort));

        CoTaskMemFree(MenuString);
    }

    DPA_Destroy(dpaSort);
    return hr;
}