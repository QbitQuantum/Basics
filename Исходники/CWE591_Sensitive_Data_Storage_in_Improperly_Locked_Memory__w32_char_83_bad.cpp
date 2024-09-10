CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_83_bad::~CWE591_Sensitive_Data_Storage_in_Improperly_Locked_Memory__w32_char_83_bad()
{
    {
        HANDLE pHandle;
        char * username = "******";
        char * domain = "Domain";
        /* Use the password in LogonUser() to establish that it is "sensitive" */
        if (LogonUserA(
                    username,
                    domain,
                    password,
                    LOGON32_LOGON_NETWORK,
                    LOGON32_PROVIDER_DEFAULT,
                    &pHandle) != 0)
        {
            printLine("User logged in successfully.");
            CloseHandle(pHandle);
        }
        else
        {
            printLine("Unable to login.");
        }
        /* POTENTIAL FLAW: Sensitive data possibly improperly locked */
        free(password);
    }
}