/*
 * main
 *
 * this is where it all happens
 */
int main(int argc, char * argv[])
{
    DWORD dwResult;                            // result from API call
    DWORD dwVersion;                           // API version reported
    WCHAR wszAdapter[MAX_ADAPTER_NAME] = {0};  // the adapter name in wide chars
    char * ptr = NULL;                         // pointer to adapter name
    BOOL bRemovePersist = FALSE;               // remove persistent request
    BOOL bAddPersist = FALSE;                  // add persistent request

    // check for persist options and adapter ID
    for (int i = 1; i < argc; i++)
    {
        char * p;
        p = argv[i];
        if ((p[0] == '/') || (p[0] == '-'))
        {
            p++;
            if ((p[0] == 'p') || (p[0] == 'P'))
                bAddPersist = TRUE;
            if ((p[0] == 'r') || (p[0] == 'R'))
                bRemovePersist = TRUE;
        }
        else
            ptr = argv[i];
    }

    if (!ptr)
        ptr = DetermineAdapter();

    // convert it for the API call
    MultiByteToWideChar(0, 0, ptr, (int) strlen(ptr), wszAdapter, MAX_ADAPTER_NAME);

    // initialize the DHCP Client Options API
    dwResult = DhcpCApiInitialize(&dwVersion);
    if (dwResult != 0)
    {
        OutputError(dwResult);
        exit(4);
    }
    else
        printf("DHCP Client Options API version %d\n", dwVersion);

    printf("Setting DHCP Options on Adapter [%S]\n", wszAdapter);

    // remove persistence if required
    if (bRemovePersist)
    {
        printf("Removing Option Persistence...\n");
        dwResult = DhcpUndoRequestParams(0, NULL, wszAdapter,
                                         DHCP_PERSISTENT_APP_STRING);
        if (dwResult != ERROR_SUCCESS)
            OutputError(dwResult);
    }
    else
    {
        //
        // Here the request is set up - since this is an easy example, the request
        // is set up statically, however in a real-world scenario this may require
        // building the request array in a more 'dynamic' way
        //
        // the DHCP Client Options API arrays for getting the options
        DHCPCAPI_PARAMS requests[1] =
        {{0, OPTION_TIME_SERVERS, FALSE, NULL, 0}}; // gateway address

        // set-up the actual arrays
        DHCPCAPI_PARAMS_ARRAY sendarray = {0, NULL}; // we aren't sending anything
        DHCPCAPI_PARAMS_ARRAY requestarray = {1, requests}; // we are requesting 1

        // buffer variables
        DWORD dwSize = INITIAL_BUFFER_SIZE; // size of buffer for options
        LPBYTE buffer = NULL;               // buffer for options
        IN_ADDR addr;                       // address in return code

        // loop until buffer is big enough to get the data and then make request
        do
        {
            if (buffer)
                LocalFree(buffer);

            buffer = (LPBYTE) LocalAlloc(LPTR, dwSize);       // allocate the buffer
            if (!buffer)
            {
                OutputError(GetLastError());
                exit(5);
            }

            // make the request on the adapter
            DWORD dwFlags = DHCPCAPI_REQUEST_SYNCHRONOUS;
            if (bAddPersist)
            {
                dwFlags = DHCPCAPI_REQUEST_PERSISTENT;
                printf("Making the request persistent...\n");
            }

            dwResult = DhcpRequestParams(dwFlags,
                                         NULL,
                                         wszAdapter,
                                         NULL, sendarray,
                                         requestarray,
                                         buffer, &dwSize,
                                         bAddPersist ?
                                         DHCP_PERSISTENT_APP_STRING : NULL);
        }
        while (dwResult == ERROR_MORE_DATA);

        // parse out results only if we made the synchronous request
        if (dwResult == ERROR_SUCCESS)
        {
            if (bAddPersist != TRUE)
            {
                // check for time server
                if (requests[0].nBytesData > 0)
                {
                    memcpy(&addr, (LPVOID) requests[0].Data, 4);
                    printf("Time Server: %s\n", inet_ntoa(addr));
                }
                else
                    printf("Time Server NOT present!\n");
            }
        }
        else
        {
            OutputError(dwResult);
        }

        // free the buffer
        if (buffer)
            LocalFree(buffer);
    }

    // de-init the api
    DhcpCApiCleanup();

    return 0;
}