int main(int argc, char **argv)
{
    int i, c, ret, errflag = 0;
    char s[6];
    
    while ((c = getopt_long(argc, argv, "A:F:p:lrRvVw?", longopts, 0)) != EOF)
	switch (c) {
	case 'A': nway_advertise = parse_media(optarg); break;
	case 'F': fixed_speed = parse_media(optarg); break;
	case 'p': override_phy = atoi(optarg); break;
	case 'r': opt_restart++;	break;
	case 'R': opt_reset++;		break;
	case 'v': verbose++;		break;
	case 'V': opt_version++;	break;
	case 'w': opt_watch++;		break;
	case 'l': opt_log++;		break;
	case '?': errflag++;
	}
    /* Check for a few inappropriate option combinations */
    if (opt_watch) verbose = 0;
    if (errflag || (fixed_speed & (fixed_speed-1)) ||
	(fixed_speed && (opt_restart || nway_advertise))) {
	fprintf(stderr, usage, argv[0]);
	return 2;
    }

    if (opt_version)
	printf(version);

    /* Open a basic socket. */
    if ((skfd = socket(AF_INET, SOCK_DGRAM,0)) < 0) {
	perror("socket");
	exit(-1);
    }

    /* No remaining args means show all interfaces. */
    if (optind == argc) {
	ret = 1;
	for (i = 0; i < MAX_ETH; i++) {
	    sprintf(s, "eth%d", i);
	    ret &= do_one_xcvr(skfd, s, 1);
	}
	if (ret)
	    fprintf(stderr, "no MII interfaces found\n");
    } else {
	ret = 0;
	for (i = optind; i < argc; i++) {
	    ret |= do_one_xcvr(skfd, argv[i], 0);
	}
    }

    if (opt_watch && (ret == 0)) {
	while (1) {
	    sleep(1);
	    if (optind == argc) {
		for (i = 0; i < MAX_ETH; i++) {
		    sprintf(s, "eth%d", i);
		    watch_one_xcvr(skfd, s, i);
		}
	    } else {
		for (i = optind; i < argc; i++)
		    watch_one_xcvr(skfd, argv[i], i-optind);
	    }
	}
    }

    close(skfd);
    return ret;
}