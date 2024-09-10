HRESULT STDMETHODCALLTYPE CBandSiteBase::AddBand(IUnknown *punk)
{
    LONG                                    NewAllocated;
    struct BandObject                       *NewBand = NULL;
    CComPtr<IDeskBand>                      DeskBand;
    CComPtr<IObjectWithSite>                ObjWithSite;
    CComPtr<IOleWindow>                     OleWindow;
    CComPtr<IWinEventHandler>               WndEvtHandler;
    REBARBANDINFOW                          rbi;
    HRESULT                                 hRet;
    UINT                                    uBand;

    TRACE("(%p, %p)\n", this, punk);

    if (punk == NULL || fRebarWindow == NULL)
        return E_FAIL;

    hRet = punk->QueryInterface(IID_PPV_ARG(IDeskBand, &DeskBand));
    if (!SUCCEEDED(hRet) || DeskBand == NULL)
        goto Cleanup;
    hRet = punk->QueryInterface(IID_PPV_ARG(IObjectWithSite, &ObjWithSite));
    if (!SUCCEEDED(hRet) || ObjWithSite == NULL)
        goto Cleanup;
    hRet = punk->QueryInterface(IID_PPV_ARG(IOleWindow, &OleWindow));
    if (!SUCCEEDED(hRet) || OleWindow == NULL)
        goto Cleanup;
    hRet = punk->QueryInterface(IID_PPV_ARG(IWinEventHandler, &WndEvtHandler));
    if (!SUCCEEDED(hRet) || WndEvtHandler == NULL)
        goto Cleanup;

    hRet = S_OK;
    if (fBandsAllocated > fBandsCount)
    {
        /* Search for a free band object */
        for (INT i = 0; i < fBandsAllocated; i++)
        {
            if (fBands[i].DeskBand == NULL)
            {
                NewBand = &fBands[i];
                break;
            }
        }
    }
    else if (fBandsAllocated > 0)
    {
        ASSERT (fBands != NULL);

        /* Reallocate the band object array */
        NewAllocated = fBandsAllocated + 8;
        if (NewAllocated > 0xFFFF)
            NewAllocated = 0xFFFF;
        if (NewAllocated == fBandsAllocated)
        {
            hRet = E_OUTOFMEMORY;
            goto Cleanup;
        }


        NewBand = static_cast<struct BandObject *>(CoTaskMemAlloc(NewAllocated * sizeof(struct BandObject)));
        if (NewBand == NULL)
        {
            hRet = E_OUTOFMEMORY;
            goto Cleanup;
        }

        /* Copy the old array */
        memcpy(NewBand, fBands, fBandsAllocated * sizeof(struct BandObject));

        /* Initialize the added bands */
        memset(&NewBand[fBandsAllocated], 0, (NewAllocated - fBandsAllocated) * sizeof(struct BandObject));

        fBandsAllocated = NewAllocated;
        CoTaskMemFree(fBands);
        fBands = NewBand;
    }
    else
    {
        ASSERT(fBands == NULL);
        ASSERT(fBandsAllocated == 0);
        ASSERT(fBandsCount == 0);

        /* Allocate new array */
        fBands = static_cast<struct BandObject *>(CoTaskMemAlloc(8 * sizeof(struct BandObject)));
        if (fBands == NULL)
        {
            hRet = E_OUTOFMEMORY;
            goto Cleanup;
        }

        /* Initialize the added bands */
        memset(fBands, 0, 8 * sizeof(struct BandObject));

        fBandsAllocated += 8;
        NewBand = &fBands[0];
    }

    if (SUCCEEDED(hRet))
    {
        ASSERT(NewBand != NULL);

        fBandsCount++;
        NewBand->DeskBand = DeskBand.Detach();
        NewBand->OleWindow = OleWindow.Detach();
        NewBand->WndEvtHandler = WndEvtHandler.Detach();

        /* Create the ReBar band */
        hRet = ObjWithSite->SetSite(static_cast<IOleWindow *>(this));
        if (SUCCEEDED(hRet))
        {
            uBand = 0xffffffff;
            if (SUCCEEDED(UpdateSingleBand(NewBand)))
            {
                if (NewBand->dbi.dwMask & DBIM_MODEFLAGS)
                {
                    if (NewBand->dbi.dwModeFlags & DBIMF_ADDTOFRONT)
                        uBand = 0;
                }
            }

            BuildRebarBandInfo(NewBand, &rbi);

            if (SUCCEEDED(NewBand->OleWindow->GetWindow(&rbi.hwndChild)) &&
                rbi.hwndChild != NULL)
            {
                rbi.fMask |= RBBIM_CHILD;
                WARN ("ReBar band uses child window 0x%p\n", rbi.hwndChild);
            }

            if (!SendMessageW(fRebarWindow, RB_INSERTBANDW, (WPARAM)uBand, reinterpret_cast<LPARAM>(&rbi)))
                return E_FAIL;

            hRet = (HRESULT)((USHORT)GetBandID(NewBand));
        }
        else
        {
            WARN("IBandSite::AddBand(): Call to IDeskBand::SetSite() failed: %x\n", hRet);

            /* Remove the band from the ReBar control */
            BuildRebarBandInfo(NewBand, &rbi);
            uBand = (UINT)SendMessageW(fRebarWindow, RB_IDTOINDEX, (WPARAM)rbi.wID, 0);
            if (uBand != (UINT)-1)
            {
                if (!SendMessageW(fRebarWindow, RB_DELETEBAND, (WPARAM)uBand, 0))
                {
                    ERR("Failed to delete band!\n");
                }
            }
            else
                ERR("Failed to map band id to index!\n");

            FreeBand(NewBand);

            hRet = E_FAIL;
            /* goto Cleanup; */
        }
    }
Cleanup:
    return hRet;
}