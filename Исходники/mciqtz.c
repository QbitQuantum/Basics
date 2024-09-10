/***************************************************************************
 *                              MCIQTZ_mciOpen                  [internal]
 */
static DWORD MCIQTZ_mciOpen(UINT wDevID, DWORD dwFlags,
                            LPMCI_DGV_OPEN_PARMSW lpOpenParms)
{
    WINE_MCIQTZ* wma;
    HRESULT hr;
    DWORD style = 0;
    RECT rc = { 0, 0, 0, 0 };

    TRACE("(%04x, %08X, %p)\n", wDevID, dwFlags, lpOpenParms);

    wma = MCIQTZ_mciGetOpenDev(wDevID);
    if (!wma)
        return MCIERR_INVALID_DEVICE_ID;

    MCIQTZ_mciStop(wDevID, MCI_WAIT, NULL);

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    wma->uninit = SUCCEEDED(hr);

    hr = CoCreateInstance(&CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, &IID_IGraphBuilder, (LPVOID*)&wma->pgraph);
    if (FAILED(hr)) {
        TRACE("Cannot create filtergraph (hr = %x)\n", hr);
        goto err;
    }

    hr = IGraphBuilder_QueryInterface(wma->pgraph, &IID_IMediaControl, (LPVOID*)&wma->pmctrl);
    if (FAILED(hr)) {
        TRACE("Cannot get IMediaControl interface (hr = %x)\n", hr);
        goto err;
    }

    hr = IGraphBuilder_QueryInterface(wma->pgraph, &IID_IMediaSeeking, (void**)&wma->seek);
    if (FAILED(hr)) {
        TRACE("Cannot get IMediaSeeking interface (hr = %x)\n", hr);
        goto err;
    }

    hr = IGraphBuilder_QueryInterface(wma->pgraph, &IID_IMediaEvent, (void**)&wma->mevent);
    if (FAILED(hr)) {
        TRACE("Cannot get IMediaEvent interface (hr = %x)\n", hr);
        goto err;
    }

    hr = IGraphBuilder_QueryInterface(wma->pgraph, &IID_IVideoWindow, (void**)&wma->vidwin);
    if (FAILED(hr)) {
        TRACE("Cannot get IVideoWindow interface (hr = %x)\n", hr);
        goto err;
    }

    hr = IGraphBuilder_QueryInterface(wma->pgraph, &IID_IBasicVideo, (void**)&wma->vidbasic);
    if (FAILED(hr)) {
        TRACE("Cannot get IBasicVideo interface (hr = %x)\n", hr);
        goto err;
    }

    hr = IGraphBuilder_QueryInterface(wma->pgraph, &IID_IBasicAudio, (void**)&wma->audio);
    if (FAILED(hr)) {
        TRACE("Cannot get IBasicAudio interface (hr = %x)\n", hr);
        goto err;
    }

    if (!(dwFlags & MCI_OPEN_ELEMENT) || (dwFlags & MCI_OPEN_ELEMENT_ID)) {
        TRACE("Wrong dwFlags %x\n", dwFlags);
        goto err;
    }

    if (!lpOpenParms->lpstrElementName || !lpOpenParms->lpstrElementName[0]) {
        TRACE("Invalid filename specified\n");
        goto err;
    }

    TRACE("Open file %s\n", debugstr_w(lpOpenParms->lpstrElementName));

    hr = IGraphBuilder_RenderFile(wma->pgraph, lpOpenParms->lpstrElementName, NULL);
    if (FAILED(hr)) {
        TRACE("Cannot render file (hr = %x)\n", hr);
        goto err;
    }

    IVideoWindow_put_AutoShow(wma->vidwin, OAFALSE);
    IVideoWindow_put_Visible(wma->vidwin, OAFALSE);
    if (dwFlags & MCI_DGV_OPEN_WS)
        style = lpOpenParms->dwStyle;
    if (dwFlags & MCI_DGV_OPEN_PARENT) {
        IVideoWindow_put_MessageDrain(wma->vidwin, (OAHWND)lpOpenParms->hWndParent);
        IVideoWindow_put_WindowState(wma->vidwin, SW_HIDE);
        IVideoWindow_put_WindowStyle(wma->vidwin, style|WS_CHILD);
        IVideoWindow_put_Owner(wma->vidwin, (OAHWND)lpOpenParms->hWndParent);
        GetClientRect(lpOpenParms->hWndParent, &rc);
        IVideoWindow_SetWindowPosition(wma->vidwin, rc.left, rc.top, rc.right - rc.top, rc.bottom - rc.top);
        wma->parent = (HWND)lpOpenParms->hWndParent;
    }
    else if (style)
        IVideoWindow_put_WindowStyle(wma->vidwin, style);
    IBasicVideo_GetVideoSize(wma->vidbasic, &rc.right, &rc.bottom);
    wma->opened = TRUE;

    if (dwFlags & MCI_NOTIFY)
        mciDriverNotify(HWND_32(LOWORD(lpOpenParms->dwCallback)), wDevID, MCI_NOTIFY_SUCCESSFUL);

    return 0;

err:
    if (wma->audio)
        IBasicAudio_Release(wma->audio);
    wma->audio = NULL;
    if (wma->vidbasic)
        IBasicVideo_Release(wma->vidbasic);
    wma->vidbasic = NULL;
    if (wma->seek)
        IMediaSeeking_Release(wma->seek);
    wma->seek = NULL;
    if (wma->vidwin)
        IVideoWindow_Release(wma->vidwin);
    wma->vidwin = NULL;
    if (wma->pgraph)
        IGraphBuilder_Release(wma->pgraph);
    wma->pgraph = NULL;
    if (wma->mevent)
        IMediaEvent_Release(wma->mevent);
    wma->mevent = NULL;
    if (wma->pmctrl)
        IMediaControl_Release(wma->pmctrl);
    wma->pmctrl = NULL;

    if (wma->uninit)
        CoUninitialize();
    wma->uninit = FALSE;

    return MCIERR_INTERNAL;
}