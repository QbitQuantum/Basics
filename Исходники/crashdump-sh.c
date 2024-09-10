static int add_cmdline_param(char *cmdline, uint64_t addr, char *cmdstr,
				char *byte)
{
	int cmdlen, len, align = 1024;
	char str[COMMAND_LINE_SIZE], *ptr;

	/* Passing in =xxxK / =xxxM format. Saves space required in cmdline.*/
	switch (byte[0]) {
		case 'K':
			if (addr%align)
				return -1;
			addr = addr/align;
			break;
		case 'M':
			addr = addr/(align *align);
			break;
	}
	ptr = str;
	strcpy(str, cmdstr);
	ptr += strlen(str);
	ultoa(addr, ptr);
	strcat(str, byte);
	len = strlen(str);
	cmdlen = strlen(cmdline) + len;
	if (cmdlen > (COMMAND_LINE_SIZE - 1))
		die("Command line overflow\n");
	strcat(cmdline, str);
#if DEBUG
	fprintf(stderr, "Command line after adding elfcorehdr: %s\n", cmdline);
#endif
	return 0;
}