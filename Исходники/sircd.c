int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    user* u;

    /* Init node and set port accoriding to configue file */
    init_node(argc, argv);

    /* Init the linked list of channel and the table of user */
    init_channel();
    init_user();
    
    /* Init server socket and set it as unblocked */
    listenfd = init_unblocking_server_socket(curr_node_config_entry->irc_port);

    /* connect to local daemon */
    local_client_fd = socket_connect(curr_node_config_entry->ipaddr,curr_node_config_entry->local_port);

    /* Init struct pool */
    init_pool();

    add_listen_fd(listenfd);

    while (1) {
        /* Wait for listening/connected descriptor(s) to become ready */
        p.ready_set = p.read_set;
        p.nready = Select(p.maxfd+1, &p.ready_set, NULL, NULL, NULL);

        /* If listening descriptor ready, add new client to pool */
        if (FD_ISSET(listenfd, &p.ready_set)) {
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

            /* create a user struct for the connect fd */
            u = (user*) Calloc(1,sizeof(user));
            user_table[connfd] = u;

            /*set server_name and host_name for user */
            u->host_name = strdup(Gethostbyaddr((const char*)&clientaddr.sin_addr,sizeof(clientaddr.sin_addr),AF_INET)->h_name);
            u->server_name = strdup(Gethostbyname("localhost")->h_name);

            add_client(connfd);
        }

        /* Echo a text line from each ready connected descriptor */
        check_clients();
    }
}