int main(int ac, char **av)
{
	int c, i, nnodes=0;
	long node=-1;
	char *end;
	char shortopts[array_len(opts)*2 + 1];
	struct bitmask *mask = NULL;

	get_short_opts(opts,shortopts);
	while ((c = getopt_long(ac, av, shortopts, opts, NULL)) != -1) {
		switch (c) {
		case 's': /* --show */
			show();
			exit(0);
		case 'H': /* --hardware */
			nopolicy();
			hardware();
			exit(0);
		case 'i': /* --interleave */
			checknuma();
			mask = numactl_parse_nodestring(optarg);
			if (!mask) {
				printf ("<%s> is invalid\n", optarg);
				usage();
			}

			errno = 0;
			setpolicy(MPOL_INTERLEAVE);
			if (shmfd >= 0)
				numa_interleave_memory(shmptr, shmlen, mask);
			else
				numa_set_interleave_mask(mask);
			checkerror("setting interleave mask");
			break;
		case 'N': /* --cpunodebind */
		case 'c': /* --cpubind */
			dontshm("-c/--cpubind/--cpunodebind");
			checknuma();
			mask = numactl_parse_nodestring(optarg);
			if (!mask) {
				printf ("<%s> is invalid\n", optarg);
				usage();
			}
			errno = 0;
			check_cpubind(do_shm);
			did_cpubind = 1;
			numa_run_on_node_mask(mask);
			checkerror("sched_setaffinity");
			break;
		case 'C': /* --physcpubind */
		{
			struct bitmask *cpubuf;
			dontshm("-C/--physcpubind");
			cpubuf = numa_parse_cpustring(optarg);
			if (!cpubuf) {
				printf ("<%s> is invalid\n", optarg);
				usage();
			}
			errno = 0;
			check_cpubind(do_shm);
			did_cpubind = 1;
			numa_sched_setaffinity(0, cpubuf);
			checkerror("sched_setaffinity");
			free(cpubuf);
			break;
		}
		case 'm': /* --membind */
			checknuma();
			setpolicy(MPOL_BIND);
			mask = numactl_parse_nodestring(optarg);
			if (!mask) {
				printf ("<%s> is invalid\n", optarg);
				usage();
			}
			errno = 0;
			numa_set_bind_policy(1);
			if (shmfd >= 0) {
				numa_tonodemask_memory(shmptr, shmlen, mask);
			} else {
				numa_set_membind(mask);
			}
			numa_set_bind_policy(0);
			checkerror("setting membind");
			break;
		case 'p': /* --preferred */
			checknuma();
			setpolicy(MPOL_PREFERRED);
			mask = numactl_parse_nodestring(optarg);
			if (!mask) {
				printf ("<%s> is invalid\n", optarg);
				usage();
			}
			for (i=0; i<mask->size; i++) {
				if (numa_bitmask_isbitset(mask, i)) {
					node = i;
					nnodes++;
				}
			}
			if (nnodes != 1)
				usage();
			numa_bitmask_free(mask);
			errno = 0;
			numa_set_bind_policy(0);
			if (shmfd >= 0)
				numa_tonode_memory(shmptr, shmlen, node);
			else
				numa_set_preferred(node);
			checkerror("setting preferred node");
			break;
		case 'l': /* --local */
			checknuma();
			setpolicy(MPOL_DEFAULT);
			errno = 0;
			if (shmfd >= 0)
				numa_setlocal_memory(shmptr, shmlen);
			else
				numa_set_localalloc();
			checkerror("local allocation");
			break;
		case 'S': /* --shm */
			check_cpubind(did_cpubind);
			nopolicy();
			attach_sysvshm(optarg, "--shm");
			shmattached = 1;
			break;
		case 'f': /* --file */
			check_cpubind(did_cpubind);
			nopolicy();
			attach_shared(optarg, "--file");
			shmattached = 1;
			break;
		case 'L': /* --length */
			noshm("--length");
			shmlen = memsize(optarg);
			break;
		case 'M': /* --shmmode */
			noshm("--shmmode");
			shmmode = strtoul(optarg, &end, 8);
			if (end == optarg || *end)
				usage();
			break;
		case 'd': /* --dump */
			if (shmfd < 0)
				complain(
				"Cannot do --dump without shared memory.\n");
			dump_shm();
			do_dump = 1;
			break;
		case 'D': /* --dump-nodes */
			if (shmfd < 0)
				complain(
			    "Cannot do --dump-nodes without shared memory.\n");
			dump_shm_nodes();
			do_dump = 1;
			break;
		case 't': /* --strict */
			did_strict = 1;
			numa_set_strict(1);
			break;
		case 'I': /* --shmid */
			shmid = strtoul(optarg, &end, 0);
			if (end == optarg || *end)
				usage();
			break;

		case 'u': /* --huge */
			noshm("--huge");
			shmflags |= SHM_HUGETLB;
			break;

		case 'o':  /* --offset */
			noshm("--offset");
			shmoffset = memsize(optarg);
			break;			

		case 'T': /* --touch */
			needshm("--touch");
			check_shmbeyond("--touch");
			numa_police_memory(shmptr, shmlen);
			break;

		case 'V': /* --verify */
			needshm("--verify");
			if (set_policy < 0)
				complain("Need a policy first to verify");
			check_shmbeyond("--verify");
			numa_police_memory(shmptr, shmlen);
			if (!mask)
				complain("Need a mask to verify");
			else
				verify_shm(set_policy, mask);
			break;

		default:
			usage();
		}
	}

	av += optind;
	ac -= optind;

	if (shmfd >= 0) {
		if (*av)
			usage();
		exit(exitcode);
	}

	if (did_strict)
		fprintf(stderr,
			"numactl: warning. Strict flag for process ignored.\n");

	if (do_dump)
		usage_msg("cannot do --dump|--dump-shm for process");

	if (shmoption)
		usage_msg("shm related option %s for process", shmoption);
	
	if (*av == NULL)
		usage();
	execvp(*av, av);
	complain("execution of `%s': %s\n", av[0], strerror(errno));
	return 0; /* not reached */
}