local void Ctimer(const char *cmd, const char *params, Player *p, const Target *target)
{
	Arena *arena = p->arena;
	int mins = 0, secs = 0;
	timerdata *td = P_ARENA_DATA(arena, tdkey);

	if (td->gamelen == 0)
	{
		char *end;
		mins = strtol(params, &end, 10);
		if (end != params)
		{
			if ((end = strchr(end, ':')))
				secs = strtol(end+1, NULL, 10);
			td->enabled = 1;
			td->timeout = TICK_MAKE(current_ticks()+(60*100*mins)+(100*secs));
			Ctime(cmd, params, p, target);
		}
		else chat->SendMessage(p, "timer format is: '?timer mins[:secs]'");
	}
	else chat->SendMessage(p, "Timer is fixed to Misc:TimedGame setting.");
}