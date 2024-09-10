int main(void)
{
  int sockfd, numbytes;
  char buf[MAXDATASIZE];
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];
//print local IP and port number
    struct sockaddr_in PatientSock;
    int PatientSockLen;
    //char ipstr[INET6_ADDRSTRLEN]="nunki.usc.edu";
    char ipstr[INET6_ADDRSTRLEN]="localhost";
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    int getsock_check;
    struct sockaddr_in my_addr;
    int addrlen=sizeof(struct sockaddr);
    char destiaddr[20]="127.0.0.1";
//read patient1.txt
  FILE *file_1;
  char patient1[2][20];
//send file
  char head[50]="authenticate ";
//compare receive
  char com[MAXDATASIZE]={'f','a','i','l','u','r','e','\0'};
//send availble
    char avail[15]={'a','v','a','i','l','a','b','l','e','\0'};
//receive table and print;receive patient key board input; send number
    char availtable[200];
    int availtablelen;
    int appointnum[1];// only for now
    char appointcom[10];//to transform int to char
    int j,k;
    char *availabilities[6][3];
    int printnum;//to check whether all availabilities are stored fully
    char selectmes[15];
//whether successfully booked
    char reserved[15];
    int docportnum;
//test side
   
    
//  if (argc != 2) {
 // fprintf(stderr,"usage: client hostname\n");
 // exit(1);
 // }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
    //hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
    
// the IP address of server should be hard coded into the program; change before submit!!!!!!!!!!
  if ((rv = getaddrinfo(destiaddr, PORT, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }
// loop through all the results and connect to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
			 p->ai_protocol)) == -1) {
      perror("client: socket");
      continue;
    }
    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("client: connect");
      continue;
    }
    break;
  }
  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return 2;
  }
//inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),s, sizeof s);
//printf("client: connecting to %s\n", s);
    
    
//host name should be hardcode in the program; change before submit!!!!!!
   // gethostname(ipstr, sizeof ipstr);
    he=gethostbyname(ipstr);
  //  getsockname(sockfd, (struct sockaddr *)&PatientSock, &PatientSockLen);
//from description checking!!!!!!!!!!
    //Retrieve the locally-­‐bound name of the specified socket and store it in the sockaddr structure
    getsock_check=getsockname(sockfd,(struct sockaddr *)&my_addr, (socklen_t *)&addrlen);
    //Error checking
    if(getsock_check==-1)
    {
        perror("getsockname");
        exit(1);
    }
    printf("Phase 1: Patient 1 has TCP port number %d and IP address ", ntohs(my_addr.sin_port));
//BJ P73
  //printf("Patient 1 has TCP port number %d and IP address ", ntohs(PatientSock.sin_port));
  addr_list = (struct in_addr **)he->h_addr_list;
  for(i = 0; addr_list[i] != NULL; i++) {
    printf("%s ", inet_ntoa(*addr_list[i]));
  }
  printf("\n");

  freeaddrinfo(servinfo); // all done with this structure
    
//read patient1.txt and send
  file_1=fopen("patient1.txt","r");
  fscanf(file_1,"%s",patient1[0]);
  fscanf(file_1,"%s",patient1[1]);
  fclose(file_1);
  strcat(head,patient1[0]);
  strcat(head," ");
  strcat(head,patient1[1]);
  if (send(sockfd, head, 50, 0) == -1)
    perror("send");
  else
    printf("Phase 1: Authentication requst from Patient 1 with username %s and password %s has been sent to the Health Center Server\n",patient1[0],patient1[1]);
//authenticate successful or not

  if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }

  buf[numbytes] = '\0';
  printf("Phase 1: Patient 1 authentication result: %s\n",buf);
 
  
   if(strcmp(buf,com)==0)
    {
  //    printf("dead\n");
      close(sockfd);
      exit(1);
    }
   
  printf("Phase 1: End of Phase 1 for Patient1\n");

// Phase 2!!!!!
//send "available"
    if (send(sockfd, avail, 15, 0) == -1)
        perror("send");
