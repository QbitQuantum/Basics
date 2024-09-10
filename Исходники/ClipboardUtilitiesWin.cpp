String getURL(IDataObject* dataObject, bool& success, String* title)
{
    STGMEDIUM store;
    String url;
    success = false;
    if (getWebLocData(dataObject, url, title)) {
        success = true;
        return url;
    } else if (SUCCEEDED(dataObject->GetData(urlWFormat(), &store))) {
        //URL using unicode
        UChar* data = (UChar*)GlobalLock(store.hGlobal);
        url = extractURL(String(data), title);
        GlobalUnlock(store.hGlobal);      
        ReleaseStgMedium(&store);
        success = true;
    } else if (SUCCEEDED(dataObject->GetData(urlFormat(), &store))) {
        //URL using ascii
        char* data = (char*)GlobalLock(store.hGlobal);
        url = extractURL(String(data), title);
        GlobalUnlock(store.hGlobal);      
        ReleaseStgMedium(&store);
        success = true;
    } else if (SUCCEEDED(dataObject->GetData(filenameWFormat(), &store))) {
        //file using unicode
        wchar_t* data = (wchar_t*)GlobalLock(store.hGlobal);
        if (data && data[0] && (PathFileExists(data) || PathIsUNC(data))) {
            RetainPtr<CFStringRef> pathAsCFString(AdoptCF, CFStringCreateWithCharacters(kCFAllocatorDefault, (const UniChar*)data, wcslen(data)));
            if (urlFromPath(pathAsCFString.get(), url)) {
                if (title)
                    *title = url;
                success = true;
            }
        }
        GlobalUnlock(store.hGlobal);      
        ReleaseStgMedium(&store);
    } else if (SUCCEEDED(dataObject->GetData(filenameFormat(), &store))) {
        //filename using ascii
        char* data = (char*)GlobalLock(store.hGlobal);       
        if (data && data[0] && (PathFileExistsA(data) || PathIsUNCA(data))) {
            RetainPtr<CFStringRef> pathAsCFString(AdoptCF, CFStringCreateWithCString(kCFAllocatorDefault, data, kCFStringEncodingASCII));
            if (urlFromPath(pathAsCFString.get(), url)) {
                if (title)
                    *title = url;
                success = true;
            }
        }
        GlobalUnlock(store.hGlobal);      
        ReleaseStgMedium(&store);
    }
    return url;
}