static int writeTarFile(const int tar_fd, const int verboseFlag,
	const unsigned long dereferenceFlag, const llist_t *include,
	const llist_t *exclude, const int gzip)
{
	pid_t gzipPid = 0;
	int errorFlag = FALSE;
	struct TarBallInfo tbInfo;

	tbInfo.hlInfoHead = NULL;

	fchmod(tar_fd, 0644);
	tbInfo.tarFd = tar_fd;
	tbInfo.verboseFlag = verboseFlag;

	/* Store the stat info for the tarball's file, so
	 * can avoid including the tarball into itself....  */
	if (fstat(tbInfo.tarFd, &tbInfo.statBuf) < 0)
		bb_perror_msg_and_die("cannot stat tar file");

	if ((ENABLE_FEATURE_TAR_GZIP || ENABLE_FEATURE_TAR_BZIP2) && gzip) {
		int gzipDataPipe[2] = { -1, -1 };
		int gzipStatusPipe[2] = { -1, -1 };
		volatile int vfork_exec_errno = 0;
		const char *zip_exec = (gzip == 1) ? "gzip" : "bzip2";

		if (pipe(gzipDataPipe) < 0 || pipe(gzipStatusPipe) < 0)
			bb_perror_msg_and_die("pipe");

		signal(SIGPIPE, SIG_IGN); /* we only want EPIPE on errors */

#if defined(__GNUC__) && __GNUC__
		/* Avoid vfork clobbering */
		(void) &include;
		(void) &errorFlag;
		(void) &zip_exec;
#endif

		gzipPid = vfork();

		if (gzipPid == 0) {
			dup2(gzipDataPipe[0], 0);
			close(gzipDataPipe[1]);

			dup2(tbInfo.tarFd, 1);

			close(gzipStatusPipe[0]);
			fcntl(gzipStatusPipe[1], F_SETFD, FD_CLOEXEC);	/* close on exec shows success */

			BB_EXECLP(zip_exec, zip_exec, "-f", NULL);
			vfork_exec_errno = errno;

			close(gzipStatusPipe[1]);
			exit(-1);
		} else if (gzipPid > 0) {
			close(gzipDataPipe[0]);
			close(gzipStatusPipe[1]);

			while (1) {
				char buf;

				int n = full_read(gzipStatusPipe[0], &buf, 1);

				if (n == 0 && vfork_exec_errno != 0) {
					errno = vfork_exec_errno;
					bb_perror_msg_and_die("cannot exec %s", zip_exec);
				} else if ((n < 0) && (errno == EAGAIN || errno == EINTR))
					continue;	/* try it again */
				break;
			}
			close(gzipStatusPipe[0]);

			tbInfo.tarFd = gzipDataPipe[1];
		} else bb_perror_msg_and_die("vfork gzip");
	}

	tbInfo.excludeList = exclude;

	/* Read the directory/files and iterate over them one at a time */
	while (include) {
		if (!recursive_action(include->data, TRUE, dereferenceFlag,
				FALSE, writeFileToTarball, writeFileToTarball, &tbInfo, 0))
		{
			errorFlag = TRUE;
		}
		include = include->link;
	}
	/* Write two empty blocks to the end of the archive */
	memset(bb_common_bufsiz1, 0, 2*TAR_BLOCK_SIZE);
	xwrite(tbInfo.tarFd, bb_common_bufsiz1, 2*TAR_BLOCK_SIZE);

	/* To be pedantically correct, we would check if the tarball
	 * is smaller than 20 tar blocks, and pad it if it was smaller,
	 * but that isn't necessary for GNU tar interoperability, and
	 * so is considered a waste of space */

	/* Close so the child process (if any) will exit */
	close(tbInfo.tarFd);

	/* Hang up the tools, close up shop, head home */
	if (ENABLE_FEATURE_CLEAN_UP)
		freeHardLinkInfo(&tbInfo.hlInfoHead);

	if (errorFlag)
		bb_error_msg("error exit delayed from previous errors");

	if (gzipPid) {
		int status;
		if (waitpid(gzipPid, &status, 0) == -1)
			bb_perror_msg("waitpid");
		else if (!WIFEXITED(status) || WEXITSTATUS(status))
			/* gzip was killed or has exited with nonzero! */
			errorFlag = TRUE;
	}
	return errorFlag;
}