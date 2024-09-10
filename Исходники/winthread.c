int
pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mux)
{
	int x, last;

	pthread_mutex_lock(&cond->lock);
	cond->waiters++;
	pthread_mutex_unlock(&cond->lock);

	// this does a pthread_mutex_unlock on mux
	x = SignalObjectAndWait(mux->handle, cond->queue, INFINITE, FALSE);
	assert(x == 0);

	pthread_mutex_lock(&cond->lock);
	cond->waiters--;
	last = cond->broadcast && cond->waiters == 0;
	pthread_mutex_unlock(&cond->lock);

	if(last)
		SignalObjectAndWait(cond->done, mux->handle, INFINITE, FALSE);
	else
		pthread_mutex_lock(mux);
	return 0;
}