/*..........................................................................*/
static DWORD WINAPI idleThread(LPVOID par) {/* signature for CreateThread() */
    (void)par;
    l_running = (uint8_t)1;
    while (l_running) {
        Sleep(10);                                      /* wait for a while */
        if (_kbhit()) {                                 /* any key pressed? */
	        char payload[1024];
            if(!gets_s(payload, sizeof(payload))) { // EOF reached
                printf("EOF received; exiting\n");
                QF_stop();
            } else {
                uint16_t len = strlen(payload);
                onPacket(payload, len, BSPConsole_print, NULL);
            }
        }

#ifdef Q_SPY
        {
            uint16_t nBytes = 1024;
            uint8_t const *block;
            QF_CRIT_ENTRY(dummy);
            block = QS_getBlock(&nBytes);
            QF_CRIT_EXIT(dummy);
            if (block != (uint8_t *)0) {
                send(l_sock, (char const *)block, nBytes, 0);
            }
        }
#endif
    }
    return 0;                                             /* return success */
}