bstr_t CCommonUtils::GetUrlHostName(LPCSTR lpURL)
{
    bstr_t lpRet = L"";
    URL_COMPONENTSA urlComponents = {0};
    
    urlComponents.dwStructSize = sizeof(urlComponents);
    urlComponents.lpszHostName = (LPSTR)malloc(strlen(lpURL)+1);
    urlComponents.dwHostNameLength = strlen(lpURL)+1;
    if(InternetCrackUrlA(lpURL, 0, 0, &urlComponents))
    {
        lpRet = urlComponents.lpszHostName;		
    }

    free(urlComponents.lpszHostName);	

    return lpRet;
}