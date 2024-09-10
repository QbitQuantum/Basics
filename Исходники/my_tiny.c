/*
 * serve_dynamic - serve dynamic content
 */
void serve_dynamic(int connfd, char* filename, char* cgiargs) {

    char body[MAXBUF], *emptylist[] = {NULL};

    /* send response headers to client */
    sprintf(body, "HTTP/1.0 200 OK\r\n");
    sprintf(body, "%sServer: Tiny Web Server\r\n", body);
    Rio_writen(connfd, body, strlen(body));
    
    if (Fork() == 0) {		/* fork a new child */
	setenv("QUERY_STRING", cgiargs, 1);
	Dup2(connfd, STDOUT_FILENO); /* redirect stdout to connfd */
	Execve(filename, emptylist, environ);
    }

    Wait(NULL);			/* parent wait */
}