static int ct_execv(void *a)
{
	struct execv_args *ea = a;
	sigset_t mask;

	sigfillset(&mask);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	/* This gets control in the container's new root (if any) */
	if (ea->env)
		execvpe(ea->path, ea->argv, ea->env);
	else
		execvp(ea->path, ea->argv);

	return -1;
}