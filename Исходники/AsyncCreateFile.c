//
// main
//
int __cdecl
wmain(int argc, wchar_t* argv[])
{
    PASYNC_CREATE_FILE_CONTEXT pContext     = NULL;
    LPCWSTR                    wszFileName  = NULL;
    DWORD                      dwWaitStatus = 0;
    DWORD                      dwTimeout    = 0;
    DWORD                      err          = 0;
	BOOL                       bReturnOnTimeout = FALSE;

    if (argc < 4) {
        printf("Usage %ls [file name] [timeout in milliseconds] [return on timeout - 0/1]\n", argv[0]);
        goto cleanup;
    }

    //
    // Get the command line arguments
    //
    wszFileName = argv[1];
    dwTimeout   = (DWORD)_wtoi(argv[2]);
	bReturnOnTimeout = (DWORD)_wtoi(argv[3]);

    //
    // Call CreateFile to check the existence of a file
    // 
    err = AsyncCreateFile( &pContext,
		                   wszFileName,
						   GENERIC_READ,
						   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						   NULL,
						   OPEN_EXISTING,
						   FILE_ATTRIBUTE_NORMAL,
						   NULL );

    if (!err) {

        printf("File found: %ls\n", wszFileName);
        goto cleanup;

	} else if (err != ERROR_IO_PENDING) {

       goto cleanup;
    }

	err = 0;

    //
    // Wait with timeout on the worker thread
    //
    dwWaitStatus = WaitForSingleObject(pContext->hThread, dwTimeout);

    switch (dwWaitStatus) {

    case WAIT_OBJECT_0: 

		//
        // Check the status after CreateFile completed
        //
        if (pContext->dwStatus != ERROR_SUCCESS) {

            err = pContext->dwStatus;

		} else {

			printf("File found: %ls\n", wszFileName);
		}

        break;
    
    case WAIT_TIMEOUT: 

		//
		// If we timeout, attempt to cancel the create.  Note that
		// this may not do anything depending on the current status of
		// the operation
		//
		
        CancelAsyncCreateFile(pContext);

		//
		// If the caller specified we should wait after the cancel call for
		// the create to complete, we do that here; otherwise we return
		// an error.
		//
		
		if (bReturnOnTimeout == TRUE) {

			err = ERROR_OPERATION_ABORTED;

		} else {

			dwWaitStatus = WaitForSingleObject(pContext->hThread, INFINITE);
			err = pContext->dwStatus;
		}

        break;

    default:
        
        err = GetLastError();
        break;
    }

cleanup:
    if (err) {

        if (err == ERROR_OPERATION_ABORTED) {

			if (bReturnOnTimeout == TRUE) {

				printf("Operation timed out while trying to open %ls\n", wszFileName);

			} else {

				//
				// If we waited for the create to complete and we still got 
				// this error code, we know that it was successfully cancelled.
				//
				printf("Operation timed out and was cancelled while trying to open %ls\n", wszFileName);
			}

        } else {

            printf("Error %u while trying to open %ls\n", err, wszFileName);
        }
    }

    if (pContext) {
        CleanupAsyncCreateFile(pContext);
    }

    return err ? 2 : 0;
}