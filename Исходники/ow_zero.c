/* Register the out port with Bonjour -- might block so done in a separate thread */
static void *Announce(void *v)
{
	struct connection_out *out = v;
	DNSServiceRef sref = 0;
	DNSServiceErrorType err;

	struct sockaddr sa;
	//socklen_t sl = sizeof(sa);
	socklen_t sl = 128;
	uint16_t port ;
	char * service_name ;
	char name[63] ;

	DETACH_THREAD;

	if (getsockname(out->file_descriptor, &sa, &sl)) {
		LEVEL_CONNECT("Could not get port number of device.");
		pthread_exit(NULL);
		return VOID_RETURN;
	}

	port = ntohs(((struct sockaddr_in *) (&sa))->sin_port) ;

	/* Add the service */
	switch (Globals.program_type) {
		case program_type_httpd:
			service_name = (Globals.announce_name) ? Globals.announce_name : "OWFS (1-wire) Web" ;
			UCLIBCLOCK;
			snprintf(name,62,"%s <%d>",service_name,(int)port);
			UCLIBCUNLOCK;
			err = DNSServiceRegister(&sref, 0, 0, name,"_http._tcp", NULL, NULL, port, 0, NULL, RegisterBack, out) ;
			Announce_Post_Register(sref, err) ;
			err = DNSServiceRegister(&sref, 0, 0, name,"_owhttpd._tcp", NULL, NULL, port, 0, NULL, RegisterBack, out) ;
			break ;
		case program_type_server:
		case program_type_external:
			service_name = (Globals.announce_name) ? Globals.announce_name : "OWFS (1-wire) Server" ;
			UCLIBCLOCK;
			snprintf(name,62,"%s <%d>",service_name,(int)port);
			UCLIBCUNLOCK;
			err = DNSServiceRegister(&sref, 0, 0, name,"_owserver._tcp", NULL, NULL, port, 0, NULL, RegisterBack, out) ;
			break;
		case program_type_ftpd:
			service_name = (Globals.announce_name) ? Globals.announce_name : "OWFS (1-wire) FTP" ;
			UCLIBCLOCK;
			snprintf(name,62,"%s <%d>",service_name,(int)port);
			UCLIBCUNLOCK;
			err = DNSServiceRegister(&sref, 0, 0, name,"_owftp._tcp", NULL, NULL, port, 0, NULL, RegisterBack, out) ;
			break;
		default:
			err = kDNSServiceErr_NoError ;
			break ;
	}

	Announce_Post_Register(sref, err) ;
	LEVEL_DEBUG("Normal completion");
	pthread_exit(NULL);

	return VOID_RETURN;
}