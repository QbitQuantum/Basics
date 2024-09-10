/* Print out streams of a file */
int os_get_streams(char *full_path)
{
    HANDLE file_h; 
    WIN32_STREAM_ID sid;
    void *context = NULL;

    char stream_name[MAX_PATH +1]; 
    char final_name[MAX_PATH +1]; 

    DWORD dwRead, shs, dw1, dw2;


    /* Opening file */
    file_h = CreateFile(full_path, 
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_POSIX_SEMANTICS,
            NULL);

    if (file_h == INVALID_HANDLE_VALUE) 
    { 
        return 0;
    }


    /* Zeroing memory */
    ZeroMemory(&sid, sizeof(WIN32_STREAM_ID));

    /* Getting stream header size -- should be 20 bytes */
    shs = (LPBYTE)&sid.cStreamName - (LPBYTE)&sid+ sid.dwStreamNameSize;


    while(1)
    {
        if(BackupRead(file_h, (LPBYTE) &sid, shs, &dwRead, 
                    FALSE, FALSE, &context) == 0)
        {
            break;
        }
        if(dwRead == 0)
        {
            break;
        }

        stream_name[0] = '\0';
        stream_name[MAX_PATH] = '\0';
        if(BackupRead(file_h, (LPBYTE)stream_name, 
                    sid.dwStreamNameSize, 
                    &dwRead, FALSE, FALSE, &context))
        {
            if(dwRead != 0)
            {
                char *tmp_pt;
                snprintf(final_name, MAX_PATH, "%s%S", full_path, 
                        (WCHAR *)stream_name);
                tmp_pt = strrchr(final_name, ':');
                if(tmp_pt)
                {
                    *tmp_pt = '\0';
                }
                printf("Found NTFS ADS: '%s' \n", final_name);
                ads_found = 1;
            }
        }

        /* Getting next */			
        if(!BackupSeek(file_h, sid.Size.LowPart, sid.Size.HighPart, 
                    &dw1, &dw2, &context))
        {
            break;
        }
    }

    CloseHandle(file_h);
    return(0);
}