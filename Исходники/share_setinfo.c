int main(int argc, const char **argv)
{
	NET_API_STATUS status;
	struct libnetapi_ctx *ctx = NULL;
	const char *hostname = NULL;
	const char *sharename = NULL;
	const char *comment = "NetApi generated Share comment";
	uint32_t level = 1004;
	uint8_t *buffer = NULL;
	uint32_t parm_err = 0;

	struct SHARE_INFO_1004 i1004;

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

	pc = poptGetContext("share_setinfo", argc, argv, long_options, 0);

	poptSetOtherOptionHelp(pc, "hostname sharename comment");
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
	sharename = poptGetArg(pc);

	if (poptPeekArg(pc)) {
		comment = poptGetArg(pc);
	}

	/* NetShareSetInfo */
	switch (level) {
		case 1004:
			i1004.shi1004_remark = comment;
			buffer = (uint8_t *)&i1004;
			break;
		default:
			break;
	}

	status = NetShareSetInfo(hostname,
				 sharename,
				 level,
				 buffer,
				 &parm_err);
	if (status != 0) {
		printf("NetShareSetInfo failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
		goto out;
	}

 out:
	libnetapi_free(ctx);
	poptFreeContext(pc);

	return status;
}