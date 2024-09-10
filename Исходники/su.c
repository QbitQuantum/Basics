int
main(int argc, char **argv)
{
    int i, optind = 0;
    char *su_user;
    struct passwd *su_info;
    struct passwd *login_info;

    struct passwd *pwd;

    char *shell;

    int ok = 0;

    setprogname (argv[0]);

    if(getarg(args, sizeof(args) / sizeof(args[0]), argc, argv, &optind))
	usage(1);

    for (i=0; i < optind; i++)
      if (strcmp(argv[i], "-") == 0) {
	 full_login = 1;
	 break;
      }

    if(help_flag)
	usage(0);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }
    if(optind >= argc)
	su_user = "******";
    else
	su_user = argv[optind++];

    if (!issuid() && getuid() != 0)
	warnx("Not setuid and you are not root, expect this to fail");

    pwd = k_getpwnam(su_user);
    if(pwd == NULL)
	errx (1, "unknown login %s", su_user);
    if (pwd->pw_uid == 0 && strcmp ("root", su_user) != 0) {
	syslog (LOG_ALERT, "NIS attack, user %s has uid 0", su_user);
	errx (1, "unknown login %s", su_user);
    }
    su_info = dup_info(pwd);
    if (su_info == NULL)
	errx (1, "malloc: out of memory");

	pwd = getpwuid(getuid());
    if(pwd == NULL)
	errx(1, "who are you?");
    login_info = dup_info(pwd);
    if (login_info == NULL)
	errx (1, "malloc: out of memory");
    if(env_flag)
	shell = login_info->pw_shell;
    else
	shell = su_info->pw_shell;
    if(shell == NULL || *shell == '\0')
	shell = _PATH_BSHELL;


#ifdef KRB5
    if(kerberos_flag && ok == 0 &&
       krb5_verify(login_info, su_info, kerberos_instance) == 0)
	ok = 5;
#endif

    if(ok == 0 && login_info->pw_uid && verify_unix(login_info, su_info) != 0) {
	printf("Sorry!\n");
	exit(1);
    }

#ifdef HAVE_GETSPNAM
   {  struct spwd *sp;
      long    today;

    sp = getspnam(su_info->pw_name);
    if (sp != NULL) {
	today = time(0)/(24L * 60 * 60);
	if (sp->sp_expire > 0) {
	    if (today >= sp->sp_expire) {
		if (login_info->pw_uid)
		    errx(1,"Your account has expired.");
		else
		    printf("Your account has expired.");
            }
            else if (sp->sp_expire - today < 14)
                printf("Your account will expire in %d days.\n",
		       (int)(sp->sp_expire - today));
	}
	if (sp->sp_max > 0) {
	    if (today >= sp->sp_lstchg + sp->sp_max) {
		if (login_info->pw_uid)
		    errx(1,"Your password has expired. Choose a new one.");
		else
		    printf("Your password has expired. Choose a new one.");
	    }
	    else if (today >= sp->sp_lstchg + sp->sp_max - sp->sp_warn)
		printf("Your account will expire in %d days.\n",
		       (int)(sp->sp_lstchg + sp->sp_max -today));
	}
    }
    }
#endif
    {
	char *tty = ttyname (STDERR_FILENO);
	if (tty)
	    syslog (LOG_NOTICE | LOG_AUTH, "%s to %s on %s",
		    login_info->pw_name, su_info->pw_name, tty);
	else
	    syslog (LOG_NOTICE | LOG_AUTH, "%s to %s",
		    login_info->pw_name, su_info->pw_name);
    }


    if(!env_flag) {
	if(full_login) {
	    char *t = getenv ("TERM");
	    char **newenv = NULL;
	    int i, j;

	    i = read_environment(_PATH_ETC_ENVIRONMENT, &newenv);

	    environ = malloc ((10 + i) * sizeof (char *));
	    if (environ == NULL)
		err (1, "malloc");
	    environ[0] = NULL;

	    for (j = 0; j < i; j++) {
		char *p = strchr(newenv[j], '=');
		if (p == NULL)
		    errx(1, "enviroment '%s' missing '='", newenv[j]);
		*p++ = 0;
		esetenv (newenv[j], p, 1);
	    }
	    free(newenv);

	    esetenv ("PATH", _PATH_DEFPATH, 1);
	    if (t)
		esetenv ("TERM", t, 1);
	    if (chdir (su_info->pw_dir) < 0)
		errx (1, "no directory");
	}
	if (full_login || su_info->pw_uid)
	    esetenv ("USER", su_info->pw_name, 1);
	esetenv("HOME", su_info->pw_dir, 1);
	esetenv("SHELL", shell, 1);
    }

    {
	int i;
	char **args;
	char *p;

	p = strrchr(shell, '/');
	if(p)
	    p++;
	else
	    p = shell;

	if (strcmp(p, "csh") != 0)
	    csh_f_flag = 0;

        args = malloc(((cmd ? 2 : 0) + 1 + argc - optind + 1 + csh_f_flag) * sizeof(*args));
	if (args == NULL)
	    err (1, "malloc");
	i = 0;
	if(full_login) {
	    if (asprintf(&args[i++], "-%s", p) == -1)
		errx (1, "malloc");
	} else
	    args[i++] = p;
	if (cmd) {
	   args[i++] = "-c";
	   args[i++] = cmd;
	}

	if (csh_f_flag)
	    args[i++] = "-f";

	for (argv += optind; *argv; ++argv)
	   args[i++] = *argv;
	args[i] = NULL;

	if(setgid(su_info->pw_gid) < 0)
	    err(1, "setgid");
	if (initgroups (su_info->pw_name, su_info->pw_gid) < 0)
	    err (1, "initgroups");
	if(setuid(su_info->pw_uid) < 0
	   || (su_info->pw_uid != 0 && setuid(0) == 0))
	    err(1, "setuid");

#ifdef KRB5
        if (ok == 5)
           krb5_start_session();
#endif
	execve(shell, args, environ);
    }

    exit(1);
}