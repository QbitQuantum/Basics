BEGIN_ZKIT

void* ThreadBase::threadFunc(void *arg)
{
	ThreadBase *thread = (ThreadBase *)arg;
	if (thread == 0) 
	{
		return 0; // error.
	}

	while (!thread->isTerminated()) 
	{
		if (thread->run() < 0) 
		{
			printf("\nthread=%d exit because of return value!", thread->getThreadId());
			break;
		}
	}

	thread->threadStopped();

	printf("\nthread exit: %d", thread->getThreadId());

	return 0;
}