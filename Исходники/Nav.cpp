HRESULT CIEFrameAuto::Navigate(BSTR URL, VARIANT * Flags, VARIANT * TargetFrameName, VARIANT * PostData, VARIANT * Headers)
{
    HRESULT hres;
    LPITEMIDLIST pidl = NULL;
    CStubBindStatusCallback * pStubCallback = NULL;
    LPBINDCTX pBindCtx = NULL;
    // BUGBUG:: need to handle location and history...
    WCHAR wszPath[MAX_URL_STRING+2];  // note stomping below if changed to dynalloc
    SAFEARRAY * pPostDataArray = NULL;
    DWORD cbPostData = 0;
    LPCWSTR pwzHeaders = NULL;
    DWORD dwInFlags=0,dwFlags = 0;
    LPCBYTE pPostData = NULL;
    BOOL fOpenWithFrameName = FALSE;
    DWORD grBindFlags = 0;

    // get target frame name out of variant
    LPCWSTR pwzTargetFrameName = NULL;
    LPCWSTR pwzUnprefixedTargetFrameName = NULL;

    hres = E_FAIL;
    TraceMsg(TF_SHDAUTO, "Shell automation: CIEFrameAuto::Navigate %s called", URL);

    if (FAILED(hres))
    {
        hres = _PidlFromUrlEtc(CP_ACP, (LPCWSTR)URL, NULL, &pidl);

        if (FAILED(hres))
            goto exit;
    }

    // to perform the navigation, we either call an internal method
    // (_pbs->NavigateToPidl) or an external interface (IHlinkFrame::Navigate),
    // depending on what data we need to pass.  NavigateToPidl is faster
    // and cheaper, but does not allow us to pass headers or post data, just
    // the URL!  So what we do is call the fast and cheap way if only the URL
    // was specified (the 90% case), and if either headers or post data were
    // specified then we call the external interface.  We have to do a bunch
    // of wrapping of parameters in IMonikers and IHlinks and whatnot only to
    // unwrap them at the other end, so we won't call this unless we need to.

    // if we have either headers or post data or need to open the page in a
    // new window or pass HLNF_CREATENOHISTORY, we have to do the navigation
    // the hard way (through IHlinkFrame::Navigate) -- here we have to do
    // a bunch of wrapping of parameters into COM objects that IHlinkFrame::
    // Navigate wants.
    if (pwzHeaders || pPostData || dwFlags || grBindFlags) {
        // Check to see if this frame is offline.
        // This is the same as doing a get_Offline

        // BUGBUG rgardner Should use TO_VARIANT_BOOL
        VARIANT_BOOL vtbFrameIsOffline = m_bOffline ? TRUE : FALSE;
        VARIANT_BOOL vtbFrameIsSilent = m_bSilent ? TRUE : FALSE;

        // make a "stub" bind status callback to hold that data and pass it
        // to the URL moniker when requested
        hres=CStubBindStatusCallback_Create(pwzHeaders,pPostData,cbPostData,
            vtbFrameIsOffline, vtbFrameIsSilent, TRUE, grBindFlags, &pStubCallback);
        if (FAILED(hres))
            goto exit;

        // get the canonicalized name back out of the pidl.  Note this is
        // different than the URL passed in... it has been auto-protocol-ized,
        // canonicalized and generally munged in the process of creating the pidl,
        // which is what we want to use.
        hres = _pbs->IEGetDisplayName(pidl, wszPath, SHGDN_FORPARSING);
        if (FAILED(hres)) {
            TraceMsg(DM_ERROR, "CIEFrameAuto::Navigate _pbs->IEGetDisplayName failed %x", hres);
            goto exit;
        }

        WCHAR *pwzLocation = (WCHAR *)UrlGetLocationW(wszPath);

        if (pwzLocation)
        {
            //  NOTE: we allocated a extra char, just so we could do the following
            MoveMemory(pwzLocation+1, pwzLocation, (lstrlenW(pwzLocation)+1)*sizeof(WCHAR));
            *pwzLocation++ = TEXT('\0');   // we own wszPath, so we can do this.
        }

        // create a bind context to pass to IHlinkFrame::Navigate
        hres=CreateBindCtx(0,&pBindCtx);
        if (FAILED(hres))
            goto exit;

        // we have either post data or headers (or we need to open in a new window) to pass in addition
        // to URL
        // call IHlinkFrame::Navigate to do the navigation
        hres = NavigateHack(dwFlags,
                    pBindCtx,
                    pStubCallback,
                    fOpenWithFrameName ? pwzTargetFrameName:NULL,
                    wszPath,
                    pwzLocation);
    } else {
        ASSERT(dwFlags==0);
        //
        // NOTES: We used to call _pbs->NavigatePidl (in IE3.0), now we call
        // _psb->BrowseObject, so that we ALWAYS hit that code path.
        //
        hres = _BrowseObject(pidl, SBSP_SAMEBROWSER|SBSP_ABSOLUTE);
    }
}