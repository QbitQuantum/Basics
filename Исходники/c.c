int main() {
    /* ================
     * resolve hostname
     * ================ */
    struct addrinfo hints = { 0 };
    struct addrinfo* result = NULL;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    int ret = getaddrinfo("api.ipify.org", NULL, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(ret));
        return 1;
    }

    /* ================
     * connect to host
     * ================ */
    struct sockaddr* address = result->ai_addr;
    if (address == NULL || address->sa_family != AF_INET) {
        fprintf(stderr, "invalid address");
        return 1;
    }
    ((struct sockaddr_in*)address)->sin_port = htobe16(80);
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ((ret = connect(fd, address, sizeof(struct sockaddr_in))) != 0) {
        perror("connect failed:");
        return 1;
    }

    /* ================
     * send request
     * ================ */
    const char message[] =
        "GET /?format=json HTTP/1.1\r\n"
        "Host: api.ipify.org\r\n"
        "Connection: close\r\n\r\n";
    const size_t message_size = sizeof(message) - 1;
    for (size_t sent_size = 0; sent_size < message_size;) {
        ret = send(fd, message + sent_size, message_size - sent_size, 0);
        if (ret < 0) {
            perror("send failed:");
            return 1;
        } else if (ret == 0) {
            fprintf(stderr, "remote shutdown");
            return 1;
        }
        sent_size += ret;
    }

    /* ================
     * receive response
     * ================ */
    char buffer[1025] = { 0 };
    const size_t buffer_size = sizeof(buffer) - 1;
    for (size_t received_size = 0; received_size < buffer_size;) {
        ret = recv(fd, buffer + received_size, buffer_size - received_size, 0);
        if (ret <= 0) {
            break;
        }
        received_size += ret;
    }

    /* ================
     * print response and free resources
     * ================ */
    printf("%s\n", buffer);
    close(fd);
    freeaddrinfo(result);
    return 0;
}