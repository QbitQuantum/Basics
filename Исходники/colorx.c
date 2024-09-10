Cwt_Color cwt_stylex_colorByName(const CWT_CHAR *name)
{
    CwtStrNS *strNS = cwt_str_ns();
    CWT_CHAR *key;
    Cwt_Color *pcolor;

    CWT_ASSERT(name);
    key = strNS->strDup(name);
    strNS->toLowerStr(key, key, strNS->strLen(key));

    pcolor = (Cwt_Color*)hash_table_lookup(__cwt_color_table, key);

    CWT_FREE(key);

    if( NULL == pcolor ) {
        return (Cwt_Color)CWT_InvalidColor;
    }
    return *pcolor;
}