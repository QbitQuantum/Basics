void DThinker::RunThinkers ()
{
	int i, count;

	ThinkCycles.Reset();
	BotSupportCycles.Reset();
	BotWTG = 0;

	ThinkCycles.Clock();

	// Tick every thinker left from last time
	for (i = STAT_FIRST_THINKING; i <= MAX_STATNUM; ++i)
	{
		TickThinkers (&Thinkers[i], NULL);
	}

	// Keep ticking the fresh thinkers until there are no new ones.
	do
	{
		count = 0;
		for (i = STAT_FIRST_THINKING; i <= MAX_STATNUM; ++i)
		{
			count += TickThinkers (&FreshThinkers[i], &Thinkers[i]);
		}
	} while (count != 0);

	ThinkCycles.Unclock();
}