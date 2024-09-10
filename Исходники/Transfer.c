/*
 * TransferStart: Retrieve files; the information needed to set up the
 * transfer is in info.
 *
 * This function is run in its own thread.
 */
void __cdecl TransferStart(void *download_info)
{
    Bool done;
    char filename[MAX_PATH + FILENAME_MAX];
    char local_filename[MAX_PATH + 1];  // Local filename of current downloaded file
    int i;
    int outfile;                   // Handle to output file
    DWORD size;                      // Size of block we're reading
    int bytes_read;                // Total # of bytes we've read

#if defined VANILLA_UPDATER
    const char *mime_types[2] = { "application/x-zip-compressed" };
#else
    const char *mime_types[4] = { "application/octet-stream", "text/plain", "application/x-msdownload", NULL };
    //const char *mime_types[2] = { "application/octet-stream", NULL };
#endif

    DWORD file_size;
    DWORD file_size_buf_len;
    DWORD index = 0;
    DownloadInfo *info = (DownloadInfo *)download_info;

    aborted = False;
    hConnection = NULL;
    hSession = NULL;
    hFile = NULL;

    hConnection = InternetOpen(szAppName, INTERNET_OPEN_TYPE_PRECONFIG,
                               NULL, NULL, INTERNET_FLAG_RELOAD);

    if (hConnection == NULL)
    {
        DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTINIT));
        return;
    }

    if (aborted)
    {
        TransferCloseHandles();
        return;
    }

    hSession = InternetConnect(hConnection, info->machine, INTERNET_INVALID_PORT_NUMBER,
                               NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (hSession == NULL)
    {
        DownloadError(info->hPostWnd, GetString(hInst, IDS_NOCONNECTION), info->machine);
        return;
    }

    for (i = info->current_file; i < info->num_files; i++)
    {
        if (aborted)
        {
            TransferCloseHandles();
            return;
        }

        // Skip non-guest files if we're a guest
        if (config.guest && !(info->files[i].flags & DF_GUEST))
        {
            PostMessage(info->hPostWnd, BK_FILEDONE, 0, i);
            continue;
        }

        // If not supposed to transfer file, inform main thread
        if (DownloadCommand(info->files[i].flags) != DF_RETRIEVE)
        {
            // Wait for main thread to finish processing previous file
            WaitForSingleObject(hSemaphore, INFINITE);

            if (aborted)
            {
                TransferCloseHandles();
                return;
            }

            PostMessage(info->hPostWnd, BK_FILEDONE, 0, i);
            continue;
        }
#if VANILLA_UPDATER
        sprintf(filename, "%s%s", info->path, info->files[i].filename);
#else
        sprintf(filename, "%s//%s", info->path, info->files[i].filename);
#endif
        hFile = HttpOpenRequest(hSession, NULL, filename, NULL, NULL,
                                mime_types, INTERNET_FLAG_NO_UI, 0);
        if (hFile == NULL)
        {
            debug(("HTTPOpenRequest failed, error = %d, %s\n",
                   GetLastError(), GetLastErrorStr()));
            DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTFINDFILE),
                          filename, info->machine);
            return;
        }

        if (!HttpSendRequest(hFile, NULL, 0, NULL, 0)) {
            debug(("HTTPSendRequest failed, error = %d, %s\n",
                   GetLastError(), GetLastErrorStr()));
            DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTSENDREQUEST),
                          filename, info->machine);
            return;
        }

        // Get file size
        file_size_buf_len = sizeof(file_size);
        index = 0;
        if (!HttpQueryInfo(hFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
                           &file_size, &file_size_buf_len, &index)) {
            debug(("HTTPQueryInfo failed, error = %d, %s\n",
                   GetLastError(), GetLastErrorStr()));
            DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTGETFILESIZE),
                          filename, info->machine);
            return;
        }

        PostMessage(info->hPostWnd, BK_FILESIZE, i, file_size);
#if VANILLA_UPDATER
        sprintf(local_filename, "%s\\%s", download_dir, info->files[i].filename);
#else
        sprintf(local_filename, "%s\\%s", info->files[i].path, info->files[i].filename);
#endif
        outfile = open(local_filename, O_BINARY | O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
        if (outfile <= 0)
        {
            debug(("Couldn't open local file %s for writing\n", local_filename));
            DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTWRITELOCALFILE),
                          local_filename);
            return;
        }

        // Read first block
        done = False;
        bytes_read = 0;
        while (!done)
        {
            if (!InternetReadFile(hFile, buf, BUFSIZE, &size))
            {
                DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTREADFTPFILE), filename);
            }

            if (size > 0)
            {
                if (write(outfile, buf, size) != size)
                {
                    DownloadError(info->hPostWnd, GetString(hInst, IDS_CANTWRITELOCALFILE),
                                  local_filename);
                    close(outfile);
                    return;
                }
            }

            // Update graph position
            bytes_read += size;
            PostMessage(info->hPostWnd, BK_PROGRESS, 0, bytes_read);

            // See if done with file
            if (size == 0)
            {
                close(outfile);
                InternetCloseHandle(hFile);
                done = True;

                // Wait for main thread to finish processing previous file
                WaitForSingleObject(hSemaphore, INFINITE);

                if (aborted)
                {
                    TransferCloseHandles();
                    return;
                }

                PostMessage(info->hPostWnd, BK_FILEDONE, 0, i);
            }
        }
    }

    InternetCloseHandle(hSession);
    InternetCloseHandle(hConnection);

    PostMessage(info->hPostWnd, BK_TRANSFERDONE, 0, 0);
}