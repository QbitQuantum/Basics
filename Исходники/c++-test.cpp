	Profiler()
		: ProfilerBase( COR_PRF_MONITOR_ENTERLEAVE, GetEnv( txtProfileEnv ) ), 
		writer( GetEnv( binProfileEnv ) )
	{
		__inst = this;
	}