int
bgcmd(int argc, char **argv)
{
	struct job *jp;
	int i;

	nextopt("");
	do {
		jp = getjob(*argptr, 0);
		if (jp->jobctl == 0)
			error("job not created under job control");
		set_curjob(jp, 1);
		out1fmt("[%ld] %s", (long)(jp - jobtab + 1), jp->ps[0].cmd);
		for (i = 1; i < jp->nprocs; i++)
			out1fmt(" | %s", jp->ps[i].cmd );
		out1c('\n');
		flushall();
		restartjob(jp);
	} while (*argptr && *++argptr);
	return 0;
}