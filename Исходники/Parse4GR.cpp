static bool XML_GetTupel(cgMSXML::IXMLElement* pElem, const wchar_t* pszAttrName, long* pa, long* pb)
{
    VARIANT     val;
    wchar_t*    pszEnd; 
    bool        bOk = true;
    long         a;
    long         b;

    VariantInit(&val);

    if(FAILED(pElem->getAttribute((wchar_t*)/*cast ok?*/pszAttrName, &val)) || val.vt!=VT_BSTR)
        return false;

    a = wcstol(val.bstrVal, &pszEnd, 10);
    if(pa)
        *pa = a;

    while(iswspace(*pszEnd))
        pszEnd++;

    if(*pszEnd == L';')
        pszEnd++;
    else
        bOk = false;

    b = wcstol(pszEnd, &pszEnd, 10);
    if(pb)
        *pb = b;

    while(iswspace(*pszEnd))
        pszEnd++;

    if(*pszEnd)
        bOk = false;

    VariantClear(&val);
    return bOk;
}