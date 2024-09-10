int
condor_gethostname(char *name, size_t namelen) {

	if (nodns_enabled()) {

		char tmp[MAXHOSTNAMELEN];
		char *param_buf;

			// First, we try NETWORK_INTERFACE
		if ( (param_buf = param( "NETWORK_INTERFACE" )) ) {
			char ip_str[MAXHOSTNAMELEN];

			// reimplement with condor_sockaddr and to_ip_string()
			condor_sockaddr addr;

			dprintf( D_HOSTNAME, "NO_DNS: Using NETWORK_INTERFACE='%s' "
					 "to determine hostname\n", param_buf );

			snprintf( ip_str, MAXHOSTNAMELEN, "%s", param_buf );
			free( param_buf );

			if (!addr.from_ip_string(ip_str)) {
				dprintf(D_HOSTNAME,
						"NO_DNS: NETWORK_INTERFACE is invalid: %s\n",
						ip_str);
				return -1;
			}

			MyString hostname = convert_ipaddr_to_hostname(addr);
			if (hostname.Length() >= (int) namelen) {
				return -1;
			}
			strcpy(name, hostname.Value());
			return 0;
		}

			// Second, we try COLLECTOR_HOST

			// To get the hostname with NODNS we are going to jump
			// through some hoops. We will try to make a UDP
			// connection to the COLLECTOR_HOST. This will result in not
			// only letting us call getsockname to find an IP for this
			// machine, but it will select the proper IP that we can
			// use to contact the COLLECTOR_HOST
		if ( (param_buf = param( "COLLECTOR_HOST" )) ) {

			//struct hostent *collector_ent;
			int s;
			//SOCKET_LENGTH_TYPE addr_len;
			char collector_host[MAXHOSTNAMELEN];
			char *idx;
			//struct sockaddr_in addr, collector_addr;
			condor_sockaddr collector_addr;
			condor_sockaddr addr;
			std::vector<condor_sockaddr> collector_addrs;

			dprintf( D_HOSTNAME, "NO_DNS: Using COLLECTOR_HOST='%s' "
					 "to determine hostname\n", param_buf );

				// Get only the name portion of the COLLECTOR_HOST
			if ((idx = index(param_buf, ':'))) {
				*idx = '\0';
			}
			snprintf( collector_host, MAXHOSTNAMELEN, "%s", param_buf );
			free( param_buf );

				// Now that we have the name we need an IP

			collector_addrs = resolve_hostname(collector_host);
			if (collector_addrs.empty()) {
				dprintf(D_HOSTNAME,
						"NO_DNS: Failed to get IP address of collector "
						"host '%s'\n", collector_host);
				return -1;
			}

			collector_addr = collector_addrs.front();
			collector_addr.set_port(1980);

				// We are doing UDP, the benefit is connect will not send
				// any network traffic on a UDP socket
			if (-1 == (s = socket(collector_addr.get_aftype(), 
								  SOCK_DGRAM, 0))) {
				dprintf(D_HOSTNAME,
						"NO_DNS: Failed to create socket, errno=%d (%s)\n",
						errno, strerror(errno));
				return -1;
			}

			if (condor_connect(s, collector_addr)) {
				close(s);
				dprintf(D_HOSTNAME,
						"NO_DNS: Failed to bind socket, errno=%d (%s)\n",
						errno, strerror(errno));
				return -1;
			}

			if (condor_getsockname(s, addr)) {
				close(s);
				dprintf(D_HOSTNAME,
						"NO_DNS: Failed to get socket name, errno=%d (%s)\n",
						errno, strerror(errno));
				return -1;
			}

			close(s);
			MyString hostname = convert_ipaddr_to_hostname(addr);
			if (hostname.Length() >= (int) namelen) {
				return -1;
			}
			strcpy(name, hostname.Value());
			return 0;
		}

			// Last, we try gethostname()
		if ( gethostname( tmp, MAXHOSTNAMELEN ) == 0 ) {

			dprintf( D_HOSTNAME, "NO_DNS: Using gethostname()='%s' "
					 "to determine hostname\n", tmp );

			std::vector<condor_sockaddr> addrs;
			MyString my_hostname(tmp);
			addrs = resolve_hostname_raw(my_hostname);
			if (addrs.empty()) {
				dprintf(D_HOSTNAME,
						"NO_DNS: resolve_hostname_raw() failed, errno=%d"
						" (%s)\n", errno, strerror(errno));
				return -1;
			}

			MyString hostname = convert_ipaddr_to_hostname(addrs.front());
			if (hostname.Length() >= (int) namelen) {
				return -1;
			}
			strcpy(name, hostname.Value());
			return 0;
		}

		dprintf(D_HOSTNAME,
				"Failed in determining hostname for this machine\n");
		return -1;

	} else {
		return gethostname(name, namelen);
	}
}