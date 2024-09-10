static int cmd_get(connection_context *c)
{
	static const char* var_version = "version";
	static const char* var_codepage = "codepage";
	char *cmdline;
	int res = 0;

	cmdline = strchr(c->cmd, ' ');
	if (!cmdline) {
		goto finish;
	}
	++cmdline;
	int l;
	if ((strstr(cmdline, var_version) == cmdline) &&
            (cmdline[l = strlen(var_version)] == 0)) {
		hprintf(c->pipe, "version 0x%04X\n", VERSION);
	} else if ((strstr(cmdline, var_codepage) == cmdline) &&
	            (cmdline[l = strlen(var_codepage)] == 0)) {
		hprintf(c->pipe, "codepage %d\n", GetOEMCP());
	} else {
		hprintf(c->pipe, "error Unknown argument (%s)\n", c->cmd);
	    goto finish;
	}
	res = 1;
finish:
	return res;
}