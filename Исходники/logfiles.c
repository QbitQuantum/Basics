static Logfile *	logfile_list (Logfile *log, char **args)
{
	Logfile *l;
	char *targets = NULL;

	say("Logfiles:");
	for (l = logfiles; l; l = l->next)
	{
		targets = logfile_get_targets(l);
		say("Log %2d [%s] logging %s is %s, file %s server %s targets %s",
			l->refnum, l->name, logtype[l->type],
			onoff[l->active],
			l->filename ? l->filename : "<NONE>", 
			l->servref == NOSERV ?  "ALL" : ltoa(l->servref),
			targets ? targets : "<NONE>");
		new_free(&targets);
	}
	return log;
}