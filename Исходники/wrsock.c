struct sockaddr_in *creerSock(char *name, char *port, int type, int *sockId) {
    //Création de la structure socketaddr : new
    struct addrinfo *res;
    res = getAddrInfo(name, port, type);
    if ((*sockId = socket(res->ai_family, res->ai_socktype,
            res->ai_protocol)) <= 0) {
        perror("\n pb creation socket \n");
    }
    //TODO copier avent de renvoyer et libérer res : freeaddrinfo(res); 
    return ((struct sockaddr_in *) res->ai_addr);
}