int main(int argc, char *argv[])
{

    if(argc != 2) {
        printf("\nUsage:\n\nserver portnumber\n\n");
        return -1;
    }
    
    char* port_number = (char *)malloc(sizeof(argv[1]));
    memcpy(port_number, argv[1], sizeof(argv[1]));
    printf("Port number: %s\n", port_number);

    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, port_number, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            //read in data
            //do appropriate action
            lab_1_request *request = (lab_1_request *)malloc(sizeof(lab_1_request));
            int num_bytes;
            if(num_bytes = recv(new_fd, request, sizeof(lab_1_request), 0) == -1) {
                perror("read error");
                exit(-1);
            }
            
            printf("Read %d bytes\n", num_bytes);
            
            to_host_byte_order(request);

            displayBuffer((char *) request, num_bytes);
            printf("\nReceived from client:\n");
            printf("Message size: %d\n", request->total_message_length);
            printf("Request id: %d\n", request->request_id);
            printf("Operation: %d\n", request->operation);
            printf("Message: %s\n\n", request->message);

            if(request->operation == VLENGTH_REQUEST) {
                vowel_length(new_fd, request);
            } else if (request->operation == VOWEL_REMOVAL_REQUEST) {
                remove_vowels(new_fd, request);
            } else {
                printf("Invalid request id\n");
            }
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }
    
    free(port_number);

    return 0;
}