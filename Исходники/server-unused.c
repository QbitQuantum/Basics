int main(void)
{
    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number

    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;
    int connected_clients[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int clients_fds[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    
    char remoteIP[INET6_ADDRSTRLEN];

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;

    struct addrinfo hints, *ai, *p;

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

    // get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }
    
    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) { 
            continue;
        }
        
        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL) {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }

    freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    // main loop
    for(;;) {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                            "socket %d\n",
                            inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*)&remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN),
                            newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                            
                            
                            
                            // TODO: remove hung up client from our list.
                            
                            
                            
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        printf("Received data %s from client.\n", buf);
                        fflush(stdout);
                        /* THIS IS THE IMPORTANT PART*/
                        // this is where all info from the client is processed.
                        int tokenval = 0;
                        char *token[255]; //user input and array to hold max possible tokens.

                        token[0] = strtok(buf, " "); //get pointer to first token found and store in 0
                                                           //place in array
                        while(token[tokenval]!= NULL) {   //ensure a pointer was found
                            tokenval++;
                            token[tokenval] = strtok(NULL, " "); //continue to tokenize the string
                        }
                        
                        if (strcmp(token[0], "identify") == 0)
                        {
                            int clival = atoi(token[1]);
                            printf("received an identification of a client.\n");
                            // loop through our connected clients and find a place to put him.
                            int foundspot = 0;
                            for (j = 0; j < 10; j++)
                            {
                                if (connected_clients[j] == clival)
                                {
                                    close(i); // duplicate client identifier.
                                    FD_CLR(i, &master); // remove from master set
                                    foundspot = 1;
                                    break;
                                }
                                if (connected_clients[j] < 0)
                                {
                                    foundspot = 1; // found an empty spot.
                                    connected_clients[j] = clival;
                                    clients_fds[j] = i;
                                    break;
                                }
                            }
                            if (!foundspot)
                            {
                                close(i); // too many connections.
                                FD_CLR(i, &master); // remove from master set
                            }
                            fflush(stdout);
                        }
                        
                        
                        
                        else if (strcmp(token[0], "listclients") == 0) // inquire about # of connected clients.
                        {
                            int clients = 0;
                            for (j = 0; j < 10; j++)
                            {
                                if (connected_clients[j] >= 0)
                                {
                                    clients += 1;
                                }
                            }
                            char temp[10];
                            sprintf(temp, "%i", clients);
                            send(i, temp, 5, 0);
                            /*
                            // TODO: use our list of clients to find out the # of clients instead of inspecting
                            // this file structure.
                            for(j = 0; j <= fdmax; j++) {
                                // count up everyone
                                if (FD_ISSET(j, &master)) {
                                    // except ourselves
                                    if (j != i) {//(j != listener && j != i) {
                                        clients += 1;
                                    }
                                }
                            }
                            */
                        
                            /*
                            for(j = 0; j <= fdmax; j++) {
                                // send to everyone!
                                if (FD_ISSET(j, &master)) {
                                
                                    // except the listener and ourselves
                                    if (j != listener && j != i) {
                                    
                                        fflush(stdout);
                                        if (send(j, buf, nbytes, 0) == -1) {
                                            perror("send");
                                        }
                                    }
                                }
                            }*/
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!
    
    return 0;
}