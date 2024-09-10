int mcast_join_group( int sock, IP *addr, const char ifce[] ) {
#if defined(MCAST_JOIN_GROUP) && !defined(__APPLE__)
	struct group_req req;

	if( ifce ) {
		if( (req.gr_interface = if_nametoindex( ifce )) == 0 ) {
			log_err( "LPD: Cannot find interface '%s' for multicast: %s", ifce, strerror( errno ) );
			return -1;
		}
	} else {
		req.gr_interface = 0;
	}

	memcpy( &req.gr_group, addr, addr_len( addr ) );

	if( setsockopt( sock, IPPROTO_IP, MCAST_JOIN_GROUP, &req, sizeof(req) ) < 0 ) {
		log_warn( "LPD: Failed to join multicast group: %s", strerror( errno ) );
		return -1;
	}

	return 0;
#else
	switch( addr->ss_family ) {
		case AF_INET: {
			struct ip_mreq mreq;
			struct ifreq ifreq;

			memcpy( &mreq.imr_multiaddr, &((IP4*) addr)->sin_addr, 4 );

			if( ifce ) {
				strncpy( ifreq.ifr_name, ifce, IFNAMSIZ );

				if( ioctl( sock, SIOCGIFADDR, &ifreq ) < 0 ) {
					log_err( "LPD: Cannot find interface '%s' for multicast: %s", ifce, strerror( errno ) );
					return -1;
				}
				memcpy( &mreq.imr_interface, &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr, 4);
			} else {
				mreq.imr_interface.s_addr = htonl( INADDR_ANY );
			}

			if( setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0 ) {
				log_warn( "LPD: Failed to join IPv4 multicast group: %s", strerror( errno ) );
				return -1;
			}
			return 0;
		}
		case AF_INET6: {
			struct ipv6_mreq	mreq6;

			memcpy( &mreq6.ipv6mr_multiaddr, &((IP6*) addr)->sin6_addr, 16 );

			if( ifce ) {
				if( (mreq6.ipv6mr_interface = if_nametoindex( ifce )) == 0 ) {
					log_err( "LPD: Cannot find interface '%s' for multicast: %s", ifce, strerror( errno ) );
					return -1;
				}
			} else {
				mreq6.ipv6mr_interface = 0;
			}

			if( setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6, sizeof(mreq6)) < 0 ) {
				log_warn( "LPD: Failed to join IPv6 multicast group: %s", strerror( errno ) );
				return -1;
			}
			return 0;
		}
		default:
			return -1;
	}
#endif
}