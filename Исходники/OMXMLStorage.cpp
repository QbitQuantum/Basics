OMUniqueObjectIdentification 
OMXMLStorage::getMetaDefIdFromQSymbol(const wchar_t* qSymbol) const
{
    TRACE("OMXMLStorage::getMetaDefIdFromQSymbol");
    
    // if the qSymbol refers to a non-baseline metadef then it
    // must be in the qSymbolMap; otherwise it is a baseline qSymbol
    OMUniqueObjectIdentification id = _metaDefIdMap.getId(qSymbol);
    if (id == nullOMUniqueObjectIdentification)
    {
        // support qualified baseline symbols
        // users __should__ use just the symbol for baseline metadefs
        const wchar_t* spc = wmemchr(qSymbol, L' ', wcslen(qSymbol));
        ASSERT("Valid QSymbol has space", spc != 0);
        id = getBaselineMetaDefId(spc + 1);
    }
    
    return id;
}