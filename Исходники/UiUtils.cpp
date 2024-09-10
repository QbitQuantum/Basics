bool ParseSizeString(LPCWSTR lpszSize, CUISize& Size)
{
    LPWSTR pstr = NULL;
    
    //
    // parse x
    //

    Size.cx = wcstol(lpszSize, &pstr, 10);
    if (pstr == NULL && *pstr != L','){
        return false;
    }

    //
    // parse y
    //

    Size.cy = wcstol(pstr + 1, &pstr, 10);
    if (pstr == NULL){
        return false;
    }

    return true;
}