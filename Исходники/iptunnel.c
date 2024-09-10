static int parse_args(int argc, char **argv, int cmd, struct ip_tunnel_parm *p)
{
	int count = 0;
	char medium[IFNAMSIZ];
	int isatap = 0;

	memset(p, 0, sizeof(*p));
	memset(&medium, 0, sizeof(medium));

	p->iph.version = 4;
	p->iph.ihl = 5;
#ifndef IP_DF
#define IP_DF		0x4000		/* Flag: "Don't Fragment"	*/
#endif
	p->iph.frag_off = htons(IP_DF);

	while (argc > 0) {
		if (strcmp(*argv, "mode") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "ipip") == 0 ||
			    strcmp(*argv, "ip/ip") == 0) {
				if (p->iph.protocol && p->iph.protocol != IPPROTO_IPIP) {
					fprintf(stderr,"You managed to ask for more than one tunnel mode.\n");
					exit(-1);
				}
				p->iph.protocol = IPPROTO_IPIP;
			} else if (strcmp(*argv, "gre") == 0 ||
				   strcmp(*argv, "gre/ip") == 0) {
				if (p->iph.protocol && p->iph.protocol != IPPROTO_GRE) {
					fprintf(stderr,"You managed to ask for more than one tunnel mode.\n");
					exit(-1);
				}
				p->iph.protocol = IPPROTO_GRE;
			} else if (strcmp(*argv, "sit") == 0 ||
				   strcmp(*argv, "ipv6/ip") == 0) {
				if (p->iph.protocol && p->iph.protocol != IPPROTO_IPV6) {
					fprintf(stderr,"You managed to ask for more than one tunnel mode.\n");
					exit(-1);
				}
				p->iph.protocol = IPPROTO_IPV6;
			} else if (strcmp(*argv, "isatap") == 0) {
				if (p->iph.protocol && p->iph.protocol != IPPROTO_IPV6) {
					fprintf(stderr, "You managed to ask for more than one tunnel mode.\n");
					exit(-1);
				}
				p->iph.protocol = IPPROTO_IPV6;
				isatap++;
			} else if (strcmp(*argv, "vti") == 0) {
				if (p->iph.protocol && p->iph.protocol != IPPROTO_IPIP) {
					fprintf(stderr, "You managed to ask for more than one tunnel mode.\n");
					exit(-1);
				}
				p->iph.protocol = IPPROTO_IPIP;
				p->i_flags |= VTI_ISVTI;
			} else {
				fprintf(stderr,"Cannot guess tunnel mode.\n");
				exit(-1);
			}
		} else if (strcmp(*argv, "key") == 0) {
			unsigned uval;
			NEXT_ARG();
			p->i_flags |= GRE_KEY;
			p->o_flags |= GRE_KEY;
			if (strchr(*argv, '.'))
				p->i_key = p->o_key = get_addr32(*argv);
			else {
				if (get_unsigned(&uval, *argv, 0)<0) {
					fprintf(stderr, "invalid value of \"key\"\n");
					exit(-1);
				}
				p->i_key = p->o_key = htonl(uval);
			}
		} else if (strcmp(*argv, "ikey") == 0) {
			unsigned uval;
			NEXT_ARG();
			p->i_flags |= GRE_KEY;
			if (strchr(*argv, '.'))
				p->i_key = get_addr32(*argv);
			else {
				if (get_unsigned(&uval, *argv, 0)<0) {
					fprintf(stderr, "invalid value of \"ikey\"\n");
					exit(-1);
				}
				p->i_key = htonl(uval);
			}
		} else if (strcmp(*argv, "okey") == 0) {
			unsigned uval;
			NEXT_ARG();
			p->o_flags |= GRE_KEY;
			if (strchr(*argv, '.'))
				p->o_key = get_addr32(*argv);
			else {
				if (get_unsigned(&uval, *argv, 0)<0) {
					fprintf(stderr, "invalid value of \"okey\"\n");
					exit(-1);
				}
				p->o_key = htonl(uval);
			}
		} else if (strcmp(*argv, "seq") == 0) {
			p->i_flags |= GRE_SEQ;
			p->o_flags |= GRE_SEQ;
		} else if (strcmp(*argv, "iseq") == 0) {
			p->i_flags |= GRE_SEQ;
		} else if (strcmp(*argv, "oseq") == 0) {
			p->o_flags |= GRE_SEQ;
		} else if (strcmp(*argv, "csum") == 0) {
			p->i_flags |= GRE_CSUM;
			p->o_flags |= GRE_CSUM;
		} else if (strcmp(*argv, "icsum") == 0) {
			p->i_flags |= GRE_CSUM;
		} else if (strcmp(*argv, "ocsum") == 0) {
			p->o_flags |= GRE_CSUM;
		} else if (strcmp(*argv, "nopmtudisc") == 0) {
			p->iph.frag_off = 0;
		} else if (strcmp(*argv, "pmtudisc") == 0) {
			p->iph.frag_off = htons(IP_DF);
		} else if (strcmp(*argv, "remote") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "any"))
				p->iph.daddr = get_addr32(*argv);
		} else if (strcmp(*argv, "local") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "any"))
				p->iph.saddr = get_addr32(*argv);
		} else if (strcmp(*argv, "dev") == 0) {
			NEXT_ARG();
			strncpy(medium, *argv, IFNAMSIZ-1);
		} else if (strcmp(*argv, "ttl") == 0 ||
			   strcmp(*argv, "hoplimit") == 0) {
			unsigned uval;
			NEXT_ARG();
			if (strcmp(*argv, "inherit") != 0) {
				if (get_unsigned(&uval, *argv, 0))
					invarg("invalid TTL\n", *argv);
				if (uval > 255)
					invarg("TTL must be <=255\n", *argv);
				p->iph.ttl = uval;
			}
		} else if (strcmp(*argv, "tos") == 0 ||
			   strcmp(*argv, "tclass") == 0 ||
			   matches(*argv, "dsfield") == 0) {
			__u32 uval;
			NEXT_ARG();
			if (strcmp(*argv, "inherit") != 0) {
				if (rtnl_dsfield_a2n(&uval, *argv))
					invarg("bad TOS value", *argv);
				p->iph.tos = uval;
			} else
				p->iph.tos = 1;
		} else {
			if (strcmp(*argv, "name") == 0) {
				NEXT_ARG();
			} else if (matches(*argv, "help") == 0)
				usage();
			if (p->name[0])
				duparg2("name", *argv);
			strncpy(p->name, *argv, IFNAMSIZ);
			if (cmd == SIOCCHGTUNNEL && count == 0) {
				struct ip_tunnel_parm old_p;
				memset(&old_p, 0, sizeof(old_p));
				if (tnl_get_ioctl(*argv, &old_p))
					return -1;
				*p = old_p;
			}
		}
		count++;
		argc--; argv++;
	}


	if (p->iph.protocol == 0) {
		if (memcmp(p->name, "gre", 3) == 0)
			p->iph.protocol = IPPROTO_GRE;
		else if (memcmp(p->name, "ipip", 4) == 0)
			p->iph.protocol = IPPROTO_IPIP;
		else if (memcmp(p->name, "sit", 3) == 0)
			p->iph.protocol = IPPROTO_IPV6;
		else if (memcmp(p->name, "isatap", 6) == 0) {
			p->iph.protocol = IPPROTO_IPV6;
			isatap++;
		} else if (memcmp(p->name, "vti", 3) == 0) {
			p->iph.protocol = IPPROTO_IPIP;
			p->i_flags |= VTI_ISVTI;
		}
	}

	if (p->iph.protocol == IPPROTO_IPIP || p->iph.protocol == IPPROTO_IPV6) {
		if ((p->i_flags & GRE_KEY) || (p->o_flags & GRE_KEY)) {
			fprintf(stderr, "Keys are not allowed with ipip and sit.\n");
			return -1;
		}
	}

	if (medium[0]) {
		p->link = if_nametoindex(medium);
		if (p->link == 0)
			return -1;
	}

	if (p->i_key == 0 && IN_MULTICAST(ntohl(p->iph.daddr))) {
		p->i_key = p->iph.daddr;
		p->i_flags |= GRE_KEY;
	}
	if (p->o_key == 0 && IN_MULTICAST(ntohl(p->iph.daddr))) {
		p->o_key = p->iph.daddr;
		p->o_flags |= GRE_KEY;
	}
	if (IN_MULTICAST(ntohl(p->iph.daddr)) && !p->iph.saddr) {
		fprintf(stderr, "Broadcast tunnel requires a source address.\n");
		return -1;
	}
	if (isatap)
		p->i_flags |= SIT_ISATAP;

	return 0;
}