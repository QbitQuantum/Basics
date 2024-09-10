const UCHAR *cmd_copy(const char *cmd)
{
	char nocmp = 0;
	cmd += *cmd + 2;
	if (optmatch(cmd, "nocmp")) {
		cmd += *cmd + 2;
		nocmp = 1;
	}
	if (optmatch(cmd, "from") == 0)
		errend(10); /* copy command error */
	readfile(pathfix(cmd + (4 + 2), 0), 0x0f);
	cmd += *cmd + 2;
	if (nocmp)
		len_filebuf = autodecomp2(SIZ_FILEBUF, filebuf0, len_filebuf);
	if (optmatch(cmd, "to") == 0)
		errend(10); /* copy command error */
	writefile(pathfix(cmd + (2 + 2), 1), 2, -1, 0x07);
	return cmd + (*cmd + 2);
}