void CWE284_Improper_Access_Control__w32_char_SHRegCreateUSKey_15_bad()
{
    switch(6)
    {
    case 6:
    {
        char * keyName = "TEST\\TestKey";
        HUSKEY hKey = HKEY_CURRENT_USER;
        /* FLAW: Call SHRegCreateUSKeyA() with KEY_ALL_ACCESS as the 2nd parameter */
        if (SHRegCreateUSKeyA(
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
    break;
    default:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    }
}