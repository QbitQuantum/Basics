/***
 *
 * Client registration adds the client information into the database
 *
 ***/
void client_registration(HRegistMessage *m, int client_socket){

    printf("Client registration! (%d)\n", client_socket);

    /* store information about the client into the local database */

    FD_SET(client_socket,&listen_set);
    socket_set.push_back(client_socket);
    if (client_socket>highest_socket)
        highest_socket=client_socket;

    clientSignals[client_socket]=m->get_param();
    int id = m->get_id();

    printf("id :: %d \n", id);

    if (id) {
        /* the client is relocating its communicating agent */
        /* the server dissacociates the old socket with the client, and
         * uses the new one instead */
        int cs = clientSocket[id];
        clientSocket[id] = client_socket;
        char *appName = clientName[cs];
        printf("appName:: %s \n", appName);
        clientInfo[appName]=client_socket;
        clientName.erase(cs);
        clientName[client_socket] = appName;

        FD_CLR(cs, &listen_set);
        if (cs==*socketIterator)
            socketIterator++;
        socket_set.remove(cs);
        if (highest_socket==cs)
            highest_socket--;
    } else {
        /* generate id for the new client */
        id = id_set.front();
        id_set.pop_front();
        clientSocket[id] = client_socket;
    }
    clientId[client_socket] = id;
    printf("Send registration (id %d) confimation !\n", id);

    /* send the confirmation message with the client_id */
    HRegistMessage *mesg=new HRegistMessage(HMESG_CLIENT_REG,client_socket);
    mesg->set_id(id);
    send_message(mesg, client_socket);
    delete mesg;
}