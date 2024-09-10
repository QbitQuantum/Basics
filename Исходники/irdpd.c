int main(int argc, char **argv)
{
	int i;
	struct servent *service;
	udpport_t route_port;
	nwio_udpopt_t udpopt;
	nwio_ipopt_t ipopt;
	asynchio_t asyn;
	time_t timeout;
	struct timeval tv;
	struct sigaction sa;
	char *offset_arg, *offset_end;
	long arg;

	udp_device= ip_device= nil;
	offset_arg= nil;

	for (i = 1; i < argc && argv[i][0] == '-'; i++) {
		char *p= argv[i] + 1;

		if (p[0] == '-' && p[1] == 0) { i++; break; }

		while (*p != 0) {
			switch (*p++) {
			case 'U':
				if (udp_device != nil) usage();
				if (*p == 0) {
					if (++i == argc) usage();
					p= argv[i];
				}
				udp_device= p;
				p= "";
				break;
			case 'I':
				if (ip_device != nil) usage();
				if (*p == 0) {
					if (++i == argc) usage();
					p= argv[i];
				}
				ip_device= p;
				p= "";
				break;
			case 'o':
				if (offset_arg != nil) usage();
				if (*p == 0) {
					if (++i == argc) usage();
					p= argv[i];
				}
				offset_arg= p;
				p= "";
				break;
			case 'b':
				bcast= 1;
				break;
			case 's':
				/*obsolete*/
				break;
			case 'd':
				debug= 1;
				break;
			default:
				usage();
			}
		}
	}
	if (i != argc) usage();

	/* Debug level signals. */
	sa.sa_handler= sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags= 0;
	sigaction(SIGUSR1, &sa, nil);
	sigaction(SIGUSR2, &sa, nil);

	if (udp_device == nil && (udp_device= getenv("UDP_DEVICE")) == nil)
		udp_device= UDP_DEVICE;

	if (ip_device == nil && (ip_device= getenv("IP_DEVICE")) == nil)
		ip_device= IP_DEVICE;

	if (offset_arg == nil) {
		priority_offset= PRIO_OFF_DEF;
	} else {
		arg= strtol(offset_arg, &offset_end, 0);
		if (*offset_end != 0 || (priority_offset= arg) != arg) usage();
	}

	if ((service= getservbyname("route", "udp")) == nil) {
		fprintf(stderr,
	"irdpd: unable to look up the port number for the 'route' service\n");
		exit(1);
	}

	route_port= (udpport_t) service->s_port;

	if ((rip_fd= open(udp_device, O_RDWR)) < 0) fatal(udp_device);

	udpopt.nwuo_flags= NWUO_COPY | NWUO_LP_SET | NWUO_DI_LOC
		| NWUO_EN_BROAD | NWUO_RP_SET | NWUO_RA_ANY | NWUO_RWDATALL
		| NWUO_DI_IPOPT;
	udpopt.nwuo_locport= route_port;
	udpopt.nwuo_remport= route_port;
	if (ioctl(rip_fd, NWIOSUDPOPT, &udpopt) < 0)
		fatal("setting UDP options failed");

	if ((irdp_fd= open(ip_device, O_RDWR)) < 0) fatal(ip_device);

	ipopt.nwio_flags= NWIO_COPY | NWIO_EN_LOC | NWIO_EN_BROAD
			| NWIO_REMANY | NWIO_PROTOSPEC
			| NWIO_HDR_O_SPEC | NWIO_RWDATALL;
	ipopt.nwio_tos= 0;
	ipopt.nwio_ttl= 1;
	ipopt.nwio_df= 0;
	ipopt.nwio_hdropt.iho_opt_siz= 0;
	ipopt.nwio_rem= htonl(0xFFFFFFFFL);
	ipopt.nwio_proto= IPPROTO_ICMP;

	if (ioctl(irdp_fd, NWIOSIPOPT, &ipopt) < 0)
		fatal("can't configure ICMP channel");

	asyn_init(&asyn);

	while (1) {
		ssize_t r;

		if (do_rip) {
			/* Try a RIP read. */
			r= asyn_read(&asyn, rip_fd, rip_buf, sizeof(rip_buf));
			if (r < 0) {
				if (errno == EIO) fatal(udp_device);
				if (errno != EINPROGRESS) report(udp_device);
			} else {
				now= time(nil);
				rip_incoming(r);
			}
		}

		if (do_rdisc) {
			/* Try an IRDP read. */
			r= asyn_read(&asyn, irdp_fd, irdp_buf,
							sizeof(irdp_buf));
			if (r < 0) {
				if (errno == EIO) fatal(ip_device);
				if (errno != EINPROGRESS) report(ip_device);
			} else {
				now= time(nil);
				irdp_incoming(r);
			}
		}
		fflush(stdout);

		/* Compute the next wakeup call. */
		timeout= next_sol < next_advert ? next_sol : next_advert;

		/* Wait for a RIP or IRDP packet or a timeout. */
		tv.tv_sec= timeout;
		tv.tv_usec= 0;
		if (asyn_wait(&asyn, 0, timeout == NEVER ? nil : &tv) < 0) {
			/* Timeout? */
			if (errno != EINTR && errno != EAGAIN)
				fatal("asyn_wait()");
			now= time(nil);
			time_functions();
		}
	}
}