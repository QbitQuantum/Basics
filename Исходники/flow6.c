int main(int argc, char **argv){
	extern char			*optarg;	
	fd_set				sset, rset;
	struct timeval		timeout;
	int					r, sel;
	time_t				curtime, start, lastfrag1=0;

	/* Arrays for storing the Flow ID samples */
	u_int32_t		test1[NSAMPLES], test2[NSAMPLES];
	unsigned int	ntest1=0, ntest2=0;
	unsigned char	testtype;

	static struct option longopts[] = {
		{"interface", required_argument, 0, 'i'},
		{"src-address", required_argument, 0, 's'},
		{"dst-address", required_argument, 0, 'd'},
		{"hop-limit", required_argument, 0, 'A'},
		{"link-src-addr", required_argument, 0, 'S'},
		{"link-dst-addr", required_argument, 0, 'D'},
		{"protocol", required_argument, 0, 'P'},
		{"dst-port", no_argument, 0, 'p'},
		{"flow-label-policy", no_argument, 0, 'W'},
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'}
	};

	char shortopts[]= "i:s:d:A:S:D:P:p:Wvh";

	char option;

	if(argc<=1){
		usage();
		exit(EXIT_FAILURE);
	}


	srandom(time(NULL));
	hoplimit=64+random()%180;

	if(init_iface_data(&idata) == FAILURE){
		puts("Error initializing internal data structure");
		exit(EXIT_FAILURE);
	}

	while((r=getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
		option= r;

		switch(option) {

			case 'i':  /* Interface */
				strncpy(idata.iface, optarg, IFACE_LENGTH-1);
				idata.iface[IFACE_LENGTH-1]=0;
				idata.ifindex= if_nametoindex(idata.iface);
				idata.iface_f=TRUE;
				break;

			case 's':	/* IPv6 Source Address */
				if((charptr = strtok_r(optarg, "/", &lasts)) == NULL){
					puts("Error in Source Address");
					exit(EXIT_FAILURE);
				}

				if ( inet_pton(AF_INET6, charptr, &(idata.srcaddr)) <= 0){
					puts("inet_pton(): Source Address not valid");
					exit(EXIT_FAILURE);
				}

				idata.srcaddr_f = 1;
		
				if((charptr = strtok_r(NULL, " ", &lasts)) != NULL){
					srcpreflen = atoi(charptr);
		
					if(srcpreflen>128){
						puts("Prefix length error in IPv6 Source Address");
						exit(EXIT_FAILURE);
					}

					sanitize_ipv6_prefix(&(idata.srcaddr), srcpreflen);
					srcprefix_f=1;
				}

				break;
	    
			case 'd':	/* IPv6 Destination Address */
				if( inet_pton(AF_INET6, optarg, &(idata.dstaddr)) <= 0){
					puts("inet_pton(): address not valid");
					exit(EXIT_FAILURE);
				}
		
				idata.dstaddr_f = 1;
				break;

			case 'A':	/* Hop Limit */
				hoplimit= atoi(optarg);
				hoplimit_f=1;
				break;

			case 'S':	/* Source Ethernet address */
				if(ether_pton(optarg, &(idata.hsrcaddr), sizeof(idata.hsrcaddr)) == 0){
					puts("Error in Source link-layer address.");
					exit(EXIT_FAILURE);
				}
		
				idata.hsrcaddr_f = 1;
				break;

			case 'D':	/* Destination Ethernet Address */
				if(ether_pton(optarg, &(idata.hdstaddr), sizeof(idata.hdstaddr)) == 0){
					puts("Error in Source link-layer address.");
					exit(EXIT_FAILURE);
				}
		
				idata.hdstaddr_f = 1;
				break;

			case 'P':	/* Protocol */
				if(strncmp(optarg, "tcp", MAX_STRING_SIZE) == 0 || \
					strncmp(optarg, "TCP", MAX_STRING_SIZE) == 0){
					protocol= IPPROTO_TCP;
				}
				else if(strncmp(optarg, "udp", MAX_STRING_SIZE) == 0 || \
					strncmp(optarg, "UDP", MAX_STRING_SIZE) == 0){
					protocol= IPPROTO_UDP;
				}
				else{
					puts("Unknown protocol type (valid types: 'tcp', 'udp')");
					exit(EXIT_FAILURE);
				}

				protocol_f= 1;
				break;

			case 'p':	/* Destination port */
				dstport= atoi(optarg);
				dstport_f=1;
				break;

			case 'W':	/* Assess the Flow Label generation policy of the target */
				flowidp_f= 1;
				break;

			case 'v':	/* Be verbose */
				idata.verbose_f++;
				break;
		
			case 'h':	/* Help */
				print_help();
		
				exit(EXIT_FAILURE);
				break;

			default:
				usage();
				exit(EXIT_FAILURE);
				break;
		
		} /* switch */
	} /* while(getopt) */

	if(geteuid()) {
		puts("flow6 needs root privileges to run.");
		exit(EXIT_FAILURE);
	}

	if(!idata.iface_f){
		if(idata.dstaddr_f && IN6_IS_ADDR_LINKLOCAL(&(idata.dstaddr))){
			puts("Must specify a network interface for link-local destinations");
			exit(EXIT_FAILURE);
		}
	}

	if(load_dst_and_pcap(&idata, LOAD_SRC_NXT_HOP) == FAILURE){
		puts("Error while learning Souce Address and Next Hop");
		exit(EXIT_FAILURE);
	}

	release_privileges();

	if( !fragh_f && dstoptuhdr_f){
		puts("Dst. Options Header (Unfragmentable Part) set, but Fragmentation not specified");
		exit(EXIT_FAILURE);
	}
    
	if(idata.verbose_f){
		print_attack_info();
	}

	if(!idata.dstaddr_f){
		puts("Error: Nothing to send! (Destination Address left unspecified)");
		exit(EXIT_FAILURE);
	}

	/* Assess the Flow ID generation policy */
	if(flowidp_f){
		if(dstport_f && !protocol_f){
			puts("Error: Must specify a protocol if the port number is specified");
			exit(EXIT_FAILURE);
		}

		if(!protocol_f){
			protocol= IPPROTO_TCP;
			dstport= 80;
		}
		else if(!dstport_f){
			if(protocol == IPPROTO_TCP)
				dstport= 80;
			else
				dstport= 53;
		}

		puts("Identifying the 'Flow ID' generation policy of the target node....");

		if(protocol == IPPROTO_TCP){
			tcpwin= ((u_int16_t) random() + 1500) & (u_int16_t)0x7f00;
			tcpseq= random();
			baseport= 50000+ random()%10000;
			lastport= baseport;
		}

		/*
		   Set filter for receiving Neighbor Solicitations, and TCP segments
		 */
		if(pcap_compile(idata.pfd, &pcap_filter, PCAP_NSTCP_FILTER, PCAP_OPT, PCAP_NETMASK_UNKNOWN) == -1){
			printf("pcap_compile(): %s", pcap_geterr(idata.pfd));
			exit(EXIT_FAILURE);
		}
		
		if(pcap_setfilter(idata.pfd, &pcap_filter) == -1){
			printf("pcap_setfilter(): %s", pcap_geterr(idata.pfd));
			exit(EXIT_FAILURE);
		}

		pcap_freecode(&pcap_filter);

		FD_ZERO(&sset);
		FD_SET(idata.fd, &sset);
		start= time(NULL);
		lastfrag1=0;		
		ntest1=0;
		ntest2=0;
		testtype= FIXED_ORIGIN;

		if(srcprefix_f){
			randprefix= idata.srcaddr;
			randpreflen=srcpreflen;
		}
		else{
			randprefix= idata.srcaddr;
			randpreflen=64;
			sanitize_ipv6_prefix(&randprefix, randpreflen);
		}

		while(1){
			curtime=time(NULL);

			if( testtype==FIXED_ORIGIN && ((curtime - start) >= ID_ASSESS_TIMEOUT || ntest1 >= NSAMPLES)){
				testtype= MULTI_ORIGIN;
				addr_sig= random();
				addr_key= random();
				start= curtime;
				continue;
			}
			else if( testtype==MULTI_ORIGIN && ((curtime - start) >= ID_ASSESS_TIMEOUT || ntest2 >= NSAMPLES)){
				break;
			}

			if((curtime - lastfrag1) >= 1){
				if(testtype == FIXED_ORIGIN){
					for(i=0; i<NSAMPLES; i++){
						if(send_fid_probe() == -1){
							puts("Error while sending packet");
							exit(EXIT_FAILURE);
						}

						lastport++;
					}
				}
				else{
					for(i=0; i<NSAMPLES; i++){
						randomize_ipv6_addr(&(idata.srcaddr), &randprefix, randpreflen);

						/*
						 * Two words of the Source IPv6 Address are specially encoded such that we only respond
						 * to Neighbor Solicitations that target those addresses, and accept ICMPv6 Echo Replies
						 * only if they are destined to those addresses
						 */
						idata.srcaddr.s6_addr16[5]= addr_sig;
						idata.srcaddr.s6_addr16[7] =  idata.srcaddr.s6_addr16[6] ^ addr_key;

						if(send_neighbor_solicit(&idata, &(idata.dstaddr)) == -1){
							puts("Error while sending Neighbor Solicitation");
							exit(EXIT_FAILURE);
						}

						if(send_fid_probe() == -1){
							puts("Error while sending packet");
							exit(EXIT_FAILURE);
						}

						lastport++;
					}
				}

				lastfrag1=curtime;
				continue;
			}

			rset= sset;
			timeout.tv_usec=0;
			timeout.tv_sec= 1;

			if((sel=select(idata.fd+1, &rset, NULL, NULL, &timeout)) == -1){
				if(errno == EINTR){
					continue;
				}
				else{
					puts("Error in select()");
					exit(EXIT_FAILURE);
				}
			}

			if(sel == 0)
				continue;

			/* Read a packet (Echo Reply, or Neighbor Solicitation) */
			if((r=pcap_next_ex(idata.pfd, &pkthdr, &pktdata)) == -1){
				printf("pcap_next_ex(): %s", pcap_geterr(idata.pfd));
				exit(EXIT_FAILURE);
			}
			else if(r == 0){
				continue; /* Should never happen */
			}

			pkt_ether = (struct ether_header *) pktdata;
			pkt_ipv6 = (struct ip6_hdr *)((char *) pkt_ether + idata.linkhsize);
			pkt_icmp6 = (struct icmp6_hdr *) ((char *) pkt_ipv6 + sizeof(struct ip6_hdr));
			pkt_end = (unsigned char *) pktdata + pkthdr->caplen;

			if( (pkt_end -  pktdata) < (idata.linkhsize + MIN_IPV6_HLEN))
				continue;

			if(pkt_ipv6->ip6_nxt == IPPROTO_ICMPV6 && pkt_icmp6->icmp6_type == ND_NEIGHBOR_SOLICIT){
				pkt_ns= (struct nd_neighbor_solicit *) pkt_icmp6;

				if( (pkt_end - (unsigned char *) pkt_ns) < sizeof(struct nd_neighbor_solicit))
					continue;
				/* 
				    If the addresses that we're using are not actually configured on the local system
				    (i.e., they are "spoofed", we must check whether it is a Neighbor Solicitation for 
				    one of our addresses, and respond with a Neighbor Advertisement. Otherwise, the kernel
				    will take care of that.
				 */
				if(testtype==FIXED_ORIGIN){
					if(!localaddr_f && is_eq_in6_addr(&(pkt_ns->nd_ns_target), &(idata.srcaddr))){
						if(send_neighbor_advert(&idata, idata.pfd, pktdata) == -1){
							puts("Error sending Neighbor Advertisement");
							exit(EXIT_FAILURE);
						}
					}
				}
				else{
					if(pkt_ns->nd_ns_target.s6_addr16[5] != addr_sig || \
						pkt_ns->nd_ns_target.s6_addr16[7] !=  (pkt_ns->nd_ns_target.s6_addr16[6] ^ addr_key))
						continue;

					if(send_neighbor_advert(&idata, idata.pfd, pktdata) == -1){
						puts("Error sending Neighbor Advertisement");
						exit(EXIT_FAILURE);
					}
				}				
			}
			else if(pkt_ipv6->ip6_nxt == protocol){

				/* Perform TCP-specific validation checks */
				if(protocol == IPPROTO_TCP){
					if( (pkt_end - (unsigned char *) pkt_ipv6) < \
							(sizeof(struct ip6_hdr) + sizeof(struct tcp_hdr)))
						continue;

					pkt_tcp= (struct tcp_hdr *) ((unsigned char *)pkt_ipv6 + sizeof(struct ip6_hdr));

					/*
					 * The TCP Destination Port must correspond to one of the ports that we have used as
					 * TCP Source Port
					 */
					if(ntohs(pkt_tcp->th_dport) < baseport || ntohs(pkt_tcp->th_dport) > lastport)
						continue;

					/* The Source Port must be that to which we're sending our TCP segments */
					if(ntohs(pkt_tcp->th_sport) != dstport)
						continue;

					/* The TCP Acknowledgement Number must ack our SYN */
					if(ntohl(pkt_tcp->th_ack) != tcpseq+1)
						continue;

					/* We sample Flow ID's only on SYN/ACKs */
					if( (pkt_tcp->th_flags & ~TH_SYN) == 0 || (pkt_tcp->th_flags & TH_ACK) == 0)
						continue;

					/* The TCP checksum must be valid */
					if(in_chksum(pkt_ipv6, pkt_tcp, pkt_end-((unsigned char *)pkt_tcp), IPPROTO_TCP) != 0)
						continue;
				}
				/* Perform UDP-specific validation checks */
				else if(protocol == IPPROTO_UDP){
					if( (pkt_end - (unsigned char *) pkt_ipv6) < \
							(sizeof(struct ip6_hdr) + sizeof(struct udp_hdr)))
						continue;

					pkt_udp= (struct udp_hdr *) ((unsigned char *)pkt_ipv6 + sizeof(struct ip6_hdr));

					/*
					 * The UDP Destination Port must correspond to one of the ports that we have used as
					 * the UDP Source Port
					 */
					if(ntohs(pkt_udp->uh_dport) < baseport || ntohs(pkt_udp->uh_dport) > lastport)
						continue;

					/* The Source Port must be that to which we're sending our UDP datagrams */
					if(ntohs(pkt_udp->uh_sport) != dstport)
						continue;

					/* The UDP checksum must be valid */
					if(in_chksum(pkt_ipv6, pkt_udp, pkt_end-((unsigned char *)pkt_udp), IPPROTO_UDP) != 0)
						continue;
				}

				if(testtype==FIXED_ORIGIN){
					if(!is_eq_in6_addr(&(pkt_ipv6->ip6_dst), &(idata.srcaddr))){
						continue;
					}

					if(ntest1 >= NSAMPLES)
						continue;

					test1[ntest1]= ntohl(pkt_ipv6->ip6_flow) & 0x000fffff;
					ntest1++;
				}
				else{
					if(pkt_ipv6->ip6_dst.s6_addr16[5] != addr_sig || \
						pkt_ipv6->ip6_dst.s6_addr16[7] !=  (pkt_ipv6->ip6_dst.s6_addr16[6] ^ addr_key)){
						continue;
					}

					if(ntest2 >= NSAMPLES)
						continue;

					test2[ntest2]= ntohl(pkt_ipv6->ip6_flow) & 0x000fffff;
					ntest2++;
				}
			}
		}

		if(idata.verbose_f > 1){
			printf("Sampled %u Flow Labels from single-origin probes\n", ntest1);

			for(i=0; i<ntest1; i++)
				printf("#%02u: %05x\n", (i+1), test1[i]);

			printf("\nSampled %u Flow Labels from multi-origin probes\n", ntest2);

			for(i=0; i<ntest2; i++)
				printf("#%02u: %05x\n", (i+1), test2[i]);

			puts("");
		}

		if(ntest1 < 10 || ntest2 < 10){
			puts("Error: Didn't receive enough response packets");
			exit(EXIT_FAILURE);
		}

		if(predict_flow_id(test1, ntest1, test2, ntest2) == -1){
			puts("Error in predict_flow_id()");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}

	exit(EXIT_SUCCESS);
}