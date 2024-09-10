cmd_t *initCmd(char *host)
{
	cmd_t *rv = (cmd_t *)Malloc0(sizeof(cmd_t));
	if (host)
		rv->host = Strdup(host);
	return rv;
}