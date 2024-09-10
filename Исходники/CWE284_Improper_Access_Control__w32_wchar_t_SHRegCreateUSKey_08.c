void CWE284_Improper_Access_Control__w32_wchar_t_SHRegCreateUSKey_08_bad()
{
    if(staticReturnsTrue())
    {
        {
            wchar_t * keyName = L"TEST\\TestKey";
            HUSKEY hKey = HKEY_CURRENT_USER;
            /* FLAW: Call SHRegCreateUSKeyW() with KEY_ALL_ACCESS as the 2nd parameter */
            if (SHRegCreateUSKeyW(
                        keyName,
                        KEY_ALL_ACCESS,
                        NULL,
                        &hKey,
                        SHREGSET_HKCU) != ERROR_SUCCESS)
            {
                printLine("Registry key could not be created");
            }
            else
            {
                printLine("Registry key created successfully");
                SHRegCloseUSKey(hKey);
            }
        }
    }
}