/* good1() uses the GoodSink on both sides of the "if" statement */
static void good1()
{
    if(globalReturnsTrueOrFalse())
    {
        {
            char * keyName = "TEST\\TestKey";
            HKEY hKey;
            /* FIX: Call RegCreateKeyExA() without KEY_ALL_ACCESS as the 6th parameter to limit access */
            if (RegCreateKeyExA(
                        HKEY_CURRENT_USER,
                        keyName,
                        0,
                        NULL,
                        REG_OPTION_NON_VOLATILE,
                        KEY_WRITE,
                        NULL,
                        &hKey,
                        NULL) != ERROR_SUCCESS)
            {
                printLine("Registry key could not be created");
            }
            else
            {
                printLine("Registry key created successfully");
                RegCloseKey(hKey);
            }
        }
    }
    else
    {
        {
            char * keyName = "TEST\\TestKey";
            HKEY hKey;
            /* FIX: Call RegCreateKeyExA() without KEY_ALL_ACCESS as the 6th parameter to limit access */
            if (RegCreateKeyExA(
                        HKEY_CURRENT_USER,
                        keyName,
                        0,
                        NULL,
                        REG_OPTION_NON_VOLATILE,
                        KEY_WRITE,
                        NULL,
                        &hKey,
                        NULL) != ERROR_SUCCESS)
            {
                printLine("Registry key could not be created");
            }
            else
            {
                printLine("Registry key created successfully");
                RegCloseKey(hKey);
            }
        }
    }
}