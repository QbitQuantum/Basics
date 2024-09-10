HRESULT create_uri(const WCHAR *url, IUri **uri)
{
    WCHAR fileUrl[INTERNET_MAX_URL_LENGTH];

    TRACE("%s\n", debugstr_w(url));

    if (!PathIsURLW(url))
    {
        WCHAR fullpath[MAX_PATH];
        DWORD needed = ARRAY_SIZE(fileUrl);

        if (!PathSearchAndQualifyW(url, fullpath, ARRAY_SIZE(fullpath)))
        {
            WARN("can't find path\n");
            return E_FAIL;
        }

        if (FAILED(UrlCreateFromPathW(fullpath, fileUrl, &needed, 0)))
        {
            ERR("can't create url from path\n");
            return E_FAIL;
        }
        url = fileUrl;
    }

    return CreateUri(url, Uri_CREATE_ALLOW_RELATIVE | Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME, 0, uri);
}