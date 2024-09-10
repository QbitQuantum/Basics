/* goodG2B1() - use goodsource and badsink by changing the first staticTrue to staticFalse */
static void goodG2B1()
{
    char * password;
    char passwordBuffer[100] = "";
    password = passwordBuffer;
    if(staticFalse)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        /* FIX: Use a hardcoded password (it was not sent over the network)
        * INCIDENTAL FLAW: CWE-259 Hard Coded Password */
        strcpy(password, "Password1234!");
    }
    if(staticTrue)
    {
        {
            HANDLE pHandle;
            char * username = "******";
            char * domain = "Domain";
            /* Use the password in LogonUser() to establish that it is "sensitive" */
            /* POTENTIAL FLAW: Using sensitive information that was possibly sent in plaintext over the network */
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
        }
    }
}