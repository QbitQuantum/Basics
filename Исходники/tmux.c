int
main(int argc, char **argv)
{
	char		*path, *label, **var, tmp[PATH_MAX];
	const char	*s;
	int		 opt, flags, keys;

#if defined(DEBUG) && defined(__OpenBSD__)
	malloc_options = (char *) "AFGJPX";
#endif

	setlocale(LC_TIME, "");
	tzset();

	if (**argv == '-')
		flags = CLIENT_LOGIN;
	else
		flags = 0;

	label = path = NULL;
	while ((opt = getopt(argc, argv, "2c:Cdf:lL:qS:uUVv")) != -1) {
		switch (opt) {
		case '2':
			flags |= CLIENT_256COLOURS;
			break;
		case 'c':
			free(shell_cmd);
			shell_cmd = xstrdup(optarg);
			break;
		case 'C':
			if (flags & CLIENT_CONTROL)
				flags |= CLIENT_CONTROLCONTROL;
			else
				flags |= CLIENT_CONTROL;
			break;
		case 'V':
			printf("%s %s\n", __progname, VERSION);
			exit(0);
		case 'f':
			set_cfg_file(optarg);
			break;
		case 'l':
			flags |= CLIENT_LOGIN;
			break;
		case 'L':
			free(label);
			label = xstrdup(optarg);
			break;
		case 'q':
			break;
		case 'S':
			free(path);
			path = xstrdup(optarg);
			break;
		case 'u':
			flags |= CLIENT_UTF8;
			break;
		case 'v':
			debug_level++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (shell_cmd != NULL && argc != 0)
		usage();

#ifdef __OpenBSD__
	if (pledge("stdio rpath wpath cpath flock fattr unix sendfd recvfd "
	    "proc exec tty ps", NULL) != 0)
		err(1, "pledge");
#endif

	/*
	 * tmux is a UTF-8 terminal, so if TMUX is set, assume UTF-8.
	 * Otherwise, if the user has set LC_ALL, LC_CTYPE or LANG to contain
	 * UTF-8, it is a safe assumption that either they are using a UTF-8
	 * terminal, or if not they know that output from UTF-8-capable
	 * programs may be wrong.
	 */
	if (getenv("TMUX") != NULL)
		flags |= CLIENT_UTF8;
	else {
		s = getenv("LC_ALL");
		if (s == NULL || *s == '\0')
			s = getenv("LC_CTYPE");
		if (s == NULL || *s == '\0')
			s = getenv("LANG");
		if (s == NULL || *s == '\0')
			s = "";
		if (strcasestr(s, "UTF-8") != NULL ||
		    strcasestr(s, "UTF8") != NULL)
			flags |= CLIENT_UTF8;
	}

	global_environ = environ_create();
	for (var = environ; *var != NULL; var++)
		environ_put(global_environ, *var);
	if (getcwd(tmp, sizeof tmp) != NULL)
		environ_set(global_environ, "PWD", tmp);

	global_options = options_create(NULL);
	options_table_populate_tree(server_options_table, global_options);

	global_s_options = options_create(NULL);
	options_table_populate_tree(session_options_table, global_s_options);
	options_set_string(global_s_options, "default-shell", "%s", getshell());

	global_w_options = options_create(NULL);
	options_table_populate_tree(window_options_table, global_w_options);

	/* Override keys to vi if VISUAL or EDITOR are set. */
	if ((s = getenv("VISUAL")) != NULL || (s = getenv("EDITOR")) != NULL) {
		if (strrchr(s, '/') != NULL)
			s = strrchr(s, '/') + 1;
		if (strstr(s, "vi") != NULL)
			keys = MODEKEY_VI;
		else
			keys = MODEKEY_EMACS;
		options_set_number(global_s_options, "status-keys", keys);
		options_set_number(global_w_options, "mode-keys", keys);
	}

	/*
	 * Figure out the socket path. If specified on the command-line with -S
	 * or -L, use it, otherwise try $TMUX or assume -L default.
	 */
	if (path == NULL) {
		/* If no -L, use the environment. */
		if (label == NULL) {
			s = getenv("TMUX");
			if (s != NULL) {
				path = xstrdup(s);
				path[strcspn (path, ",")] = '\0';
				if (*path == '\0') {
					free(path);
					label = xstrdup("default");
				}
			} else
				label = xstrdup("default");
		}

		/* -L or default set. */
		if (label != NULL) {
			if ((path = makesocketpath(label)) == NULL) {
				fprintf(stderr, "can't create socket: %s\n",
				    strerror(errno));
				exit(1);
			}
		}
	}
	free(label);

	if (strlcpy(socket_path, path, sizeof socket_path) >=
	    sizeof socket_path) {
		fprintf(stderr, "socket path too long: %s\n", path);
		exit(1);
	}
	free(path);

	/* Pass control to the client. */
	exit(client_main(osdep_event_init(), argc, argv, flags));
}