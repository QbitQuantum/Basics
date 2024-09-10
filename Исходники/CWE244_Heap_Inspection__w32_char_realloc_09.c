void CWE244_Heap_Inspection__w32_char_realloc_09_bad()
{
    if(GLOBAL_CONST_TRUE)
    {
        {
            char * password = (char *)malloc(100*sizeof(char));
            if (password == NULL) {exit(-1);}
            size_t passwordLen = 0;
            HANDLE hUser;
            char * username = "******";
            char * domain = "Domain";
            /* Initialize password */
            password[0] = '\0';
            if (fgets(password, 100, stdin) == NULL)
            {
                printLine("fgets() failed");
                /* Restore NUL terminator if fgets fails */
                password[0] = '\0';
            }
            /* Remove the carriage return from the string that is inserted by fgets() */
            passwordLen = strlen(password);
            if (passwordLen > 0)
            {
                password[passwordLen-1] = '\0';
            }
            /* Use the password in LogonUser() to establish that it is "sensitive" */
            if (LogonUserA(
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
            /* FLAW: reallocate password without clearing the password buffer
             * which could leave a copy of the password in memory */
            password = realloc(password, 200 * sizeof(char));
            if (password == NULL) {exit(-1);}
            /* Zeroize the password */
            SecureZeroMemory(password, 200 * sizeof(char));
            /* Use the password buffer again */
            strcpy(password, "Nothing to see here");
            printLine(password);
            free(password);
        }
    }
}