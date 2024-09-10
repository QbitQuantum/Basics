/**
 * bidirectional popen() call
 *
 * @param rwepipe - int array of size three
 * @param exe - program to run
 * @param argv - argument list
 * @return pid or -1 on error
 *
 * The caller passes in an array of three integers (rwepipe), on successful
 * execution it can then write to element 0 (stdin of exe), and read from
 * element 1 (stdout) and 2 (stderr).
 */
static int popenRWE(int *rwepipe, const char *exe, const char *const argv[])
{
	int in[2];
	int out[2];
	int err[2];
	int pid;
	int rc;

	rc = pipe(in);
	if (rc < 0)
		goto error_in;

	rc = pipe(out);
	if (rc < 0)
		goto error_out;

	rc = pipe(err);
	if (rc < 0)
		goto error_err;

	pid = fork();
	if (pid > 0) {
		/* parent */
		close(in[0]);
		close(out[1]);
		close(err[1]);
		rwepipe[0] = in[1];
		rwepipe[1] = out[0];
		rwepipe[2] = err[0];
		return pid;
	} else if (pid == 0) {
		/* child */
		close(in[1]);
		close(out[0]);
		close(err[0]);
		close(0);
		rc = dup(in[0]);
		close(1);
		rc = dup(out[1]);
		close(2);
		rc = dup(err[1]);

		execvp(exe, (char **)argv);
		exit(1);
	} else
		goto error_fork;

	return pid;

error_fork:
	close(err[0]);
	close(err[1]);
error_err:
	close(out[0]);
	close(out[1]);
error_out:
	close(in[0]);
	close(in[1]);
error_in:
	return -1;
}