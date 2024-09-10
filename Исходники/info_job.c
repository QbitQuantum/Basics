extern int scontrol_callerid(int argc, char **argv)
{
	int af, ver = 4;
	unsigned char ip_src[sizeof(struct in6_addr)],
		      ip_dst[sizeof(struct in6_addr)];
	uint32_t port_src, port_dst, job_id;
	network_callerid_msg_t req;
	char node_name[MAXHOSTNAMELEN], *ptr;

	if (argc == 5) {
		ver = strtoul(argv[4], &ptr, 0);
		if (ptr && ptr[0]) {
			error("Address family not an integer");
			return SLURM_ERROR;
		}
	}

	if (ver != 4 && ver != 6) {
		error("Invalid address family: %d", ver);
		return SLURM_ERROR;
	}

	af = ver == 4 ? AF_INET : AF_INET6;
	if (!inet_pton(af, argv[0], ip_src)) {
		error("inet_pton failed for '%s'", argv[0]);
		return SLURM_ERROR;
	}

	port_src = strtoul(argv[1], &ptr, 0);
	if (ptr && ptr[0]) {
		error("Source port not an integer");
		return SLURM_ERROR;
	}

	if (!inet_pton(af, argv[2], ip_dst)) {
		error("scontrol_callerid: inet_pton failed for '%s'", argv[2]);
		return SLURM_ERROR;
	}

	port_dst = strtoul(argv[3], &ptr, 0);
	if (ptr && ptr[0]) {
		error("Destination port not an integer");
		return SLURM_ERROR;
	}

	memcpy(req.ip_src, ip_src, 16);
	memcpy(req.ip_dst, ip_dst, 16);
	req.port_src = port_src;
	req.port_dst = port_dst;
	req.af = af;

	if (slurm_network_callerid(req, &job_id, node_name, MAXHOSTNAMELEN)
			!= SLURM_SUCCESS) {
		fprintf(stderr,
			"slurm_network_callerid: unable to retrieve callerid data from remote slurmd\n");
		return SLURM_FAILURE;
	} else if (job_id == (uint32_t)NO_VAL) {
		fprintf(stderr,
			"slurm_network_callerid: remote job id indeterminate\n");
		return SLURM_FAILURE;
	} else {
		printf("%u %s\n", job_id, node_name);
		return SLURM_SUCCESS;
	}
}