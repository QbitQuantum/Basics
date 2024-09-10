void
rpc_init(char *name, int prog, int vers, void (*dispatch)(), int defport)
{
	struct sockaddr_in saddr;
	SVCXPRT	*transp;
	int	sock;
	socklen_t asize;

	asize = sizeof(saddr);
	sock = 0;
	if (getsockname(0, (struct sockaddr *) &saddr, &asize) == 0
	    && saddr.sin_family == AF_INET) {
		socklen_t ssize = sizeof (int);
		int fdtype = 0;
		if (getsockopt(0, SOL_SOCKET, SO_TYPE,
				(char *)&fdtype, &ssize) == -1)
			xlog(L_FATAL, "getsockopt failed: %s", strerror(errno));
		/* inetd passes a UDP socket or a listening TCP socket.
		 * listen will fail on a connected TCP socket(passed by rsh).
		 */
		if (!(fdtype == SOCK_STREAM && listen(0,5) == -1)) {
			_rpcfdtype = fdtype;
			_rpcpmstart = 1;
		}
	}
	if (!_rpcpmstart) {
		pmap_unset(prog, vers);
		sock = RPC_ANYSOCK;
	}

	if ((_rpcfdtype == 0) || (_rpcfdtype == SOCK_DGRAM)) {
		static SVCXPRT *last_transp = NULL;
 
		if (_rpcpmstart == 0) {
			if (last_transp
			    && (!defport || defport == last_transp->xp_port)) {
				transp = last_transp;
				goto udp_transport;
			}
			if (defport == 0)
				sock = RPC_ANYSOCK;
			else if ((sock = makesock(defport, IPPROTO_UDP)) < 0) {
				xlog(L_FATAL, "%s: cannot make a UDP socket\n",
						name);
			}
		}
		if (sock == RPC_ANYSOCK)
			sock = svcudp_socket (prog, 1);
		transp = svcudp_create(sock);
		if (transp == NULL) {
			xlog(L_FATAL, "cannot create udp service.");
		}
      udp_transport:
		if (!svc_register(transp, prog, vers, dispatch, IPPROTO_UDP)) {
			xlog(L_FATAL, "unable to register (%s, %d, udp).",
					name, vers);
		}
		last_transp = transp;
	}

	if ((_rpcfdtype == 0) || (_rpcfdtype == SOCK_STREAM)) {
		static SVCXPRT *last_transp = NULL;

		if (_rpcpmstart == 0) {
			if (last_transp
			    && (!defport || defport == last_transp->xp_port)) {
				transp = last_transp;
				goto tcp_transport;
			}
			if (defport == 0)
				sock = RPC_ANYSOCK;
			else if ((sock = makesock(defport, IPPROTO_TCP)) < 0) {
				xlog(L_FATAL, "%s: cannot make a TCP socket\n",
						name);
			}
		}
		if (sock == RPC_ANYSOCK)
			sock = svctcp_socket (prog, 1);
		transp = svctcp_create(sock, 0, 0);
		if (transp == NULL) {
			xlog(L_FATAL, "cannot create tcp service.");
		}
      tcp_transport:
		if (!svc_register(transp, prog, vers, dispatch, IPPROTO_TCP)) {
			xlog(L_FATAL, "unable to register (%s, %d, tcp).",
					name, vers);
		}
		last_transp = transp;
	}

	if (_rpcpmstart) {
		signal (SIGALRM, closedown);
		alarm (_RPCSVC_CLOSEDOWN);
	}
}