/*thread for new client connection, arg is the client_fd*/
void *port_mapper_thread(void *arg){
    int sockfd = (int *)arg;

    //LoadLink *link;
    //link = threadArgs->loadLink;

    char logmsg[128]; 

    /* There are 5 types of Packets to be exchanged via port-mapper:
     * 1) Register service (from server to port mapper)         (000)
     * 2) Register acknowledge (from port mapper to server)     (001)
     * 3) Hello Packets (from server to port mapper)            (111)
     * 4) Request server location (from client to portmapper)   (010)
     * 5) Response server location (from portmapper to client)  (011)
     * */

    struct timeval *tmpcost, cost, timer; // use high quality timer to calculate the ping cost
    struct timezone tzp;

    /* keep receiving Data from server or client */
    //while(1){

    gettimeofday(&timer, &tzp);

    /*lock the send back in case it interrupt by other threads*/
    pthread_mutex_lock(&mutex);

    Packet *packet_recv; // MUST use pointer to fit different Packet
    packet_recv = (Packet *)calloc(1, sizeof(Packet));

    //printf("==port-mapper 1==");
    Recv(sockfd, packet_recv, sizeof(Packet), MSG_NOSIGNAL);

    //printf("==port-mapper 2==");
    /* Register service */
    if(strcmp(packet_recv->packet_type, "000") == 0){
        int dup_register = 0;
        //snprintf(logmsg, sizeof(logmsg), "serverthread(0x%x): packet_recv type: %s\n", pthread_self(), packet_recv->packet_type);
        //logging(LOGFILE, logmsg);
        dup_register = writePortMapperTable(packet_recv, PORT_MAPPER_TABLE_FILE);
        sendRegisterReply(sockfd, packet_recv, dup_register);
    }
    /* Hello packet */
    else if(strcmp(packet_recv->packet_type, "111") == 0){
        snprintf(logmsg, sizeof(logmsg), "serverthread(0x%x): packet_recv type: %s\n", pthread_self(), packet_recv->packet_type);
        logging(LOGFILE, logmsg);
        //sendHello(sockfd, router, threadParam->port);
    }
    /* Request server location */
    else if(strcmp(packet_recv->packet_type, "010") == 0 ){
        snprintf(logmsg, sizeof(logmsg), "serverthread(0x%x): packet_recv type: %s\n", pthread_self(), packet_recv->packet_type);
        logging(LOGFILE, logmsg);
        /*record the chosen response into loadlink*/
        sendRequestReply(sockfd, packet_recv);
    }
    //printf("==port-mapper 3==");

    pthread_mutex_unlock(&mutex);

    shutdown(sockfd, SHUT_RDWR);
    //snprintf(logmsg, sizeof(logmsg), "serverthread(0x%x): served request, exiting thread\n", pthread_self());
    //logging(LOGFILE, logmsg);

    //pthread_exit(0);
    free(packet_recv);
    pthread_exit((void *)link);
    //return (void *) threadArgs->loadLink;
}