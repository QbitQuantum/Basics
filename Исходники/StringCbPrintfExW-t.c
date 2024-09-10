void testFlags(){
    wchar_t dest[11];
    wchar_t * wanted;

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
                    NULL, NULL, STRSAFE_IGNORE_NULLS, NULL)),
            "Test printing a NULL string.");
    is_wstring(L"", dest,
            "Result of printing a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
                    NULL, NULL, STRSAFE_FILL_BEHIND_NULL | '@',
                    L"testing")),
            "Test filling with '@' behind null termination.");
    is_wstring(L"testing", dest,
            "Result of printing and filling behind null termination.");

    wanted = malloc(3 * sizeof(wchar_t));
    if(wanted == NULL){
        bail("Memory allocation failed.");
    }
    memset(wanted, '@', 3 * sizeof(wchar_t));

    ok(memcmp(&dest[8], wanted, 3 * sizeof(wchar_t)) == 0,
            "Correct data filled after null termination.");

    free(wanted);

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    ok(FAILED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@', L"too much data")),
            "Test filling with '@' on failure.");

    wanted = malloc(11 * sizeof(wchar_t));
    if(wanted == NULL){
        bail("Memory allocation failed.");
    }
    memset(wanted, '@', 10 * sizeof(wchar_t));
    wanted[10] = L'\0';

    ok(memcmp(dest, wanted, 11 * sizeof(wchar_t)) == 0,
            "Result of filling with '@' on failure.");

    free(wanted);

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    ok(FAILED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE, L"Also too much")),
            "Test nulling string on failure.");
    is_wstring(L"", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    ok(FAILED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), NULL, NULL,
                    STRSAFE_NO_TRUNCATION, L"Won't fit in dest")),
            "Test printing with truncating disabled.");
    is_wstring(L"", dest,
            "Result after printing with truncating disabled.");
}