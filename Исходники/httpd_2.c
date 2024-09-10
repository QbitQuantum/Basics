void header(int fd,int contentLength) {
    char buffer[255];  // completely arbritray, should be enough.

    sendTo(fd, "Server: Test/Testing\n");
    sendTo(fd, "Content-Type: text/plain\n");
    if(contentLength > 0) {
        sprintf(buffer,"Content-Length: %d\n", contentLength);
        sendTo(fd, buffer);
    }
    sendTo(fd,"\n\n");
}