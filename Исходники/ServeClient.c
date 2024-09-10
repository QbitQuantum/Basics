/* $begin serve_dynamic */
void serve_dynamic(int fd, char *filename, char *cgiargs, rio_t *rp)
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

    if (Fork() == 0) { /* child */
        /* Real server would set all CGI vars here */
        read_request(rp, cgiargs);
        setenv("QUERY_STRING", cgiargs, 1);
        fprintf(stderr, "%s: %s\r\n", "QUERY_STRING", cgiargs);
        Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */
        Execve(filename, emptylist, environ); /* Run CGI program */
    }
    Wait(NULL); /* Parent waits for and reaps child */
}