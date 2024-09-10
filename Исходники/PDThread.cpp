/**
 * \brief 쓰레드를 시작
 *
 * \param priority 우선순위
 *
 * \return 0:ok, -1:error
 */
int Thread::start(Priority priority/*=InheritPriority*/)
{
	setPriority(priority);

	d->stop = false;
#ifndef WIN32

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//does not work pthread_join with PTHRAD_CREATE_DETACHED
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (d->priority == InheritPriority)
	{
		pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
	}
	else
	{
		int prio;
		int schedPolicy;
		if (pthread_attr_getschedpolicy(&attr, &schedPolicy) == 0) 
		{
			int prioMin = sched_get_priority_min(schedPolicy);
			int prioMax = sched_get_priority_max(schedPolicy);
			if (prioMin != -1 && prioMax != -1) 
			{
				if (d->priority == IdlePriority) prio = prioMin;
				else if (d->priority == TimeCriticalPriority) prio = prioMax;
				else
				{
					prio = (((prioMax - prioMin) / TimeCriticalPriority) * 
						d->priority) + prioMin;
					prio = std::max(prioMin, std::min(prioMax, prio));
				}

				sched_param sp;
				sp.sched_priority = prio;

				if (pthread_attr_setinheritsched(&attr, 
					PTHREAD_EXPLICIT_SCHED) != 0
					|| pthread_attr_setschedpolicy(&attr, schedPolicy) != 0
					|| pthread_attr_setschedparam(&attr, &sp) != 0) 
				{
					pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
				}

			} //if (prioMin != -1 && prioMax != -1) 

		} //if (pthread_attr_getschedpolicy(&attr, &schedPolicy) == 0) 
	}

	int n = ::pthread_create(&d->handle, &attr, Thread::run2, this);
	if (n == EPERM)
	{
		// permission error
		pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
		n = pthread_create(&d->handle, &attr, Thread::run2, this);
	}

	pthread_attr_destroy(&attr);

	if (n)
	{
		return -1;
	}
#else
	unsigned int thrdAddr = 0;
	d->handle = (HANDLE)_beginthreadex(NULL,0,Thread::run2,this,0,&thrdAddr);
	if (d->handle == 0) return -1;
	SetThreadPriority(d->handle,THREAD_PRIORITY_BELOW_NORMAL);
#endif
	
	return 0;
}