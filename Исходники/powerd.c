static int
poweroff(const char *msg, char **cmd_argv)
{
	struct stat	statbuf;
	pid_t		pid, child;
	struct passwd	*pwd;
	char		*home, *user;
	char		ehome[] = "HOME=";
	char		euser[] = "LOGNAME=";
	int		status;
	char		**ca;

	if (mutex_trylock(&poweroff_mutex) != 0)
		return (0);

	if (stat("/dev/console", &statbuf) == -1 ||
	    (pwd = getpwuid(statbuf.st_uid)) == NULL) {
		(void) mutex_unlock(&poweroff_mutex);
		return (1);
	}

	if (msg)
		syslog(LOG_NOTICE, msg);

	if (*cmd_argv == NULL) {
		logerror("No command to run.");
		(void) mutex_unlock(&poweroff_mutex);
		return (1);
	}

	home = malloc(strlen(pwd->pw_dir) + sizeof (ehome));
	user = malloc(strlen(pwd->pw_name) + sizeof (euser));
	if (home == NULL || user == NULL) {
		free(home);
		free(user);
		logerror("No memory.");
		(void) mutex_unlock(&poweroff_mutex);
		return (1);
	}
	(void) strcpy(home, ehome);
	(void) strcat(home, pwd->pw_dir);
	(void) strcpy(user, euser);
	(void) strcat(user, pwd->pw_name);

	/*
	 * Need to simulate the user enviroment, minimaly set HOME, and USER.
	 */
	if ((child = fork1()) == 0) {
		(void) putenv(home);
		(void) putenv(user);
		(void) setgid(pwd->pw_gid);
		(void) setuid(pwd->pw_uid);

		/*
		 * check for shutdown flag and set environment
		 */
		for (ca = cmd_argv; *ca; ca++) {
			if (strcmp("-h", *ca) == 0) {
				(void) putenv("SYSSUSPENDDODEFAULT=");
				break;
			}
		}

		(void) execv(cmd_argv[0], cmd_argv);
		exit(EXIT_FAILURE);
	} else {
		free(home);
		free(user);
		if (child == -1) {
			(void) mutex_unlock(&poweroff_mutex);
			return (1);
		}
	}
	pid = 0;
	while (pid != child)
		pid = wait(&status);
	if (WEXITSTATUS(status)) {
		(void) syslog(LOG_ERR, "Failed to exec \"%s\".", cmd_argv[0]);
		(void) mutex_unlock(&poweroff_mutex);
		return (1);
	}

	(void) mutex_unlock(&poweroff_mutex);
	return (0);
}