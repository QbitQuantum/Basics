int
tclsh_main(int ac, char **av)
{
	char	cmd[MAXPATH];
	int	ret;
	pid_t	pid;

	sprintf(cmd, "%s/gui/bin/tclsh", bin);
	unless(executable(cmd)) {
		fprintf(stderr, "Cannot find the Tcl interpreter.\n");
		exit(1);
	}

	av[0] = cmd;
	spawn_tcl = 1;
	if ((pid = spawnvp(_P_NOWAIT, av[0], av)) < 0) {
		fprintf(stderr, "bk: cannot spawn %s\n", av[0]);
	}
	spawn_tcl = 0;
	if (waitpid(pid, &ret, 0) < 0) {
		return (126);
	} else if (!WIFEXITED(ret)) {
		return (127);
	} else {
		return (WEXITSTATUS(ret));
	}
}