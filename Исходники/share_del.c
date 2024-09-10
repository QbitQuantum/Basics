int main(int argc, const char **argv)
{
	NET_API_STATUS status;
	struct libnetapi_ctx *ctx = NULL;
	const char *hostname = NULL;
	const char *sharename = NULL;

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

	pc = poptGetContext("share_del", argc, argv, long_options, 0);

	poptSetOtherOptionHelp(pc, "hostname sharename");
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

	/* NetShareDel */

	status = NetShareDel(hostname,
			     sharename,
			     0);
	if (status != 0) {
		printf("NetShareDel failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
		goto out;
	}

 out:
	libnetapi_free(ctx);
	poptFreeContext(pc);

	return status;
}