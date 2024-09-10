/*
 * Wrapper around Windows' brain-dead tmpfile().
 */
static FILE *
mkfb_tmpfile(void)
{
	FILE *f;
#if defined(_WIN32) /*[*/
	char *n;
#endif /*]*/

#if !defined(_WIN32) /*[*/
	f = tmpfile();
	if (f == NULL) {
		perror("tmpfile");
		exit(1);
	}
#else /*][*/
	n = _tempnam(NULL, "mkfb");
	if (n == NULL) {
		fprintf(stderr, "_tempnam failed.\n");
		exit(1);
	}
	f = fopen(n, "w+b");
	if (f == NULL) {
		fprintf(stderr, "_tempnam open(\"%s\") failed: %s\n",
			n, strerror(errno));
		exit(1);
	}
	free(n);
#endif /*]*/

	return f;
}