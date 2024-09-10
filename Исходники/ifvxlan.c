static
DECL_CMD_FUNC(setvxlan_group, addr, d)
{
	struct ifvxlancmd cmd;
	struct addrinfo *ai;
	struct sockaddr *sa;
	int error;

	bzero(&cmd, sizeof(cmd));

	if ((error = getaddrinfo(addr, NULL, NULL, &ai)) != 0)
		errx(1, "error in parsing group address string: %s",
		    gai_strerror(error));

	sa = ai->ai_addr;

	switch (ai->ai_family) {
#ifdef INET
	case AF_INET: {
		struct in_addr addr = ((struct sockaddr_in *)sa)->sin_addr;

		if (!IN_MULTICAST(ntohl(addr.s_addr)))
			errx(1, "group address must be multicast");

		cmd.vxlcmd_sa.in4.sin_family = AF_INET;
		cmd.vxlcmd_sa.in4.sin_addr = addr;
		break;
	}
#endif
#ifdef INET6
	case AF_INET6: {
		struct in6_addr *addr = &((struct sockaddr_in6 *)sa)->sin6_addr;

		if (!IN6_IS_ADDR_MULTICAST(addr))
			errx(1, "group address must be multicast");

		cmd.vxlcmd_sa.in6.sin6_family = AF_INET6;
		cmd.vxlcmd_sa.in6.sin6_addr = *addr;
		break;
	}
#endif
	default:
		errx(1, "group address %s not supported", addr);
	}

	freeaddrinfo(ai);

	if (!vxlan_exists(s)) {
		if (cmd.vxlcmd_sa.sa.sa_family == AF_INET) {
			params.vxlp_with |= VXLAN_PARAM_WITH_REMOTE_ADDR4;
			params.vxlp_remote_in4 = cmd.vxlcmd_sa.in4.sin_addr;
		} else {
			params.vxlp_with |= VXLAN_PARAM_WITH_REMOTE_ADDR6;
			params.vxlp_remote_in6 = cmd.vxlcmd_sa.in6.sin6_addr;
		}
		return;
	}

	if (do_cmd(s, VXLAN_CMD_SET_REMOTE_ADDR, &cmd, sizeof(cmd), 1) < 0)
		err(1, "VXLAN_CMD_SET_REMOTE_ADDR");
}