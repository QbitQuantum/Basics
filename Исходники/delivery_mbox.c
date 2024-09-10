static void
delivery_mbox_open(struct deliver *deliver)
{
	char	*environ_new[2];

	environ_new[0] = "PATH=" _PATH_DEFPATH;
	environ_new[1] = (char *)NULL;
	environ = environ_new;

	if (deliver->from[0] == '\0')
		strlcpy(deliver->from, "MAILER-DAEMON", sizeof deliver->from);
	execle(PATH_MAILLOCAL, PATH_MAILLOCAL, "-f", deliver->from,
	    deliver->to, (char *)NULL, environ_new);
	perror("execle");
	_exit(1);
}