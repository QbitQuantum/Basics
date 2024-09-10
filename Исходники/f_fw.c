static int fw_parse_opt(struct filter_util *qu, char *handle, int argc, char **argv, struct nlmsghdr *n)
{
	struct tc_police tp;
	struct tcmsg *t = NLMSG_DATA(n);
	struct rtattr *tail;
	__u32 mask = 0;
	int mask_set = 0;

	memset(&tp, 0, sizeof(tp));

	if (handle) {
		char *slash;
		if ((slash = strchr(handle, '/')) != NULL)
			*slash = '\0';
		if (get_u32(&t->tcm_handle, handle, 0)) {
			fprintf(stderr, "Illegal \"handle\"\n");
			return -1;
		}
		if (slash) {
			if (get_u32(&mask, slash+1, 0)) {
				fprintf(stderr, "Illegal \"handle\" mask\n");
				return -1;
			}
			mask_set = 1;
		}
	}

	if (argc == 0)
		return 0;

	tail = NLMSG_TAIL(n);
	addattr_l(n, 4096, TCA_OPTIONS, NULL, 0);

	if (mask_set)
		addattr32(n, MAX_MSG, TCA_FW_MASK, mask);

	while (argc > 0) {
		if (matches(*argv, "classid") == 0 ||
		    matches(*argv, "flowid") == 0) {
			unsigned handle;
			NEXT_ARG();
			if (get_tc_classid(&handle, *argv)) {
				fprintf(stderr, "Illegal \"classid\"\n");
				return -1;
			}
			addattr_l(n, 4096, TCA_FW_CLASSID, &handle, 4);
		} else if (matches(*argv, "police") == 0) {
			NEXT_ARG();
			if (parse_police(&argc, &argv, TCA_FW_POLICE, n)) {
				fprintf(stderr, "Illegal \"police\"\n");
				return -1;
			}
			continue;
		} else if (matches(*argv, "action") == 0) {
			NEXT_ARG();
			if (parse_action(&argc, &argv, TCA_FW_ACT, n)) {
				fprintf(stderr, "Illegal fw \"action\"\n");
				return -1;
			}
			continue;
		} else if (strcmp(*argv, "indev") == 0) {
			char d[IFNAMSIZ+1];
			memset(d, 0, sizeof (d));
			argc--;
			argv++;
			if (argc < 1) {
				fprintf(stderr, "Illegal indev\n");
				return -1;
			}
			strncpy(d, *argv, sizeof (d) - 1);
			addattr_l(n, MAX_MSG, TCA_FW_INDEV, d, strlen(d) + 1);
		} else if (strcmp(*argv, "help") == 0) {
			explain();
			return -1;
		} else {
			fprintf(stderr, "What is \"%s\"?\n", *argv);
			explain();
			return -1;
		}
		argc--; argv++;
	}
	tail->rta_len = (void *) NLMSG_TAIL(n) - (void *) tail;
	return 0;
}