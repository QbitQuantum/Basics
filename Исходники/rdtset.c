/**
 * @brief Execute command (fork, exec, wait)
 *
 * @param [in] argc number of cmd args
 * @param [in] argv cmd args
 *
 * @return Operation status
 * @retval 0 on success
 * @retval -1 on error
 */
static int
execute_cmd(int argc, char **argv)
{
	int i = 0;

	if (0 >= argc || NULL == argv)
		return -1;

	if (g_cfg.verbose) {
		printf("Trying to execute ");
		for (i = 0; i < argc; i++)
			printf("%s ", argv[i]);

		printf("\n");
	}

	pid_t pid = fork();

	if (-1 == pid) {
		fprintf(stderr, "%s,%s:%d Failed to execute %s !"
				" fork failed\n", __FILE__, __func__, __LINE__,
				argv[0]);
		return -1;
	} else if (0 < pid) {
		int status = EXIT_FAILURE;
		/* Wait for child */
		waitpid(pid, &status, 0);

		if (EXIT_SUCCESS != status)
			return -1;
	} else {
		/* set cpu affinity */
		if (0 != set_affinity(0)) {
			fprintf(stderr, "%s,%s:%d Failed to set core "
				"affinity!\n", __FILE__, __func__,
				__LINE__);
			_Exit(EXIT_FAILURE);
		}

		/* drop elevated root privileges */
		if (0 == g_cfg.sudo_keep && 0 != sudo_drop())
			_Exit(EXIT_FAILURE);

		errno = 0;
		/* execute command */
		execvp(argv[0], argv);

		fprintf(stderr, "%s,%s:%d Failed to execute %s, %s (%i) !\n",
				__FILE__, __func__, __LINE__,
				argv[0], strerror(errno), errno);

		_Exit(EXIT_FAILURE);
	}

	return 0;
}