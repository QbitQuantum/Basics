/* $begin post_dynamic */
void post_dynamic(int fd, char *filename, int contentLength,rio_t *rp)
{
    char buf[MAXLINE],length[32], *emptylist[] = { NULL },data[MAXLINE];
    int p[2];

    sprintf(length,"%d",contentLength);

    if(pipe(p)==-1)
	syslog(LOG_ERR,"cannot create pipe");

    /*       The post data is sended by client,we need to redirct the data to cgi stdin.
    *  	 so, child read contentLength bytes data from fp,and write to p[1];
    *    parent should redirct p[0] to stdin. As a result, the cgi script can
    *    read the post data from the stdin. 
    */
    if(!ishttps)  /* https already read all data ,include post data  by SSL_read() */
    {
    	if (Fork() == 0)
	{  /* child  */ 
		close(p[0]);
		Rio_readnb(rp,data,contentLength);
		Rio_writen(p[1],data,contentLength);
		exit(0)	;
	}
    }  
    else
    {
    }
    

    /* Send response headers to client */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

    Dup2(p[0],STDIN_FILENO);  /* Redirct p[0] to stdin */
    close(p[0]);

    close(p[1]);
    setenv("CONTENT-LENGTH",length , 1); 
    Dup2(fd,STDOUT_FILENO);        /* Redirct stdout to client */ 
    Execve(filename, emptylist, environ); 
}