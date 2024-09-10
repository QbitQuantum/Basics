int main(int argc, const char * argv[]) {

    const char *server;
    const char *port;
    const char *user;
    const char *image_url;
    const char *message;

    programName = argv[0];

    smc_parsecommandline(argc, argv, showUsage, &server, &port, &user, &message, &image_url, &verbose);

    INFO("main()", "Using the following options: server=\"%s\", port=\"%s\", user=\"%s\", img_url=\"%s\", message=\"%s\"", server, port, user, image_url, message);

    INFO("main()", "connecting to server=\"%s\", port=\"%s\"", server, port);
    int sfd = 0;
    if (connectToServer(server, port, &sfd) != SUCCESS) {
        fprintf(stderr, "%s: connectToServer() failed for server %s and port %s: %s\n", programName, server, port, strerror(errno));
        exit(errno);
    }

    INFO("main()", "open file descriptor for writing %s", "");
    errno = SUCCESS;
    FILE *toServer = fdopen(sfd, "w");
    if (toServer == NULL) {
        fprintf(stderr, "%s: fdOpen() to write to server failed: %s\n", programName, strerror(errno));
        close(sfd);
        exit(errno);
    }

    INFO("main()", "sending data to server %s", server);
    if (sendData(toServer, "user="******"%s: sendData() for param user=<user> failed: %s\n", programName, strerror(errno));
        shutdown(sfd, SHUT_RDWR);
        fclose(toServer);
        exit(errno);
    }

    if (image_url != NULL) {
        INFO("main()", "found image, sending to server %s", server);
        if (sendData(toServer, "img=", image_url) == ERROR) {
            fprintf(stderr, "%s: sendData() for param img=<image_url> failed: %s\n", programName, strerror(errno));
            shutdown(sfd, SHUT_RDWR);
            fclose(toServer);
            exit(errno);
        }
    }

    INFO("main()", "send message to server %s", server);
    if (sendData(toServer, "", message) == ERROR) {
        fprintf(stderr, "%s: sendData() for message failed: %s\n", programName, strerror(errno));
        shutdown(sfd, SHUT_RDWR);
        fclose(toServer);
        exit(errno);
    }

    /* fclose schließt auch sfd, daher vorher ein dup */
    INFO("main()", "creating backup of file descriptor %s", "");
    int backupOfSfd = dup(sfd);

    INFO("main()", "closing connection to server %s", server);
    if (shutdown(sfd, SHUT_WR) != SUCCESS) {
        fprintf(stderr, "%s: shutDown() SHUT_WR for server connection failed: %s\n", programName, strerror(errno));
        fclose(toServer);
        exit(EXIT_FAILURE);
    }

    INFO("main()", "closing file descriptor %s", "");
    fclose(toServer);
    INFO("main()", "closed writing channel to server %s", server);

    INFO("main()", "open stream from server %s", server);
    FILE *fromServer = fdopen(backupOfSfd, "r");
    if (fromServer == NULL) {
        fprintf(stderr, "%s: fdOpen() to read from server failed: %s\n", programName, strerror(errno));
        close(backupOfSfd);
        exit(errno);
    }
    INFO("main()", "opened reading channel from server %s", server);
    /* read line for status=... */
    /* if status returned from server != 0 then exit using the status */
    int status = ERROR;

    INFO("main()", "start checking server response %s", "");
    if (checkServerResponseStatus(fromServer, &status) != SUCCESS || status != SUCCESS) {
        fprintf(stderr, "%s: reading server response failed with error %d\n", programName, status);
        fclose(fromServer);
        close(backupOfSfd);
        exit(status);
    }
    INFO("main()", "server returned status %d", status);

    INFO("main()", "start receiving files from server %s", server);
    int canTransferFile = SUCCESS;
    while (canTransferFile != DONE) {
        canTransferFile = transferFile(fromServer);
        if (canTransferFile == ERROR) {
            fprintf(stderr, "%s: transferFile() failed: %s\n", programName, strerror(errno));
            fclose(fromServer);
            close(backupOfSfd);
            exit(EXIT_FAILURE);
        }
    }

    INFO("main()", "received all data, closing connection to server %s", server);
    fclose(fromServer);
    close(backupOfSfd);
    INFO("main()", "closed connection to server %s", server);
    INFO("main()", "bye %s!", user);
    exit(status);
}