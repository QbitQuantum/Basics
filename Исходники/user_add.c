int main(int argc, const char **argv)
{
	NET_API_STATUS status;
	struct libnetapi_ctx *ctx = NULL;
	const char *hostname = NULL;
	const char *username = NULL;
	const char *password = NULL;
	struct USER_INFO_1 info1;
	uint32_t parm_error = 0;

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

	pc = poptGetContext("user_add", argc, argv, long_options, 0);

	poptSetOtherOptionHelp(pc, "hostname username password");
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

	if (!poptPeekArg(pc)) {
		poptPrintHelp(pc, stderr, 0);
		goto out;
	}
	password = poptGetArg(pc);

	/* NetUserAdd */

	info1.usri1_name = username;
	info1.usri1_password = password;
	info1.usri1_password_age = 0;
	info1.usri1_priv = 0;
	info1.usri1_home_dir = NULL;
	info1.usri1_comment = "User created using Samba NetApi Example code";
	info1.usri1_flags = 0;
	info1.usri1_script_path = NULL;

	status = NetUserAdd(hostname,
			    1,
			    (uint8_t *)&info1,
			    &parm_error);
	if (status != 0) {
		printf("NetUserAdd failed with: %s\n",
			libnetapi_get_error_string(ctx, status));
	}

 out:
	libnetapi_free(ctx);
	poptFreeContext(pc);

	return status;
}