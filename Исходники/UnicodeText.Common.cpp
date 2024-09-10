void LogicalStringCompareTest(const WCHAR* str1, const WCHAR* str2, int expected)
{
    int compareStringResult = CompareStringW(LOCALE_USER_DEFAULT, NORM_IGNORECASE | SORT_DIGITSASNUMBERS, str1, -1, str2, -1);

    if (compareStringResult == 0)
    {
        printf("ERROR: CompareStringW failed with error: %d\n", ::GetLastError());
        return;
    }

    compareStringResult = compareStringResult - CSTR_EQUAL;

    int res = PlatformAgnostic::UnicodeText::Internal::LogicalStringCompareImpl<WCHAR>(str1, str2);
    bool passed = res == expected;

    if (compareStringResult != expected)
    {
        wprintf(L"WARNING: Incorrect expected value: %d, actual: %d\n", expected, compareStringResult);
    }

    if (passed)
    {
        wprintf(L"[%s]\n", L"PASS");
    }
    else
    {
        wprintf(L"[%s] Expected: %d, Actual: %d)\n", L"FAIL", expected, res);
    }
}