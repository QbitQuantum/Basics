HRESULT CKhParser::GetNextHomonym( SAFEARRAY** lpHomonym )
{
    if (currHom == -1)
        return S_OK;
    std::wstring str;
    if (currHom < homonyms.size())
        str = homonyms[currHom].khak;
    else
        str = homonyms[currHom % homonyms.size()].rus;

    long idx, len, start;
    len = (long)str.length();
    SafeArrayLock(*lpHomonym);

    SafeArrayGetUBound(*lpHomonym, 1, &len);
    SafeArrayGetLBound(*lpHomonym, 1, &start);
    short asterisk = L'*';
    for (idx = start; idx < len; idx ++) {
        if (idx == str.length()) {
//        if (str[idx] == 0x0) {
            SafeArrayPutElement(*lpHomonym, &idx, &asterisk);
            break;
        }
        SafeArrayPutElement(*lpHomonym, &idx, &str[ idx ]);
    }
    SafeArrayUnlock(*lpHomonym);

    currHom++;

    return S_OK;
}