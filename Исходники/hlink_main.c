/***********************************************************************
 *             HlinkNavigateToStringReference (HLINK.@)
 */
HRESULT WINAPI HlinkNavigateToStringReference( LPCWSTR pwzTarget,
        LPCWSTR pwzLocation, IHlinkSite *pihlsite, DWORD dwSiteData,
        IHlinkFrame *pihlframe, DWORD grfHLNF, LPBC pibc,
        IBindStatusCallback *pibsc, IHlinkBrowseContext *pihlbc)
{
    HRESULT r;
    IHlink *hlink = NULL;

    FIXME("%s %s %p %08x %p %08x %p %p %p\n",
          debugstr_w(pwzTarget), debugstr_w(pwzLocation), pihlsite,
          dwSiteData, pihlframe, grfHLNF, pibc, pibsc, pihlbc);

    r = HlinkCreateFromString( pwzTarget, pwzLocation, NULL, pihlsite,
                               dwSiteData, NULL, &IID_IHlink, (LPVOID*) &hlink );
    if (SUCCEEDED(r))
        r = HlinkNavigate(hlink, pihlframe, grfHLNF, pibc, pibsc, pihlbc);

    return r;
}