//receive table
    if ((availtablelen = recv(sockfd, availtable, 200, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    avail[availtablelen] = '\0';
//store what you receive
    //strtok(availtable," ");
    for(j=0;j<6;j++)
    {
        for(k=0;k<3;k++)
        {
            if (j==0&&k==0) {
                availabilities[j][k]=strtok(availtable," ");
            }
            else
            {
                if((availabilities[j][k]=strtok(NULL," "))==NULL)
                {
                   // printnum=5;
                    continue;
                }
            }
            //fscanf(file_2,"%s", availabilities[i][j]);
            //  availabilities[i][5][0]=1;//right?
        }
    }
    //need to check whether the last line of availabilities[j][k] is null!
    if (availabilities[5][0]==NULL) {
        printnum=5;
        availabilities[5][0]="-1";//to assign this line as useless
    }
    else
    {
        printnum=6;
    }
//print the table;receive patient key board input; send number
    printf("Phase 2: The following appointments are available for Patient1:\n");
    for(j=0;j<printnum;j++)
    {
        for(k=0;k<3;k++)
        {

            printf("%s ", availabilities[j][k]);
        }
        printf("\n");
    }
    //printf("\n");
    printf("Please enter the preferred appointment index and press enter:\n");
    scanf("%d",&appointnum[0]);//is error check needed here?!!!!!!!!!
    //error check
    sprintf(appointcom,"%d",appointnum[0]);
    while((strcmp(availabilities[0][0],appointcom))&&(strcmp(availabilities[1][0],appointcom))&&(strcmp(availabilities[2][0],appointcom))&&(strcmp(availabilities[3][0],appointcom))&&(strcmp(availabilities[4][0],appointcom))&&(strcmp(availabilities[5][0],appointcom))){
        printf("Please enter the preferred appointment index and press enter:\n");
        scanf("%d",&appointnum[0]);
        sprintf(appointcom,"%d",appointnum[0]);
    }
    //send select message
    strcpy(selectmes, "selection ");
    strcat(selectmes,appointcom);
    if (send(sockfd, selectmes, 15, 0) == -1)
        perror("send");
    //receive reply whether the patient book is accepted
    if ((recv(sockfd, reserved, 15, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    char *docname;
    char *docport;
    if(strcmp(reserved,"notavailable")){
        docname=strtok(reserved," ");// the doctor's name could be stored here
        docport=strtok(NULL," ");
        docportnum=atoi(docport);
        printf("Phase 2: The requested appointment is available and reserved to Patient1. The assigned doctor port number is %d\n",docportnum);
    //end of patient tcp progress
        close(sockfd);
    }
    else{
        printf("Phase 2: The requested appointment from Patient 1 is not available.Exiting...\n");
        close(sockfd);
        exit(1);
    }
    
    //from now on start the phase 3 udp!!!!! 11.9
    int sockfd_1;
    struct addrinfo hints_1, *servinfo_1, *p_1;
    int rv_1;
    int numbytes_1;
    //read patient1insurance.txt
    FILE *file_3;
    char patient1insurance[20];
    // receive price
    socklen_t addr_len_1;
    struct sockaddr_storage their_addr_1;
    char price[3];
    
  //  if (argc != 2) {
   //     fprintf(stderr,"usage: talker hostname message\n");
    //    exit(1);
   // }
    memset(&hints_1, 0, sizeof hints_1);
    hints_1.ai_family = AF_UNSPEC;
    hints_1.ai_socktype = SOCK_DGRAM;
    if ((rv_1 = getaddrinfo(destiaddr, docport, &hints_1, &servinfo_1)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv_1));
        return 1;
    }
    // loop through all the results and make a socket
    for(p_1 = servinfo_1; p_1 != NULL; p_1 = p_1->ai_next) {
        if ((sockfd_1 = socket(p_1->ai_family, p_1->ai_socktype,
                             p_1->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }
        break;
    }
    if (p_1 == NULL) {
        fprintf(stderr, "talker: failed to bind socket\n");
        return 2;
    }
    //screen
    
    
    
    // printf("Phase 3: Patient 1 has a dynamic UDP port number and IP address\n");//handle!!!!!!!!
    
    
    //read patient1insurance.txt
    file_3=fopen("patient1insurance.txt","r");
    fscanf(file_3,"%s",patient1insurance);
    // fscanf(file_1,"%s",patient1[1]);
    fclose(file_3);
    
    if ((numbytes_1 = sendto(sockfd_1, patient1insurance, strlen(patient1insurance), 0,p_1->ai_addr, p_1->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
    // IP address and port number
    char hostname[20]="localhost";
    struct hostent *ipaddress;
    struct sockaddr_in my_addr_1;
    int addrlen_1=sizeof(struct sockaddr);
    struct in_addr **addr_list_1;
    ipaddress=gethostbyname(hostname);//IP address
    addr_list_1 = (struct in_addr **)ipaddress->h_addr_list;
    getsockname(sockfd_1,(struct sockaddr *)&my_addr_1, (socklen_t *)&addrlen_1);//socket
    printf("Phase 3: Patient 1 has a dynamic UDP port %d and IP address %s\n",ntohs(my_addr_1.sin_port), inet_ntoa(*addr_list_1[0]));
    // get the Ip address of doc
  
    addr_len_1=sizeof(struct sockaddr);
    printf("Phase 3: The cost estimation request from Patient 1 with insurance plan %s has been sent to the doctor with port number %s and IP adress ", patient1insurance, docport);
    // receive price
    if ((numbytes_1 = recvfrom(sockfd_1, price, 3 , 0,
                             (struct sockaddr *)&their_addr_1, &addr_len_1)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    
   // struct sockaddr_in peer_addr;
    int addrlen_2=sizeof(struct sockaddr);
    struct sockaddr_in *peer_addrt=(struct sockaddr_in *)&their_addr_1;
    char peer_IP[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET,&peer_addrt->sin_addr,peer_IP,sizeof peer_IP);
    printf("%s\n",peer_IP);//Print IP address
    
    
    printf("Phase 3: Patient 1 receives %s$ estimation cost from doctor with port number %s and name %s \n",price,docport, docname);
    //  printf("Phase 3: Patient 1 receives %s$ estimation cost from doctor with port number and name %s \n",price, docname);
    //printf("%s\n",price);
    printf("Phase 3: End of Phase 3 for Patient 1\n");
    freeaddrinfo(servinfo_1);
    // printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
    close(sockfd_1);
    return 0;

    
    
    
    
    //end of patient program
  return 0;
}