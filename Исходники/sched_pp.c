int main (int argc, char **argv)
{
	int do_get = 0;
	int do_set = 0;
	char *pvalue = NULL;
	pid_t pid=0;
	int priority=0;
	int policy = -1;
	int index;
	int c;

	printf("sched_pp (V1.0) (c) M.Behr, 2013\n");
	opterr = 0;

	while ((c = getopt (argc, argv, "gs:p:P:")) != -1)
		switch (c)
		{
		case 'g':
			do_get = 1;
			break;
		case 's':
			do_set = 1;
			priority = atol(optarg);
			break;
		case 'p':
			pvalue = optarg;
			pid=atol(pvalue);
			break;
		case 'P':
			if (!strcmp(optarg, "SCHED_FIFO")) policy = SCHED_FIFO;
			else if (!strcmp(optarg, "SCHED_RR")) policy = SCHED_RR;
			else if (!strcmp(optarg, "SCHED_OTHER")) policy = SCHED_OTHER;
			else{
				fprintf(stderr, "Unknown policy <%s>.\n", optarg);
				return 2;
			}
			break;
		case '?':
			if (optopt == 'p' || optopt == 's' || optopt == 'P')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr,
						"Unknown option character `\\x%x'.\n",
						optopt);
			return 1;
		default:
			abort ();
		}

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	if (!do_get && !do_set){
		printf("Usage:\nsched_pp -p <pid> [-g] [-s <priority>] [-P<policy=SCHED_FIFO|SCHED_RR|SCHED_OTHER>]\n");
	}

	if (do_get){
		print_params(pid, 0);
	}

	if (do_set){
		int cur_policy;
		/* print before */
		print_params(pid, &cur_policy);

		if (policy != -1){
			printf("trying to change pid %d to policy %d and priority %d:\n", pid, policy, priority);
			if (policy != SCHED_OTHER)
				set_policy(pid, policy, priority);
			else{
				set_policy(pid, policy, 0); /* SCHED_OTHER only allows 0 for that priority */
				set_priority(pid, policy, priority);
			}

		}else{
			printf("trying to change pid %d to priority %d:\n Params now:\n", pid, priority);
			set_priority(pid, cur_policy, priority);
		}
		/* print afterwards */
		print_params(pid, 0);
	}

	return 0;
}