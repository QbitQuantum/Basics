int main (void)
{
    int rc;
 
    setup_test_environment();
    //  Create the infrastructure
    void *ctx = zmq_ctx_new ();
    assert (ctx);

    void *rep = zmq_socket (ctx, ZMQ_REP);
    assert (rep);
    void *req = zmq_socket (ctx, ZMQ_REQ);
    assert (req);

    rc = zmq_bind(rep, "tcp://127.0.0.1:5560");
    assert (rc == 0);

    rc = zmq_connect(req, "tcp://127.0.0.1:5560");
    assert (rc == 0);

    char tmp[MSG_SIZE];
    zmq_send(req, tmp, MSG_SIZE, 0);

    zmq_msg_t msg;
    rc = zmq_msg_init(&msg);
    assert (rc == 0);

    zmq_recvmsg(rep, &msg, 0);
    assert(zmq_msg_size(&msg) == MSG_SIZE);
  
	  // get the messages source file descriptor
    int srcFd = zmq_msg_get(&msg, ZMQ_SRCFD);
    assert(srcFd >= 0);

	  // get the remote endpoint
    struct sockaddr_storage ss;
    socklen_t addrlen = sizeof ss;
    rc = getpeername (srcFd, (struct sockaddr*) &ss, &addrlen);
    assert (rc == 0);

    char host [NI_MAXHOST];
    rc = getnameinfo ((struct sockaddr*) &ss, addrlen, host, sizeof host, NULL, 0, NI_NUMERICHOST);
    assert (rc == 0);

	  // assert it is localhost which connected
    assert (strcmp(host, "127.0.0.1") == 0);

    rc = zmq_close (rep);
    assert (rc == 0);
    rc = zmq_close (req);
    assert (rc == 0);

	  // sleep a bit for the socket to be freed
	  usleep(30000);
	
	  // getting name from closed socket will fail
    rc = getpeername (srcFd, (struct sockaddr*) &ss, &addrlen);
    assert (rc == -1);
    assert (errno == EBADF);
    
    rc = zmq_ctx_term (ctx);
    assert (rc == 0);

    return 0 ;
}