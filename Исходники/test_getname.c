int
main(int argc, char *argv[])
{
	int clt_sk, svr_sk, accept_sk;
	sockaddr_storage_t svr_loop, accept_loop;
	sockaddr_storage_t svr_local_addr, svr_peer_addr;
	sockaddr_storage_t clt_local_addr, clt_peer_addr;
	socklen_t len;
	int error;
	int pf_class;

        /* Rather than fflush() throughout the code, set stdout to 
	 * be unbuffered.  
	 */ 
	setvbuf(stdout, NULL, _IONBF, 0); 

	/* Initialize the server and client addresses. */ 
#if TEST_V6
	pf_class = PF_INET6;
        svr_loop.v6.sin6_family = AF_INET6;
        svr_loop.v6.sin6_addr = (struct in6_addr)SCTP_IN6ADDR_ANY_INIT;
        svr_loop.v6.sin6_port = htons(SCTP_TESTPORT_1);
#else
	pf_class = PF_INET;
	svr_loop.v4.sin_family = AF_INET;
	svr_loop.v4.sin_addr.s_addr = INADDR_ANY;
	svr_loop.v4.sin_port = htons(SCTP_TESTPORT_1);
#endif

	/* Create and bind the listening server socket.  */
        svr_sk = test_socket(pf_class, SOCK_STREAM, IPPROTO_SCTP);
	test_bind(svr_sk, &svr_loop.sa, sizeof(svr_loop));

	memset(&svr_local_addr, 0x00, sizeof(svr_local_addr));
	len = sizeof(svr_local_addr);
	/* Verify that getsockname() on an unconnected socket works fine. */
	error = getsockname(svr_sk, (struct sockaddr *)&svr_local_addr, &len);
	if (0 != error)
		tst_brkm(TBROK, tst_exit, "getsockname: %s", strerror(errno));

	tst_resm(TPASS, "getsockname on an unconnected socket");

	memset(&svr_peer_addr, 0x00, sizeof(svr_peer_addr));
	len = sizeof(svr_peer_addr);
	/* Verify that getpeername() on an unconnected socket fails. */
	error = getpeername(svr_sk, (struct sockaddr *)&svr_peer_addr, &len);
	if ((-1 != error) || (ENOTCONN != errno))
		tst_brkm(TBROK, tst_exit, "getpeername on an unconnected "
			 "socket error:%d, errno:%d", error, errno);

	tst_resm(TPASS, "getpeername on an unconnected socket");

	/* Mark svr_sk as being able to accept new associations.  */
	test_listen(svr_sk, 5);

	/* Create the client socket.  */
	clt_sk = test_socket(pf_class, SOCK_STREAM, IPPROTO_SCTP);
	
	/* Do a blocking connect from clt_sk to svr_sk */      
#if TEST_V6
	svr_loop.v6.sin6_addr = in6addr_loopback;
#else
	svr_loop.v4.sin_addr.s_addr = SCTP_IP_LOOPBACK;
#endif
	test_connect(clt_sk, &svr_loop.sa, sizeof(svr_loop));

	memset(&clt_local_addr, 0x00, sizeof(clt_local_addr));
	len = sizeof(clt_local_addr);
	/* Get the client's local address. */
	error = getsockname(clt_sk, (struct sockaddr *)&clt_local_addr, &len);
	if (0 != error)
		tst_brkm(TBROK, tst_exit, "getsockname on a connected client "
			 "socket: %s", strerror(errno));

	tst_resm(TPASS, "getsockname on a connected client socket");

	memset(&clt_peer_addr, 0x00, sizeof(clt_peer_addr));
	len = sizeof(clt_peer_addr);
	/* Get the client's peer address. */
	error = getpeername(clt_sk, (struct sockaddr *)&clt_peer_addr, &len);
	if (0 != error)
		tst_brkm(TBROK, tst_exit, "getpeername on a connected client "
			 "socket: %s", strerror(errno));

	tst_resm(TPASS, "getpeername on a connected client socket");

	/* Extract the association on the listening socket as a new socket. */
	len = sizeof(accept_loop);
	accept_sk = test_accept(svr_sk, &accept_loop.sa, &len); 

	memset(&svr_local_addr, 0x00, sizeof(svr_local_addr));
	len = sizeof(svr_local_addr);
	/* Get the server's local address. */
	error = getsockname(accept_sk, (struct sockaddr *)&svr_local_addr,
				&len);
	if (0 != error)
		tst_brkm(TBROK, tst_exit, "getsockname on a connected server "
			 "socket: %s", strerror(errno));

	tst_resm(TPASS, "getsockname on a connected server socket");

	memset(&svr_peer_addr, 0x00, sizeof(svr_peer_addr));
	len = sizeof(svr_peer_addr);
	/* Get the server's peer address. */
	error = getpeername(accept_sk, (struct sockaddr *)&svr_peer_addr,
				&len);
	if (0 != error)
		tst_brkm(TBROK, tst_exit, "getpeername on a connected server "
			 "socket: %s", strerror(errno));

	tst_resm(TPASS, "getpeername on a connected server socket");

	if (svr_local_addr.v4.sin_port != clt_peer_addr.v4.sin_port)
		tst_brkm(TBROK, tst_exit, "Server's local port(%d) doesn't "
			 "match Client's peer port(%d)\n",
			 svr_local_addr.v4.sin_port, clt_peer_addr.v4.sin_port);

	if (svr_peer_addr.v4.sin_port != clt_local_addr.v4.sin_port)
		tst_brkm(TBROK, tst_exit, "Server's peer port(%d) doesn't "
			 "match Client's local port(%d)\n",
			 svr_peer_addr.v4.sin_port, clt_local_addr.v4.sin_port);
#if TEST_V6
	if (memcmp(&svr_local_addr, &clt_peer_addr, len) != 0)
		tst_brkm(TBROK, tst_exit, "Server's local address and client's "
			 "peer addresses do not match\n");

	if (memcmp(&svr_peer_addr, &clt_local_addr, len) != 0)
		tst_brkm(TBROK, tst_exit, "Server's peer address and client's "
			 "local addresses do not match\n");
#else
	if (svr_local_addr.v4.sin_addr.s_addr !=
		 		clt_peer_addr.v4.sin_addr.s_addr)
		tst_brkm(TBROK, tst_exit, "Server's local address and client's "
			 "peer addresses do not match\n");
	if (svr_peer_addr.v4.sin_addr.s_addr !=
		 		clt_local_addr.v4.sin_addr.s_addr)
		tst_brkm(TBROK, tst_exit, "Server's peer address and client's "
			 "local addresses do not match\n");
#endif
	tst_resm(TPASS, "getsockname/getpeername server/client match");

	memset(&clt_local_addr, 0x00, sizeof(clt_local_addr));
	len = sizeof(clt_local_addr);
	/*getsockname():  Bad socket descriptor, EBADF expected error*/
	error = getsockname(-1, (struct sockaddr *)&clt_local_addr, &len);
	if (error != -1 || errno != EBADF)
		tst_brkm(TBROK, tst_exit, "getsockname on a bad socket "
			 "descriptor. error:%d errno:%d", error, errno);

	tst_resm(TPASS, "getsockname on a bad socket descriptor - EBADF");

	/*getsockname(): Invalid socket, ENOTSOCK expected error*/
	error = getsockname(0, (struct sockaddr *)&clt_local_addr, &len);
	if (error != -1 || errno != ENOTSOCK)
		tst_brkm(TBROK, tst_exit, "getsockname on an invalid socket "
			 "error:%d errno:%d", error, errno);

	tst_resm(TPASS, "getsockname on an invalid socket - ENOTSOCK");

	/*getsockname(): Invalid structure, EFAULT expected error*/
	error = getsockname(clt_sk, (struct sockaddr *)-1, &len);
	if (error != -1 || errno != EFAULT)
		tst_brkm(TBROK, tst_exit, "getsockname with invalid buffer "
			 "error:%d errno:%d", error, errno);

	tst_resm(TPASS, "getsockname with invalid buffer - EFAULT");
 
	memset(&clt_peer_addr, 0x00, sizeof(clt_peer_addr));
	len = sizeof(clt_peer_addr);
	/*getpeername():  Bad socket descriptor, EBADF expected error*/
	error = getpeername(-1, (struct sockaddr *)&clt_local_addr, &len);
	if (error != -1 || errno != EBADF)
		tst_brkm(TBROK, tst_exit, "getpeername on a bad socket "
			 "descriptor. error:%d errno:%d", error, errno);

	tst_resm(TPASS, "getpeername on a bad socket descriptor - EBADF");

	/*getpeername(): Invalid socket, ENOTSOCK expected error*/
	error = getpeername(0, (struct sockaddr *)&clt_local_addr, &len);
	if (error != -1 || errno != ENOTSOCK)
		tst_brkm(TBROK, tst_exit, "getpeername on an invalid socket "
			 "error:%d errno:%d", error, errno);

	tst_resm(TPASS, "getpeername on an invalid socket - ENOTSOCK");

	/*getpeername(): Invalid structure, EFAULT expected error*/
	error = getpeername(clt_sk, (struct sockaddr *)-1, &len);
	if (error != -1 || errno != EFAULT)
		tst_brkm(TBROK, tst_exit, "getpeername with invalid buffer "
			 "error:%d errno:%d", error, errno);

	tst_resm(TPASS, "getpeername with invalid buffer - EFAULT");
 
	close(clt_sk);
	close(svr_sk);
	close(accept_sk);

        /* Indicate successful completion.  */
	return 0;
}