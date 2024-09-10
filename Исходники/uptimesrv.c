/* Since a socket endpoint is represented as a file descriptor, we can use
 * read() and write() to communicate with a socket, as long as it is
 * connected. Although we can exchange data using read() and write(), that
 * is about all we can do with these two functions. If we want to specify
 * options, receive packets from multiple clients, or send out-of-band data,
 * we need to use on of the six socket functions designed for data transfer.
 *
 * The simplest one is send(). It is similar to write(), but allows us to
 * specify flags to change how the data we want to transmit is treated.
 * #include <sys/socket.h>
 * ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
 *      Returns: number of bytes sent if OK, -1 on error
 * Like write(), the socket has to be connected to use send(). The buf and
 * nbytes arguments have the same meaning as they do with write().
 * send()函数的flags可能取值为:MSG_DONTROUTE, MSG_DONTWAIT, MSG_EOR, MSG_OOB
 *
 * If send() returns success, it doesn't necessarily mean that the process
 * at the other end of the connection receives the data. All we are
 * guaranteed is that when send() succeeds, the data has been delivered to
 * the network drivers without error.
 *
 * With a protocol that supports message boundaries, if we try to send a
 * single message larger than the maximum supported by the protocol, send()
 * will fail with errno set to EMSGSIZE. With a byte-stream protocol, send()
 * will block until the entire amount of data has been transmitted.
 *
 * The sendto() function is similar to send(). The diffrence is that
 * sendto() allows us to specify a destination address to be used with
 * connectionless socket.
 * ssize_t sendto(int sockfd, const void *buf, size_t nbytes, int flags,
 *      const struct sockaddr *destaddr, socklen_t destlen);
 *      Returns: number of bytes sent if OK, -1 on error 
 * With a connection-oriented socket, the destination address is ignored, as
 * the destination is implied by the connection. With a connectionless
 * socket, we can't use send() unless the destination address is first set
 * by calling connect(), so sendto() gives us an alternate way to send a
 * message.
 *
 * We have one more choice when transmitting data over a socket. We can call
 * sendmsg() with a msghdr structure to specify multiple buffers from which
 * to transmit data, similar to the writev() function.
 * ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
 *      Returns: number of bytes sent if OK, -1 on error
 * 关于这个函数的其他信息可查看man手册.
 */
int main(void)
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, n, err;
    char *hostname;

/* To find out its address, the server needs to get the name of the host on
 * which it is running. Some systems don't define the _SC_HOST_NAME_MAX
 * constant, so we use HOST_NAME_MAX in this case. If the system doesn't
 * define HOST_NAME_MAX, we define it ourselves. POSIX.1 states that the
 * minimum value for the host name is 255 bytes, not including the
 * terminating null, so we define HOST_NAME_MAX to be 256 to include the
 * terminating null.
 * man sysconf 中对 HOST_NAME_MAX, _SC_HOST_NAME_MAX 解释如下:
 * Max length of a hostname, not including the terminating null byte, as
 * returned by gethostname(). Must not be less than _POSIX_HOST_NAME_MAX
 * (255).
 */
#ifdef _SC_HOST_NAME_MAX
    n = sysconf(_SC_HOST_NAME_MAX);
    if (n < 0)
#endif
        n = HOST_NAME_MAX;
    if ((hostname = malloc(n)) == NULL) {
        perror("malloc error");
        exit(1);
    }

    if (gethostname(hostname, n) < 0) {
        perror("gethostname error");
        exit(1);
    }

    daemonize("ruptimed");

    hint.ai_flags = AI_CANONNAME;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM; /* 只获取tcp类型的服务 */
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_addr = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next = NULL;
    /* 注意, "ruptime" 服务并不是标准服务,系统中默认是没有这个服务的,运行
     * 时,getaddrinfo()函数报错: Servname not supported for ai_socktype
     * 解决这个问题的方法是:将"ruptime"服务添加到/etc/services文件中,这样
     * getaddrinfo()函数就能获取到该服务,不会再报错.
     */
    if ((err = getaddrinfo(hostname, "ruptime", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "getaddrinfo error: %s\n", gai_strerror(err));
        exit(1);
    }
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
                        aip->ai_addrlen, QLEN)) >= 0) {
            serve(sockfd);
            exit(0);
        }
    }

    exit(1);
}