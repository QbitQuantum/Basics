int main(int argc, char *argv[]) {
    struct sockaddr_in dest;
    int s;
    int slen = sizeof(dest);
    char message[BUFLEN];
    WSADATA wsa;

    PDH_HQUERY hquery;
    PDH_HCOUNTER hcountercpu;
    PDH_STATUS status;
    PDH_FMT_COUNTERVALUE counterval;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup %d\n", WSAGetLastError());
        return 1;
    }

    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    dest.sin_addr.s_addr = inet_addr(SERVER);

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        fprintf(stderr, "socket %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    if ((status = PdhOpenQuery(NULL, 0, &hquery)) != ERROR_SUCCESS) {
        fprintf(stderr, "PdhOpenQuery %lx\n", status);    
        return 1;
    }

    if ((status = PdhAddCounter(hquery, COUNTER_PATH, 0, &hcountercpu)) != ERROR_SUCCESS) {
        fprintf(stderr, "PdhAddCounter (mem) %lx\n", status);    
        return 1;
    }

    /* According to MSDN: Many counters, such as rate counters, require two
    data samples to calculate a formatted data value.
    http://msdn.microsoft.com/en-us/library/windows/desktop/aa371897(v=vs.85).aspx
    But it's not clear which counters might only require one.
    */
    if ((status = PdhCollectQueryData(hquery)) != ERROR_SUCCESS) {
        fprintf(stderr, "PdhCollectQueryData %lx\n", status);    
        return 1;
    }

    Sleep(INTERVAL);

    while (1) {
        if ((status = PdhCollectQueryData(hquery)) != ERROR_SUCCESS) {
            fprintf(stderr, "PdhCollectQueryData %lx\n", status);    
            return 1;
        }

        if ((status = PdhGetFormattedCounterValue(hcountercpu, PDH_FMT_LARGE, 0, &counterval)) != ERROR_SUCCESS) {
            fprintf(stderr, "PdhGetFormattedCounterValue(cpu) %lx\n", status);    
            return 1;
        }

        // %I64d is a MSVC thing
        sprintf_s(message, BUFLEN, "machine.mojave.memAvailable %I64d %d", counterval.largeValue, (unsigned)time(NULL));
        printf("Sending %s\n", message);

        // Send plaintext to carbon server
        if (sendto(s, message, strlen(message), 0, (SOCKADDR*)&dest, slen) == SOCKET_ERROR) {
            fprintf(stderr, "sendto %d\n", WSAGetLastError());
            
            if (closesocket(s) == SOCKET_ERROR) {
                fprintf(stderr, "closesocket %d\n", WSAGetLastError());
            }

            WSACleanup();
            return 1;
        }

        Sleep(INTERVAL);
    }

    if (closesocket(s) == SOCKET_ERROR) {
        fprintf(stderr, "closesocket %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();

    return 0;
}