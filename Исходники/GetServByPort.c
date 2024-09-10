int main(void) {
    struct servent *servent;
    int port;
    char proto[] = "tcp";
    char name[] = "http";

    /*
    TODO what is a service? PING, HTTP, etc. application layer stuff?
    How to gete those working then?
    */

    port = 80;
    servent = getservbyport(port, proto);
    if (servent == NULL) {
        fprintf(stderr, "getservbyport(%d, %s) failed\n", port, proto);
    } else {
        printf("getservbyport\n");
        printf("  s_name  = %s\n", servent->s_name);
        printf("  s_proto = %s\n", servent->s_proto);
    }

    servent = getservbyname(name, proto);
    if (servent == NULL) {
        fprintf(stderr, "getservbyname(%s, %s) failed\n", name, proto);
    } else {
        printf("getservbyname\n");
        printf("  s_name  = %s\n", servent->s_name);
        printf("  s_port  = %d\n", servent->s_port);
        printf("  s_proto = %s\n", servent->s_proto);
    }
    return EXIT_SUCCESS;
}