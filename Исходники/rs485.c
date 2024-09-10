int main(
    int argc,
    char *argv[])
{
    unsigned long hThread = 0;
    uint32_t arg_value = 0;
    char lpBuf[1];
    DWORD dwRead = 0;
    unsigned i = 0, len = 0, count = 0;
    char hex_pair[5] = "0xff";
    char ch = ' ';
    int lsb = 0, msb = 0;
    long my_baud = 38400;
    uint8_t buffer[501] = { 0 };

    if (argc > 1) {
        RS485_Set_Interface(argv[1]);
    }
    if (argc > 2) {
        my_baud = strtol(argv[2], NULL, 0);
    }
    RS485_Set_Baud_Rate(my_baud);
    RS485_Initialize();
#if defined(_WIN32)
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT);
    SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlCHandler, TRUE);
#endif
#ifdef TEST_RS485_TRANSMIT
    /* read a stream of characters from stdin or argument */
    if (argc > 3) {
        len = strlen(argv[3]);
        for (i = 0; i < len; i++) {
            /* grab pairs of hex characters, skip spaces */
            ch = argv[3][i];
            if (ch == ' ') {
                continue;
            }
            msb = ascii_hex_to_int(ch);
            if (msb >= 0) {
                i++;
                ch = argv[3][i];
                lsb = ascii_hex_to_int(ch);
                if (lsb >= 0) {
                    buffer[count] = msb << 4 | lsb;
                } else {
                    buffer[count] = msb;
                }
                count++;
                if (count >= sizeof(buffer)) {
                    break;
                }
            }
        }
        RS485_Send_Frame(NULL, buffer, count);
    }
#endif
#ifdef TEST_RS485_RECEIVE
    /* receive task */
    for (;;) {
        if (!ReadFile(RS485_Handle, lpBuf, sizeof(lpBuf), &dwRead, NULL)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                RS485_Print_Error();
            }
        } else {
            /* print any characters received */
            if (dwRead) {
                for (i = 0; i < dwRead; i++) {
                    fprintf(stderr, "%02X ", lpBuf[i]);
                }
            }
            dwRead = 0;
        }
    }
#endif
}