mlt_slices mlt_slices_init( int threads, int policy, int priority )
{
	pthread_attr_t tattr;
	struct sched_param param;
	mlt_slices ctx = (mlt_slices)calloc( 1, sizeof( struct mlt_slices_s ) );
	char *env = getenv( ENV_SLICES );
#ifdef _WIN32
	#if _WIN32_WINNT >= 0x0601
		int cpus = GetActiveProcessorCount( ALL_PROCESSOR_GROUPS );
	#else
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		int cpus = info.dwNumberOfProcessors;
	#endif
#else
	int cpus = sysconf( _SC_NPROCESSORS_ONLN );
#endif
	int i, env_val = env ? atoi(env) : 0;

	/* check given threads count */
	if ( !env || !env_val )
	{
		if ( threads < 0 )
			threads = -threads * cpus;
		else if ( !threads )
			threads = cpus;
	}
	else if ( env_val < 0 )
	{
		if ( threads < 0 )
			threads = env_val * threads * cpus;
		else if ( !threads )
			threads = -env_val * cpus;
		else
			threads = -env_val * threads;
	}
	else // env_val > 0
	{
		if ( threads < 0 )
			threads = env_val * threads;
		else if ( !threads )
			threads = env_val;
	}
	if ( threads > MAX_SLICES )
		threads = MAX_SLICES;

	ctx->count = threads;

	/* init attributes */
	pthread_mutex_init ( &ctx->cond_mutex, NULL );
	pthread_cond_init ( &ctx->cond_var_job, NULL );
	pthread_cond_init ( &ctx->cond_var_ready, NULL );
	pthread_attr_init( &tattr );
	if ( policy < 0 )
		policy = SCHED_OTHER;
	if ( priority < 0 )
		priority = sched_get_priority_max( policy );
	pthread_attr_setschedpolicy( &tattr, policy );
	param.sched_priority = priority;
	pthread_attr_setschedparam( &tattr, &param );

	/* run worker threads */
	for ( i = 0; i < ctx->count; i++ )
	{
		pthread_create( &ctx->threads[i], &tattr, mlt_slices_worker, ctx );
		pthread_setschedparam( ctx->threads[i], policy, &param);
	}

	pthread_attr_destroy( &tattr );

	/* return context */
	return ctx;
}