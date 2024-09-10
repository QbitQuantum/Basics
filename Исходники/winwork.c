osd_work_queue *osd_work_queue_alloc(int flags)
{
	int numprocs = effective_num_processors();
	osd_work_queue *queue;
	int threadnum;

	// allocate a new queue
	queue = (osd_work_queue *)malloc(sizeof(*queue));
	if (queue == NULL)
		goto error;
	memset(queue, 0, sizeof(*queue));

	// initialize basic queue members
	queue->tailptr = (osd_work_item **)&queue->list;
	queue->flags = flags;

	// allocate events for the queue
	queue->doneevent = CreateEvent(NULL, TRUE, TRUE, NULL);		// manual reset, signalled
	if (queue->doneevent == NULL)
		goto error;

	// initialize the critical section
	scalable_lock_init(&queue->lock);

	// determine how many threads to create...
	// on a single-CPU system, create 1 thread for I/O queues, and 0 threads for everything else
	if (numprocs == 1)
		queue->threads = (flags & WORK_QUEUE_FLAG_IO) ? 1 : 0;

	// on an n-CPU system, create (n-1) threads for multi queues, and 1 thread for everything else
	else
		queue->threads = (flags & WORK_QUEUE_FLAG_MULTI) ? (numprocs - 1) : 1;

	// clamp to the maximum
	queue->threads = MIN(queue->threads, WORK_MAX_THREADS);

	// allocate memory for thread array (+1 to count the calling thread)
	queue->thread = (work_thread_info *)malloc((queue->threads + 1) * sizeof(queue->thread[0]));
	if (queue->thread == NULL)
		goto error;
	memset(queue->thread, 0, (queue->threads + 1) * sizeof(queue->thread[0]));

	// iterate over threads
	for (threadnum = 0; threadnum < queue->threads; threadnum++)
	{
		work_thread_info *thread = &queue->thread[threadnum];
		uintptr_t handle;

		// set a pointer back to the queue
		thread->queue = queue;

		// create the per-thread wake event
		thread->wakeevent = CreateEvent(NULL, FALSE, FALSE, NULL);	// auto-reset, not signalled
		if (thread->wakeevent == NULL)
			goto error;

		// create the thread
		handle = _beginthreadex(NULL, 0, worker_thread_entry, thread, 0, NULL);
		thread->handle = (HANDLE)handle;
		if (thread->handle == NULL)
			goto error;

		// set its priority: I/O threads get high priority because they are assumed to be
		// blocked most of the time; other threads just match the creator's priority
		if (flags & WORK_QUEUE_FLAG_IO)
			SetThreadPriority(thread->handle, THREAD_PRIORITY_ABOVE_NORMAL);
		else
			SetThreadPriority(thread->handle, GetThreadPriority(GetCurrentThread()));
	}

	// start a timer going for "waittime" on the main thread
	begin_timing(queue->thread[queue->threads].waittime);
	return queue;

error:
	osd_work_queue_free(queue);
	return NULL;
}