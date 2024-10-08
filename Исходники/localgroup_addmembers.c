int main(int argc, const char **argv)
{
	NET_API_STATUS status;
	struct libnetapi_ctx *ctx = NULL;
	const char *hostname = NULL;
	const char *groupname = NULL;
	struct LOCALGROUP_MEMBERS_INFO_0 *g0;
	struct LOCALGROUP_MEMBERS_INFO_3 *g3;
	uint32_t total_entries = 0;
	uint8_t *buffer = NULL;
	uint32_t level = 3;
	const char **names = NULL;
	int i = 0;

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

	pc = poptGetContext("localgroup_addmembers", argc, argv, long_options, 0);

	poptSetOtherOptionHelp(pc, "hostname groupname member1 member2 ...");
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
	groupname = poptGetArg(pc);

	if (!poptPeekArg(pc)) {
		poptPrintHelp(pc, stderr, 0);
		goto out;
	}

	names = poptGetArgs(pc);
	for (i=0; names[i] != NULL; i++) {
		total_entries++;
	}

	switch (level) {
		case 0:
			status = NetApiBufferAllocate(sizeof(struct LOCALGROUP_MEMBERS_INFO_0) * total_entries,
						      (void **)&g0);
			if (status) {
				printf("NetApiBufferAllocate failed with: %s\n",
					libnetapi_get_error_string(ctx, status));
				goto out;
			}

			for (i=0; i<total_entries; i++) {
				if (!ConvertStringSidToSid(names[i], &g0[i].lgrmi0_sid)) {
					printf("could not convert sid\n");
					goto out;
				}
			}

			buffer = (uint8_t *)g0;
			break;
		case 3:
			status = NetApiBufferAllocate(sizeof(struct LOCALGROUP_MEMBERS_INFO_3) * total_entries,
						      (void **)&g3);
			if (status) {
				printf("NetApiBufferAllocate failed with: %s\n",
					libnetapi_get_error_string(ctx, status));
				goto out;
			}

			for (i=0; i<total_entries; i++) {
				g3[i].lgrmi3_domainandname = names[i];
			}

			buffer = (uint8_t *)g3;
			break;
		default:
			break;
	}

	/* NetLocalGroupAddMembers */

	status = NetLocalGroupAddMembers(hostname,
					 groupname,
					 level,
					 buffer,
					 total_entries);
	if (status != 0) {
		printf("NetLocalGroupAddMembers failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
	}

 out:
	libnetapi_free(ctx);
	poptFreeContext(pc);

	return status;
}