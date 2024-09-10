/**************************************************************************
 * StringTableAddString [SETUPAPI.@]
 *
 * Adds a new string to the string table.
 *
 * PARAMS
 *     hStringTable [I] Handle to the string table
 *     lpString     [I] String to be added to the string table
 *     dwFlags      [I] Flags
 *                        1: case sensitive compare
 *
 * RETURNS
 *     Success: String ID
 *     Failure: -1
 *
 * NOTES
 *     If the given string already exists in the string table it will not
 *     be added again. The ID of the existing string will be returned in
 *     this case.
 */
DWORD WINAPI
StringTableAddString(HSTRING_TABLE hStringTable,
                     LPWSTR lpString,
                     DWORD dwFlags)
{
    PSTRING_TABLE pStringTable;
    DWORD i;

    TRACE("%p %s %lx\n", hStringTable, debugstr_w(lpString), dwFlags);

    pStringTable = (PSTRING_TABLE)hStringTable;
    if (pStringTable == NULL)
    {
        ERR("Invalid hStringTable!\n");
        return (DWORD)-1;
    }

    /* Search for existing string in the string table */
    for (i = 0; i < pStringTable->dwMaxSlots; i++)
    {
        if (pStringTable->pSlots[i].pString != NULL)
        {
            if (dwFlags & 1)
            {
                if (!lstrcmpW(pStringTable->pSlots[i].pString, lpString))
                {
                    return i + 1;
                }
            }
            else
            {
                if (!lstrcmpiW(pStringTable->pSlots[i].pString, lpString))
                {
                    return i + 1;
                }
            }
        }
    }

    /* Check for filled slot table */
    if (pStringTable->dwUsedSlots == pStringTable->dwMaxSlots)
    {
        FIXME("Resize the string table!\n");
        return (DWORD)-1;
    }

    /* Search for an empty slot */
    for (i = 0; i < pStringTable->dwMaxSlots; i++)
    {
        if (pStringTable->pSlots[i].pString == NULL)
        {
            pStringTable->pSlots[i].pString = MyMalloc((lstrlenW(lpString) + 1) * sizeof(WCHAR));
            if (pStringTable->pSlots[i].pString == NULL)
            {
                TRACE("Couldn't allocate memory for a new string!\n");
                return (DWORD)-1;
            }

            lstrcpyW(pStringTable->pSlots[i].pString, lpString);

            pStringTable->dwUsedSlots++;

            return i + 1;
        }
    }

    TRACE("Couldn't find an empty slot!\n");

    return (DWORD)-1;
}