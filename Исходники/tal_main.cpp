LPCSTRINGTEMPLATE TaLocale_GetStringResource (int ids, HINSTANCE *phInstFound)
{
    // Strings are organized into heaps of String Tables, each table
    // holding 16 strings (regardless of their length). The first table's
    // first string index is for string #1. When searching for a string,
    // the string's table is the index given to FindResource.
    //
    LPCSTRINGTEMPLATE pst = NULL;
    LANGID lang = TaLocale_GetLanguage();

    int iTable = (ids / 16) + 1;           // 1 = first string table
    int iIndex = ids - ((iTable-1) * 16);  // 0 = first string in the table

    HINSTANCE hInstance = NULL;
	size_t iModule = 0;
    for (; !pst && TaLocale_EnumModule (iModule, &hInstance); ++iModule)
    {
        HRSRC hr;
        if ((hr = FindResourceEx (hInstance, RT_STRING, MAKEINTRESOURCE( iTable ), lang)) == NULL)
        {
            // Our translation teams don't usually change the language
            // constants within .RC files, so we should look for English
            // language translations too.
            //
            if ((hr = FindResourceEx (hInstance, RT_STRING, MAKEINTRESOURCE( iTable ), MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US))) == NULL)
            {
                // If we still can't find it, we'll take anything...
                //
                if ((hr = FindResource (hInstance, RT_STRING, MAKEINTRESOURCE( iTable ))) == NULL)
                    continue;
            }
        }

        HGLOBAL hg;
        if ((hg = LoadResource (hInstance, hr)) != NULL)
        {
            const WORD *pTable;
            if     ((pTable = (WORD*)LockResource (hg)) != NULL)
            {
                try {
                    // Skip words in the string table until we reach the string
                    // index we're looking for.
                    //
                    for (int iIndexWalk = iIndex; iIndexWalk && ((LPCSTRINGTEMPLATE)pTable)->cchString; --iIndexWalk) {
                        pTable += 1 + ((LPCSTRINGTEMPLATE)pTable)->cchString;
                    }

                    if (IsValidStringTemplate ((LPCSTRINGTEMPLATE)pTable))
                    {
                        pst = (LPCSTRINGTEMPLATE)pTable;
                        if (phInstFound)
                            *phInstFound = hInstance;
                    } else {
                        UnlockResource(pTable);
                        FreeResource(hg);
                    }
                }
                catch(...)
                {
                    UnlockResource(pTable);
                    FreeResource(hg);
                    // If we walked off the end of the table, then the
                    // string we want just wasn't there.
                }
            }
        }
    }

    return pst;
}