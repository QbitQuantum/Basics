void TimeoutJobIDs()
{
	double flCurTime = Plat_FloatTime();
	
	int iNext;
	for ( int i=g_JobMemories.Head(); i != g_JobMemories.InvalidIndex(); i=iNext )
	{
		iNext = g_JobMemories.Next( i );
		
		if ( (flCurTime - g_JobMemories[i].m_Time) > JOB_MEMORY_DURATION )
			g_JobMemories.Remove( i );
	}
}