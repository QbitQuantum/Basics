int get(int sockfd, char *remote_file, char *local_file) {
    int len,
        pkt_num = 1;
    char request[512];
    struct file_info fi;
    uint8_t successful = FALSE;

    /* Create local file */
    strcpy(fi.filename, local_file);
    strcpy(fi.mode, MODE_OCTET); //TODO
    fi.readonly = FALSE;

    if (file_init(&fi) == ERRNO_FOPEN) {
        error_num(6);
        return -1;
    }

    struct pkt_request req;
    req.opcode = PKT_RRQ;
    strcpy(req.filename, remote_file);
    strcpy(req.mode, MODE_OCTET); // TODO
    len = serialize_request(&req, request);

    dccp_send(sockfd, request, len);

    while (TRUE) {
        int bytes;
        char buf[BUF_SIZE];

        if ((bytes = recv(sockfd, buf, BUF_SIZE, 0)) <= 0) {
            /* Client shut down */
            if (bytes == 0) {
                //TODO client shut down
                error_num(4);
                break;
            } else  {
                //TODO error
            }
        }

        printf("PKT %d\n", pkt_num++);

        uint16_t opcode = ntohs(*(uint16_t *) buf);

        /* Handle incoming packet */
        if (opcode == PKT_DATA) {
            uint32_t block = ntohs(*(uint32_t *) (buf + B2));
            char *data = buf + B2 + B4;

            printf("block: %d\n", block);

            /* Ignore data with wrong block number */
            if (block == fi.cur_block + 1) {
                append_block(&fi, data, bytes - B2 - B4);
            } else if (block <= fi.cur_block) { // resend ack for lost packet
                send_ack(sockfd, block);
                continue;
            } else {
                continue;
            }

            printf("last_bytes: %d\n", fi.last_numbytes);

            /* Send ACK */
    if (pkt_num != 2 && pkt_num != 3 && pkt_num != 4) // DEBUG REMOVE
            send_ack(sockfd, block); 

            if (fi.last_numbytes < BLOCKSIZE) {
                // transfer finished
                successful = TRUE;
                break; // TODO not break, wait for timeout
            }

        } else if (opcode == PKT_ACK) {

        } else if (opcode == PKT_ERROR) {

        } else {

        }
    }

    file_close(&fi);
    if (!successful)
        remove(fi.filename);
    return 0;
}