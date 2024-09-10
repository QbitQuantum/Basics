int main(int argc, char* argv[])
{
    char buff[2048];
    char io[2];
    HANDLE hFile;
    DWORD readed, written;
    DCB dcb;
    BOOL fFirst = FALSE;

    /* Creating cache */
    memset(buff, 0, 2048);

    FILE* fl = fopen("sdramtest.bin", "rb+");
    if (fl == NULL) {
        return -100;
    }
    fread(buff, 1, 2048, fl);
    fclose(fl);


    hFile = CreateFileW(PORT, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return -1;
    }

    BOOL res = GetCommState(hFile, &dcb);
    res = BuildCommDCBW(PARAM, &dcb);
    res = SetCommState(hFile, &dcb);

    if (res == FALSE) {
        return -2;
    }


    for (;;) {
        BOOL res = ReadFile(hFile, io, 1, &readed, NULL);
        if ((res) && (readed > 0)) {
            io[1] = 0;
            printf("%s", io);
            if ((io[0] == '<') && !fFirst) {
                fFirst = TRUE;

                /* Copy 2048 bytes */
                res = WriteFile(hFile, buff, 2048, &written, NULL);
                if (res) {
                    printf("\n%d bytes sended\n", (int)written);
                }
            } else if ((io[0] == '<') && fFirst) {
                return 1;
            }
        }
    }


    return 0;
}