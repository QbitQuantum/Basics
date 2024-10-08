int main(int argc, const char **argv)
{
	NET_API_STATUS status;
	struct libnetapi_ctx *ctx = NULL;
	const char *hostname = NULL;
	const char *username = NULL;
	uint32_t level = 0;
	uint8_t *buffer = NULL;
	uint32_t entries_read = 0;
	uint32_t total_entries = 0;
	int i;

	struct GROUP_USERS_INFO_0 *info0 = NULL;
	struct GROUP_USERS_INFO_1 *info1 = NULL;

	poptContext pc;
	int opt;

	struct poptOption long_options[] = {
		POPT_AUTOHELP
		POPT_COMMON_LIBNETAPI_EXAMPLES
		POPT_TABLEEND
	};

	status = libnetapi_init(&ctx);
	if (status != 0) {
		return status;
	}

	pc = poptGetContext("user_getgroups", argc, argv, long_options, 0);

	poptSetOtherOptionHelp(pc, "hostname username level");
	while((opt = poptGetNextOpt(pc)) != -1) {
	}

	if (!poptPeekArg(pc)) {
		poptPrintHelp(pc, stderr, 0);
		goto out;
	}
	hostname = poptGetArg(pc);

	if (!poptPeekArg(pc)) {
		poptPrintHelp(pc, stderr, 0);
		goto out;
	}
	username = poptGetArg(pc);

	if (poptPeekArg(pc)) {
		level = atoi(poptGetArg(pc));
	}

	/* NetUserGetGroups */

	do {
		status = NetUserGetGroups(hostname,
					  username,
					  level,
					  &buffer,
					  (uint32_t)-1,
					  &entries_read,
					  &total_entries);
		if (status == 0 || status == ERROR_MORE_DATA) {

			switch (level) {
				case 0:
					info0 = (struct GROUP_USERS_INFO_0 *)buffer;
					break;
				case 1:
					info1 = (struct GROUP_USERS_INFO_1 *)buffer;
					break;
				default:
					break;
			}

			for (i=0; i<entries_read; i++) {
				switch (level) {
					case 0:
						printf("#%d group: %s\n", i, info0->grui0_name);
						info0++;
						break;
					case 1:
						printf("#%d group: %s\n", i, info1->grui1_name);
						printf("#%d attributes: %d\n", i, info1->grui1_attributes);
						info1++;
						break;
					default:
						break;
				}
			}
			NetApiBufferFree(buffer);
		}
	} while (status == ERROR_MORE_DATA);

	if (status != 0) {
		printf("NetUserGetGroups failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
	}

 out:
	libnetapi_free(ctx);
	poptFreeContext(pc);

	return status;
}