static int
netsnmp_ssh_recv(netsnmp_transport *t, void *buf, int size,
		 void **opaque, int *olength)
{
    int rc = -1;
    netsnmp_tmStateReference *tmStateRef = NULL;
    netsnmp_ssh_addr_pair *addr_pair = NULL;
    int iamclient = 0;

    DEBUGMSGTL(("ssh", "at the top of ssh_recv\n"));
    DEBUGMSGTL(("ssh", "t=%p\n", t));
    if (t != NULL && t->data != NULL) {
	addr_pair = (netsnmp_ssh_addr_pair *) t->data;
    }

    DEBUGMSGTL(("ssh", "addr_pair=%p\n", addr_pair));
    if (t != NULL && addr_pair && addr_pair->channel) {
        DEBUGMSGTL(("ssh", "t=%p, addr_pair=%p, channel=%p\n",
                    t, addr_pair, addr_pair->channel));
        iamclient = 1;
	while (rc < 0) {
	    rc = libssh2_channel_read(addr_pair->channel, buf, size);
	    if (rc < 0) {  /* XXX: from tcp; ssh equiv?:  && errno != EINTR */
		DEBUGMSGTL(("ssh", "recv fd %d err %d (\"%s\")\n",
			    t->sock, errno, strerror(errno)));
		break;
	    }
	    DEBUGMSGTL(("ssh", "recv fd %d got %d bytes\n",
			t->sock, rc));
	}
    } else if (t != NULL) {

#ifdef SNMPSSHDOMAIN_USE_EXTERNAL_PIPE

        socklen_t       tolen = sizeof(struct sockaddr_un);

        if (t != NULL && t->sock >= 0) {
            struct sockaddr *to;
            to = (struct sockaddr *) SNMP_MALLOC_STRUCT(sockaddr_un);
            if (NULL == to) {
                *opaque = NULL;
                *olength = 0;
                return -1;
            }

            if(getsockname(t->sock, to, &tolen) != 0){
                free(to);
                *opaque = NULL;
                *olength = 0;
                return -1;
            };

            if (addr_pair->username[0] == '\0') {
                /* we don't have a username yet, so this is the first message */
                struct ucred *remoteuser;
                struct msghdr msg;
                struct iovec iov[1];
                char cmsg[CMSG_SPACE(sizeof(remoteuser))+4096];
                struct cmsghdr *cmsgptr;
                u_char *charbuf  = buf;

                iov[0].iov_base = buf;
                iov[0].iov_len = size;

                memset(&msg, 0, sizeof msg);
                msg.msg_iov = iov;
                msg.msg_iovlen = 1;
                msg.msg_control = &cmsg;
                msg.msg_controllen = sizeof(cmsg);
                
                rc = recvmsg(t->sock, &msg, MSG_DONTWAIT); /* use DONTWAIT? */
                if (rc <= 0) {
                    return rc;
                }

                /* we haven't received the starting info */
                if ((u_char) charbuf[0] > NETSNMP_SSHTOSNMP_VERSION1) {
                    /* unsupported connection version */
                    snmp_log(LOG_ERR, "received unsupported sshtosnmp version: %d\n", charbuf[0]);
                    return -1;
                }

                DEBUGMSGTL(("ssh", "received first msg over SSH; internal SSH protocol version %d\n", charbuf[0]));

                for (cmsgptr = CMSG_FIRSTHDR(&msg); cmsgptr != NULL; cmsgptr = CMSG_NXTHDR(&msg, cmsgptr)) {
                    if (cmsgptr->cmsg_level == SOL_SOCKET && cmsgptr->cmsg_type == SCM_CREDENTIALS) {
                        /* received credential info */
                        struct passwd *user_pw;

                        remoteuser = (struct ucred *) CMSG_DATA(cmsgptr);

                        if ((user_pw = getpwuid(remoteuser->uid)) == NULL) {
                            snmp_log(LOG_ERR, "No user found for uid %d\n",
                                remoteuser->uid);
                            return -1;
                        }
                        if (strlen(user_pw->pw_name) >
                            sizeof(addr_pair->username)-1) {
                            snmp_log(LOG_ERR,
                                     "User name '%s' too long for snmp\n",
                                     user_pw->pw_name);
                            return -1;
                        }
                        strlcpy(addr_pair->username, user_pw->pw_name,
                                sizeof(addr_pair->username));
                    }
                    DEBUGMSGTL(("ssh", "Setting user name to %s\n",
                                addr_pair->username));
                }

                if (addr_pair->username[0] == '\0') {
                    snmp_log(LOG_ERR,
                             "failed to extract username from sshd connected unix socket\n");
                    return -1;
                }

                if (rc == 1) {
                    /* the only packet we received was the starting one */
                    t->flags |= NETSNMP_TRANSPORT_FLAG_EMPTY_PKT;
                    return 0;
                }

                rc -= 1;
                memmove(charbuf, &charbuf[1], rc);
            } else {
                while (rc < 0) {
                    rc = recvfrom(t->sock, buf, size, 0, NULL, NULL);
                    if (rc < 0 && errno != EINTR) {
                        DEBUGMSGTL(("ssh", "recv fd %d err %d (\"%s\")\n",
                                    t->sock, errno, strerror(errno)));
                        return rc;
                    }
                    *opaque = (void*)to;
                    *olength = sizeof(struct sockaddr_un);
                }
            }
            DEBUGMSGTL(("ssh", "recv fd %d got %d bytes\n",
                        t->sock, rc));
        }
        
#else /* we're called directly by sshd and use stdin/out */

        struct passwd *user_pw;

        iamclient = 0;
        /* we're on the server side and should read from stdin */
        while (rc < 0) {
            rc = read(STDIN_FILENO, buf, size);
            if (rc < 0 && errno != EINTR) {
                DEBUGMSGTL(("ssh",
                            " read on stdin failed: %d (\"%s\")\n",
                            errno, strerror(errno)));
                break;
            }
            if (rc == 0) {
                /* 0 input is probably bad since we selected on it */
                DEBUGMSGTL(("ssh", "got a 0 read on stdin\n"));
                return -1;
            }
            DEBUGMSGTL(("ssh", "read on stdin got %d bytes\n", rc));
        }

/* XXX: need to check the username, but addr_pair doesn't exist! */
        /*
        DEBUGMSGTL(("ssh", "current username=%s\n", c));
        if (addr_pair->username[0] == '\0') {
            if ((user_pw = getpwuid(getuid())) == NULL) {
                snmp_log(LOG_ERR, "No user found for uid %d\n", getuid());
                return -1;
            }
            if (strlen(user_pw->pw_name) > sizeof(addr_pair->username)-1) {
                snmp_log(LOG_ERR, "User name '%s' too long for snmp\n",
                         user_pw->pw_name);
                return -1;
            }
            strlcpy(addr_pair->username, user_pw->pw_name,
                    sizeof(addr_pair->username));
        }
        */

#endif /* ! SNMPSSHDOMAIN_USE_EXTERNAL_PIPE */
    }

    /* create a tmStateRef cache */
    tmStateRef = SNMP_MALLOC_TYPEDEF(netsnmp_tmStateReference);

    /* secshell document says were always authpriv, even if NULL algorithms */
    /* ugh! */
    /* XXX: disallow NULL in our implementations */
    tmStateRef->transportSecurityLevel = SNMP_SEC_LEVEL_AUTHPRIV;

    /* XXX: figure out how to get the specified local secname from the session */
    if (iamclient && 0) {
        /* XXX: we're on the client; we should have named the
           connection ourselves...  pull this from session somehow? */
        strlcpy(tmStateRef->securityName, addr_pair->username,
                sizeof(tmStateRef->securityName));
    } else {
#ifdef SNMPSSHDOMAIN_USE_EXTERNAL_PIPE
        strlcpy(tmStateRef->securityName, addr_pair->username,
                sizeof(tmStateRef->securityName));
#else /* we're called directly by sshd and use stdin/out */
        /* we're on the server... */
        /* XXX: this doesn't copy properly and can get pointer
           reference issues */
        if (strlen(getenv("USER")) > 127) {
            /* ruh roh */
            /* XXX: clean up */
            return -1;
            exit;
        }

        /* XXX: detect and throw out overflow secname sizes rather
           than truncating. */
        strlcpy(tmStateRef->securityName, getenv("USER"),
                sizeof(tmStateRef->securityName));
#endif /* ! SNMPSSHDOMAIN_USE_EXTERNAL_PIPE */
    }
    tmStateRef->securityName[sizeof(tmStateRef->securityName)-1] = '\0';
    tmStateRef->securityNameLen = strlen(tmStateRef->securityName);
    *opaque = tmStateRef;
    *olength = sizeof(netsnmp_tmStateReference);

    return rc;
}