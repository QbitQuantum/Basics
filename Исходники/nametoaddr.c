/*
 * Convert a port name to its port and protocol numbers.
 * We assume only TCP or UDP.
 * Return 0 upon failure.
 */
int
pcap_nametoport(const char *name, int *port, int *proto)
{
	struct servent *sp;
	char *other;

	sp = getservbyname(name, (char *)0);
	if (sp != NULL) {
		NTOHS(sp->s_port);
		*port = sp->s_port;
		*proto = pcap_nametoproto(sp->s_proto);
		/*
		 * We need to check /etc/services for ambiguous entries.
		 * If we find the ambiguous entry, and it has the
		 * same port number, change the proto to PROTO_UNDEF
		 * so both TCP and UDP will be checked.
		 */
		if (*proto == IPPROTO_TCP)
			other = "udp";
		else
			other = "tcp";

		sp = getservbyname(name, other);
		if (sp != 0) {
			NTOHS(sp->s_port);
#ifdef notdef
			if (*port != sp->s_port)
				/* Can't handle ambiguous names that refer
				   to different port numbers. */
				warning("ambiguous port %s in /etc/services",
					name);
#endif
			*proto = PROTO_UNDEF;
		}
		return 1;
	}
#if defined(ultrix) || defined(__osf__)
	/* Special hack in case NFS isn't in /etc/services */
	if (strcmp(name, "nfs") == 0) {
		*port = 2049;
		*proto = PROTO_UNDEF;
		return 1;
	}
#endif
	return 0;
}