//
// Each worker thread starts here.
DWORD WINAPI ThreadFunc(LPVOID pVoid)
{
    BOOL    bResult;
    DWORD   dwNumRead;
    struct ContextKey *pCntx;
    LPOVERLAPPED lpOverlapped;

    UNREFERENCED_PARAMETER(pVoid);

    // Loop forever on getting packets from
    // the I/O completion port.
    for (;;)
    {
        bResult = GetQueuedCompletionStatus(
                      ghCompletionPort,
                      &dwNumRead,
                      &(DWORD)pCntx,
                      &lpOverlapped,
                      INFINITE
                  );

        if (bResult == FALSE
                && lpOverlapped == NULL)
        {
            FatalError(
                "ThreadFunc - Illegal call to GetQueuedCompletionStatus");
        }

        else if (bResult == FALSE
                 && lpOverlapped != NULL)
        {
            // This happens occasionally instead of
            // end-of-file. Not sure why.
            closesocket(pCntx->sock);
            free(pCntx);
            fprintf(stderr,
                    "ThreadFunc - I/O operation failed\n");
        }

        else if (dwNumRead == 0)
        {
            closesocket(pCntx->sock);
            free(pCntx);
            fprintf(stderr, "ThreadFunc - End of file.\n");
        }

        // Got a valid data block!
        // Save the data to our buffer and write it
        // all back out (echo it) if we have see a \n
        else
        {
            // Figure out where in the buffer to save the character
            char *pch = &pCntx->OutBuffer[pCntx->nOutBufIndex++];
            *pch++ = pCntx->InBuffer[0];
            *pch = '\0';    // For debugging, WriteFile doesn't care
            if (pCntx->InBuffer[0] == '\n')
            {
                WriteFile(
                    (HANDLE)(pCntx->sock),
                    pCntx->OutBuffer,
                    pCntx->nOutBufIndex,
                    &pCntx->dwWritten,
                    &pCntx->ovOut
                );
                pCntx->nOutBufIndex = 0;
                fprintf(stderr, "Echo on socket %x.\n", pCntx->sock);
            }

            // Start a new read
            IssueRead(pCntx);
        }
    }

    return 0;
}