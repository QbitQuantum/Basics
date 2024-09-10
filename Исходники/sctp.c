static void
sctp_print_address(union sctp_sockstore *address, int port, int num_port)
{
	struct servent *sp = 0;
	char line[80], *cp;
	int width;

	switch (address->sa.sa_family) {
#ifdef INET
	case AF_INET:
		sprintf(line, "%.*s.", Wflag ? 39 : 16, inetname(&address->sin.sin_addr));
		break;
#endif
#ifdef INET6
	case AF_INET6:
		sprintf(line, "%.*s.", Wflag ? 39 : 16, inet6name(&address->sin6.sin6_addr));
		break;
#endif
	default:
		sprintf(line, "%.*s.", Wflag ? 39 : 16, "");
		break;
	}
	cp = strchr(line, '\0');
	if (!num_port && port)
		sp = getservbyport((int)port, "sctp");
	if (sp || port == 0)
		sprintf(cp, "%.15s ", sp ? sp->s_name : "*");
	else
		sprintf(cp, "%d ", ntohs((u_short)port));
	width = Wflag ? 45 : 22;
	printf("%-*.*s ", width, width, line);
}