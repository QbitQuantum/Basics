void CWE226_Sensitive_Information_Uncleared_Before_Release__w32_wchar_t_alloca_16_bad()
{
    while(1)
    {
        {
            wchar_t * password = (wchar_t *)ALLOCA(100*sizeof(wchar_t));
            size_t passwordLen = 0;
            HANDLE hUser;
            wchar_t * username = L"User";
            wchar_t * domain = L"Domain";
            /* Initialize password */
            password[0] = L'\0';
            if (fgetws(password, 100, stdin) == NULL)
            {
                printLine("fgetws() failed");
                /* Restore NUL terminator if fgetws fails */
                password[0] = L'\0';
            }
            /* Remove the carriage return from the string that is inserted by fgetws() */
            passwordLen = wcslen(password);
            if (passwordLen > 0)
            {
                password[passwordLen-1] = L'\0';
            }
            /* Use the password in LogonUser() to establish that it is "sensitive" */
            if (LogonUserW(
                        username,
                        domain,
                        password,
                        LOGON32_LOGON_NETWORK,
                        LOGON32_PROVIDER_DEFAULT,
                        &hUser) != 0)
            {
                printLine("User logged in successfully.");
                CloseHandle(hUser);
            }
            else
            {
                printLine("Unable to login.");
            }
            /* FLAW: Release password from the stack without first clearing the buffer */
        }
        break;
    }
}