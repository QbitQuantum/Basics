PRIVATE void run_a_command ARGS1(char *, command)
{
	char **argv;
	int argc;
	char *str;
	int alen;

	alen = 10;
	argv = (char **)malloc(10 * sizeof(char *));
	if (argv == NULL)
	{
		return;
	}
	argc = 0;

	str = strtok(command, " \t\n");
	while (str != NULL)
	{
		argv[argc] = strdup(str);
		argc++;
		if (argc >= alen)
		{
			int i;
			char **tmp_av;

			tmp_av = (char **)malloc((alen + 10) * sizeof(char *));
			if (tmp_av == NULL)
			{
				return;
			}
			for (i=0; i<alen; i++)
			{
				tmp_av[i] = argv[i];
			}
			alen += 10;
			free((char *)argv);
			argv = tmp_av;
		}
		str = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;

	if (fork() == 0)
	{
		execvp(argv[0], argv);
	}
	else
	{
		int i;

		/*
		 * The signal handler in main.c will clean this child
		 * up when it exits.
		 */

		for (i=0; i<argc; i++)
		{
			if (argv[i] != NULL)
			{
				free(argv[i]);
			}
		}
		free((char *)argv);
	}
}