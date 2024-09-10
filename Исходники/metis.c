void metis_discover(char* interface,char* metisip) {
    int rc;
    int i;
    int on=1;
    //struct ifreq ifr;

    fprintf(stderr,"Looking for Metis card on interface %s\n",interface);

    discovering=1;
    
    // send a broadcast to locate metis boards on the network
    discovery_socket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(discovery_socket<0) {
        perror("create socket failed for discovery_socket\n");
        exit(1);
    }

    // get my MAC address and IP address
    if(get_addr(discovery_socket,interface)<0) {
        exit(1);
    }

    printf("%s IP Address: %ld.%ld.%ld.%ld\n",
              interface,
              ip_address&0xFF,
              (ip_address>>8)&0xFF,
              (ip_address>>16)&0xFF,
              (ip_address>>24)&0xFF);

    printf("%s MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
         interface,
         hw_address[0], hw_address[1], hw_address[2], hw_address[3], hw_address[4], hw_address[5]);


    // start a receive thread to get discovery responses
    rc=pthread_create(&receive_thread_id,NULL,metis_receive_thread,NULL);
    if(rc != 0) {
        fprintf(stderr,"pthread_create failed on metis_receive_thread: rc=%d\n", rc);
        exit(1);
    }

    // bind to this interface
    struct sockaddr_in name={0};
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = ip_address;
    name.sin_port = htons(DISCOVERY_SEND_PORT);
    bind(discovery_socket,(struct sockaddr*)&name,sizeof(name));


    // allow broadcast on the socket
    rc=setsockopt(discovery_socket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    if(rc != 0) {
        fprintf(stderr,"cannot set SO_BROADCAST: rc=%d\n", rc);
        exit(1);
    }

    discovery_length=sizeof(discovery_addr);
    memset(&discovery_addr,0,discovery_length);
    discovery_addr.sin_family=AF_INET;
    discovery_addr.sin_port=htons(DISCOVERY_SEND_PORT);
    discovery_addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);

    buffer[0]=0xEF;
    buffer[1]=0xFE;
    buffer[2]=0x02;
    for(i=0;i<60;i++) {
        buffer[i+3]=0x00;
    }

    if(sendto(discovery_socket,buffer,63,0,(struct sockaddr*)&discovery_addr,discovery_length)<0) {
        perror("sendto socket failed for discovery_socket\n");
        exit(1);
    }
}