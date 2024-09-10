/* Check if file has NTFS ADS */
int os_check_ads(const char *full_path)
{
    HANDLE file_h;
    WIN32_STREAM_ID sid;
    void *context = NULL;
    char stream_name[MAX_PATH + 1];
    char final_name[MAX_PATH + 1];
    DWORD dwRead, shs, dw1, dw2;

    /* Open file */
    file_h = CreateFile(full_path,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_POSIX_SEMANTICS,
                        NULL);

    if (file_h == INVALID_HANDLE_VALUE) {
        return 0;
    }

    /* Zero memory */
    ZeroMemory(&sid, sizeof(WIN32_STREAM_ID));

    /* Get stream header size -- should be 20 bytes */
    shs = (LPBYTE)&sid.cStreamName - (LPBYTE)&sid + sid.dwStreamNameSize;

    while (1) {
        if (BackupRead(file_h, (LPBYTE) &sid, shs, &dwRead,
                       FALSE, FALSE, &context) == 0) {
            break;
        }
        if (dwRead == 0) {
            break;
        }

        stream_name[0] = '\0';
        stream_name[MAX_PATH] = '\0';
        if (BackupRead(file_h, (LPBYTE)stream_name,
                       sid.dwStreamNameSize,
                       &dwRead, FALSE, FALSE, &context)) {
            if (dwRead != 0) {
                DWORD i = 0;
                int max_path_size = 0;
                char *tmp_pt;
                char op_msg[OS_SIZE_1024 + 1];

                snprintf(final_name, MAX_PATH, "%s", full_path);
                max_path_size = strlen(final_name);

                /* Copy from wide char to char */
                while ((i < dwRead) && (max_path_size < MAX_PATH)) {
                    if (stream_name[i] != 0) {
                        final_name[max_path_size] = stream_name[i];
                        max_path_size++;
                        final_name[max_path_size] = '\0';
                    }
                    i++;
                }

                tmp_pt = strrchr(final_name, ':');
                if (tmp_pt) {
                    *tmp_pt = '\0';
                }

                snprintf(op_msg, OS_SIZE_1024, "NTFS Alternate data stream "
                         "found: '%s'. Possible hidden"
                         " content.",
                         final_name);
                notify_rk(ALERT_ROOTKIT_FOUND, op_msg);
            }
        }

        /* Get next */
        if (!BackupSeek(file_h, sid.Size.LowPart, sid.Size.HighPart,
                        &dw1, &dw2, &context)) {
            break;
        }
    }

    CloseHandle(file_h);
    return (0);
}