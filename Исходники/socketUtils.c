struct packet *readPacket(int sockfd) {
    //printf("In readPacket()\n");
    char delimiter = '^';
    char buffer[PACKET_SIZE];
    struct packet *packet = (struct packet *) malloc(sizeof(struct packet));
    struct header *header = (struct header *) malloc(sizeof(struct header));
    packet->header = header;

    //start receiving packet

    //receive 2 bytes for message type
    int bytes_received = recv(sockfd, buffer, 2, 0);
    if (bytes_received == 0) {
        //printf("Recevied zero bytes. Probably because someone terminated.\n");
        return NULL;
    }
    if (bytes_received != 2) {
        char buffer2[2];
        bytes_received += recv(sockfd, buffer2, 1, 0);
        buffer[1] = buffer2[0];
        if (bytes_received != 2) {
            fprintf(stderr, "Error while reading package hearder. Can't proceed.\n");
            exit(-1);
        }

    }
    buffer[bytes_received] = 0;
    if (bytes_received == 0) {
        //printf("Recevied zero bytes. Probably because someone terminated.\n");
        return NULL;
    }
    //printf("Message Type: %s, bytes received: %d\n", buffer, bytes_received);
    packet->header->messageType = atoi(buffer);
    //printf("Received a packet of type: %d\n", packet->header->messageType);
    bytes_received = recv(sockfd, buffer, 1, 0); //discard the delimiter
    //receive the message length
    bytes_received = recv(sockfd, buffer, 1, 0); //first character of length
    //printf("Received byte : %d\n", bytes_received);
    char length[PACKET_SIZE];
    int index = 0;
    while (buffer[0] != delimiter) {
        //printf("Parsing : %c\n", buffer[0]);
        length[index] = buffer[0];
        index++;
        bytes_received = recv(sockfd, buffer, 1, 0);

    }
    length[index] = 0;
    //printf("length chars: %s\n", length);
    packet->header->length = atoi(length);
    //printf("Packet Lenth: %d\n", packet->header->length);
    //read the file name, we have last read the delimiter

    //%02d^%d^%s^%s
    bytes_received = recv(sockfd, buffer, 1, 0);
    char filename[1000];
    index = 0;
    while (buffer[0] != delimiter) {
        filename[index] = buffer[0];
        index++;
        bytes_received = recv(sockfd, buffer, 1, 0);
    }
    filename[index] = 0;
    packet->header->fileName = filename;
    //printf("Filename: %s\n", packet->header->fileName);

    //if message is empty
    if (packet->header->length == 0) {
        packet->message = strdup("");
        return packet;
    }

    //receive the message
    int message_lenght_to_be_received = packet->header->length;

    char *message = (char *) malloc(0);
    int messageLength = 0;
    do {
        bytes_received = recv(sockfd, buffer, message_lenght_to_be_received, 0);
        buffer[bytes_received] = 0;

        //need to concat the buffers received
        messageLength += bytes_received;
        message = realloc(message, messageLength);
        int i;
        for (i = (messageLength - bytes_received); i < messageLength; i++) {
            message[i] = buffer[i - (messageLength - bytes_received)];
        }

        //printf("Bytes of message received: %d Buffer: %s\n", bytes_received, buffer);
        message_lenght_to_be_received -= bytes_received;
    } while (message_lenght_to_be_received > 0);
    message = realloc(message, messageLength + 1);
    message[messageLength] = 0;
    //printf("Bytes of message received: %d Buffer: %s\n", messageLength, message);

//    char *message = "";
//    while (message_lenght_to_be_received > PACKET_SIZE) {
//        bytes_received = recv(sockfd, buffer, PACKET_SIZE, 0);
//        //message = stringConcat(message, buffer);
//        message_lenght_to_be_received = message_lenght_to_be_received - PACKET_SIZE;
//    }
//    bytes_received = recv(sockfd, buffer, message_lenght_to_be_received, 0); //receive only the remaining message
//    buffer[bytes_received] = 0;
//    printf("Buffer: %s, Buffer Size: %d\n", buffer, sizeof(buffer));
    //message = stringConcat(message, buffer);
    packet->message = message;
    //printf("Message: %s\n", packet->message);
    return packet;
}