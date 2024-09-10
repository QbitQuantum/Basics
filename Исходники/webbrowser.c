BOOL InitWebBrowser(HHInfo *info, HWND hwndParent)
{
    WebBrowserContainer *container;
    IOleInPlaceObject *inplace;
    HRESULT hr;
    RECT rc;

    container = heap_alloc_zero(sizeof(*container));
    if (!container)
        return FALSE;

    container->IOleClientSite_iface.lpVtbl = &OleClientSiteVtbl;
    container->IOleInPlaceSite_iface.lpVtbl = &OleInPlaceSiteVtbl;
    container->IOleInPlaceFrame_iface.lpVtbl = &OleInPlaceFrameVtbl;
    container->IDocHostUIHandler_iface.lpVtbl = &DocHostUIHandlerVtbl;
    container->ref = 1;
    container->hwndWindow = hwndParent;

    info->web_browser = container;

    hr = OleCreate(&CLSID_WebBrowser, &IID_IOleObject, OLERENDER_DRAW, 0,
                   &container->IOleClientSite_iface, &MyIStorage,
                   (void **)&container->ole_obj);

    if (FAILED(hr)) goto error;

    GetClientRect(hwndParent, &rc);

    hr = OleSetContainedObject((struct IUnknown *)container->ole_obj, TRUE);
    if (FAILED(hr)) goto error;

    hr = IOleObject_DoVerb(container->ole_obj, OLEIVERB_SHOW, NULL,
                           &container->IOleClientSite_iface, -1, hwndParent, &rc);
    if (FAILED(hr)) goto error;

    hr = IOleObject_QueryInterface(container->ole_obj, &IID_IOleInPlaceObject, (void**)&inplace);
    if (FAILED(hr)) goto error;

    IOleInPlaceObject_SetObjectRects(inplace, &rc, &rc);
    IOleInPlaceObject_Release(inplace);

    hr = IOleObject_QueryInterface(container->ole_obj, &IID_IWebBrowser2, (void **)&container->web_browser);
    if (SUCCEEDED(hr))
        return TRUE;

error:
    ReleaseWebBrowser(info);
    return FALSE;
}