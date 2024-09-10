int main(int argc, const char **argv)
{
	NET_API_STATUS status;
	struct libnetapi_ctx *ctx = NULL;
	const char *hostname = NULL;
	uint8_t *buffer = NULL;
	uint32_t entries_read = 0;
	uint32_t total_entries = 0;
	uint32_t resume_handle = 0;
	int i;

	struct USER_INFO_0 *info0;

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

	pc = poptGetContext("user_enum", argc, argv, long_options, 0);

	poptSetOtherOptionHelp(pc, "hostname");
	while((opt = poptGetNextOpt(pc)) != -1) {
	}

	if (!poptPeekArg(pc)) {
		poptPrintHelp(pc, stderr, 0);
		goto out;
	}
	hostname = poptGetArg(pc);

	/* NetUserEnum */

	do {
		status = NetUserEnum(hostname,
				     0,
				     0,
				     &buffer,
				     (uint32_t)-1,
				     &entries_read,
				     &total_entries,
				     &resume_handle);
		if (status == 0 || status == ERROR_MORE_DATA) {
			info0 = (struct USER_INFO_0 *)buffer;
			for (i=0; i<entries_read; i++) {
				printf("user %d: %s\n", i, info0->usri0_name);
				info0++;
			}
			NetApiBufferFree(buffer);
		}
	} while (status == ERROR_MORE_DATA);

	if (status != 0) {
		printf("NetUserEnum failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
	}

 out:
	libnetapi_free(ctx);
	poptFreeContext(pc);

	return status;
}