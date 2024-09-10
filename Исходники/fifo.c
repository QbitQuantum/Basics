int main (int argc, char **argv)
{
	const char *pathname = "trash";
	const char buffer1[] = "hello world!\n";
	const char buffer2[] = "goodbye old world, hello new world!\n";
	char fdcontents1[sizeof(buffer1)];
	char fdcontents2[sizeof(buffer2)];
	int fifo1 = -1, fifo2 = -1, ret, op_num = 0;

	parse_args(argc, argv);
	/* FIXME eventually stdio streams should be harmless */
	close(0);
	logfp = fopen(LOG_FILE, "w");
	if (!logfp) {
		perror("could not open logfile");
		exit(1);
	}
	dup2(fileno(logfp), 1); /* redirect stdout and stderr to the log file */
	dup2(fileno(logfp), 2);
	if (!move_to_cgroup("freezer", "1", getpid())) {
		log_error("move_to_cgroup");
		exit(2);
	}

/* Open a first fifo, write to it, and unlink it */
label(mkfifo1,   ret, mkfifo(pathname, S_IRUSR|S_IWUSR));
label(open1,   fifo1, open(pathname, oflags));
label(setflags1, ret, setflags(fifo1));
label(write1,    ret, write(fifo1, buffer1, sizeof(buffer1)));
label(unlink,    ret, unlink(pathname));

/* Open a second fifo, write to it */
label(mkfifo2,   ret, mkfifo(pathname, S_IRUSR|S_IWUSR));
label(open2,   fifo2, open(pathname, oflags));
label(setflags2, ret, setflags(fifo2));
label(write2,    ret, write(fifo2, buffer2, sizeof(buffer2)));

/* Check fifo contents */
label(read1,     ret, read(fifo1, fdcontents1, sizeof(fdcontents1)));
	if (strcmp(buffer1, fdcontents1) != 0) {
		log("FAIL", "original fifo contents don't match.");
		ret = EXIT_FAILURE;
		goto out;
	}
label(read2,     ret, read(fifo2, fdcontents2, sizeof(fdcontents2)));
	if (strcmp(buffer2, fdcontents2) != 0) {
		log("FAIL", "new fifo contents don't match.");
		ret = EXIT_FAILURE;
		goto out;
	}
	ret = EXIT_SUCCESS;
out:
	if (ret != EXIT_SUCCESS)
		perror("ERROR");
	if (fifo1 > -1)
		close(fifo1);
	if (fifo2 > -1)
		close(fifo2);
	unlink(pathname);
	fclose(logfp);
	exit(ret);
}