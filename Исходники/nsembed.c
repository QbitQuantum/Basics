static nsresult NSAPI nsURIContentListener_OnStartURIOpen(nsIURIContentListener *iface,
                                                          nsIURI *aURI, PRBool *_retval)
{
    NSContainer *This = NSURICL_THIS(iface);
    nsIWineURI *wine_uri;
    nsACString spec_str;
    const char *spec;
    nsresult nsres;

    nsACString_Init(&spec_str, NULL);
    nsIURI_GetSpec(aURI, &spec_str);
    nsACString_GetData(&spec_str, &spec, NULL);

    TRACE("(%p)->(%p(%s) %p)\n", This, aURI, debugstr_a(spec), _retval);

    nsACString_Finish(&spec_str);

    nsres = nsIURI_QueryInterface(aURI, &IID_nsIWineURI, (void**)&wine_uri);
    if(NS_FAILED(nsres)) {
        WARN("Could not get nsIWineURI interface: %08lx\n", nsres);
        return NS_ERROR_NOT_IMPLEMENTED;
    }

    nsIWineURI_SetNSContainer(wine_uri, This);

    if(This->bscallback && This->bscallback->mon) {
        LPWSTR url;
        HRESULT hres;

        hres = IMoniker_GetDisplayName(This->bscallback->mon, NULL, 0, &url);
        if(SUCCEEDED(hres)) {
            IMoniker *mon = NULL;

            hres = CreateURLMoniker(NULL, url, &mon);
            if(SUCCEEDED(hres)) {
                nsIWineURI_SetMoniker(wine_uri, mon);
                IMoniker_Release(mon);
            }else {
                WARN("CreateURLMoniker failed: %08lx\n", hres);
            }
        }else {
            WARN("GetDisplayName failed: %08lx\n", hres);
        }
    }

    nsIWineURI_Release(wine_uri);

    return NS_ERROR_NOT_IMPLEMENTED;
}