void testFlags(){
    wchar_t dest[11];
    wchar_t * wanted;

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    ok(SUCCEEDED(StringCbCopyExW(dest, 11 * sizeof(wchar_t),
                    NULL, NULL, NULL,
                    STRSAFE_IGNORE_NULLS)),
            "Test copying a NULL string.");
    is_wstring(L"", dest,
            "Result of copying a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    ok(SUCCEEDED(StringCbCopyExW(dest, 11 * sizeof(wchar_t),
                    L"testing", NULL, NULL,
                    STRSAFE_FILL_BEHIND_NULL | '@')),
            "Test filling with '@' behind null termination.");
    is_wstring(L"testing", dest,
            "Result of copying and filling behind null termination.");

    wanted = malloc(3 * sizeof(wchar_t));
    if(wanted == NULL){
        bail("Memory allocation failed.");
    }
    memset(wanted, '@', 3 * sizeof(wchar_t));

    ok(memcmp(&dest[8], wanted, 3 * sizeof(wchar_t)) == 0,
            "Correct data filled after null termination.");

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    ok(FAILED(StringCbCopyExW(dest, 11 * sizeof(wchar_t),
                    L"too much data", NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@')),
            "Test filling with '@' on failure.");
    
    wanted = malloc(10 * sizeof(wchar_t));
    if(wanted == NULL){
        bail("Memory allocation failed.");
    }
    memset(wanted, '@', 10 * sizeof(wchar_t));

    ok(memcmp(dest, wanted, 10 * sizeof(wchar_t)) == 0,
            "Result of filling with '@' on failure.");
    ok(dest[10] == L'\0',
            "Check null termination at end of filled buffer.");
    free(wanted);

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    ok(FAILED(StringCbCopyExW(dest, 11 * sizeof(wchar_t),
                    L"Also too much", NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE)),
            "Test nulling string on failure.");
    is_wstring(L"", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    ok(FAILED(StringCbCopyExW(dest, 11 * sizeof(wchar_t), 
                    L"Won't fit in dest", NULL, NULL,
                    STRSAFE_NO_TRUNCATION)),
            "Test copying with truncating disabled.");
    is_wstring(L"", dest,
            "Result after copying with truncating disabled.");
}