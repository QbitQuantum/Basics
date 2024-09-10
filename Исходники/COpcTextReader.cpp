// IsEqual
static bool IsEqual(COpcText& cToken, LPCWSTR szValue1, LPCWSTR szValue2, UINT uSize = -1)
{
    if (szValue1 == NULL || szValue2 == NULL)
    {
        return (szValue1 == szValue2);
    }

    else if (uSize == -1 && cToken.GetIgnoreCase())
    {
        return (wcsicmp(szValue1, szValue2) == 0);
    }

    else if (uSize == -1)
    {
        return (wcscmp(szValue1, szValue2) == 0);
    }

    else if (cToken.GetIgnoreCase())
    {
        return (wcsnicmp(szValue1, szValue2, uSize) == 0);
    }
    
    return (wcsncmp(szValue1, szValue2, uSize) == 0);
}