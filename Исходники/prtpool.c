PR_JoinThreadPool(PRThreadPool *tpool)
{
PRStatus rval = PR_SUCCESS;
PRCList *head;
PRStatus rval_status;

	PR_Lock(tpool->jobq.lock);
	while (!tpool->shutdown)
		PR_WaitCondVar(tpool->shutdown_cv, PR_INTERVAL_NO_TIMEOUT);

	/*
	 * wakeup worker threads
	 */
#ifdef OPT_WINNT
	/*
	 * post shutdown notification for all threads
	 */
	{
		int i;
		for(i=0; i < tpool->current_threads; i++) {
			PostQueuedCompletionStatus(tpool->jobq.nt_completion_port, 0,
												TRUE, NULL);
		}
	}
#else
	PR_NotifyAllCondVar(tpool->jobq.cv);
#endif

	/*
	 * wakeup io thread(s)
	 */
	notify_ioq(tpool);

	/*
	 * wakeup timer thread(s)
	 */
	PR_Lock(tpool->timerq.lock);
	notify_timerq(tpool);
	PR_Unlock(tpool->timerq.lock);

	while (!PR_CLIST_IS_EMPTY(&tpool->jobq.wthreads)) {
		wthread *wthrp;

		head = PR_LIST_HEAD(&tpool->jobq.wthreads);
		PR_REMOVE_AND_INIT_LINK(head);
		PR_Unlock(tpool->jobq.lock);
		wthrp = WTHREAD_LINKS_PTR(head);
		rval_status = PR_JoinThread(wthrp->thread);
		PR_ASSERT(PR_SUCCESS == rval_status);
		PR_DELETE(wthrp);
		PR_Lock(tpool->jobq.lock);
	}
	PR_Unlock(tpool->jobq.lock);
	while (!PR_CLIST_IS_EMPTY(&tpool->ioq.wthreads)) {
		wthread *wthrp;

		head = PR_LIST_HEAD(&tpool->ioq.wthreads);
		PR_REMOVE_AND_INIT_LINK(head);
		wthrp = WTHREAD_LINKS_PTR(head);
		rval_status = PR_JoinThread(wthrp->thread);
		PR_ASSERT(PR_SUCCESS == rval_status);
		PR_DELETE(wthrp);
	}

	while (!PR_CLIST_IS_EMPTY(&tpool->timerq.wthreads)) {
		wthread *wthrp;

		head = PR_LIST_HEAD(&tpool->timerq.wthreads);
		PR_REMOVE_AND_INIT_LINK(head);
		wthrp = WTHREAD_LINKS_PTR(head);
		rval_status = PR_JoinThread(wthrp->thread);
		PR_ASSERT(PR_SUCCESS == rval_status);
		PR_DELETE(wthrp);
	}

	/*
	 * Delete queued jobs
	 */
	while (!PR_CLIST_IS_EMPTY(&tpool->jobq.list)) {
		PRJob *jobp;

		head = PR_LIST_HEAD(&tpool->jobq.list);
		PR_REMOVE_AND_INIT_LINK(head);
		jobp = JOB_LINKS_PTR(head);
		tpool->jobq.cnt--;
		delete_job(jobp);
	}

	/* delete io jobs */
	while (!PR_CLIST_IS_EMPTY(&tpool->ioq.list)) {
		PRJob *jobp;

		head = PR_LIST_HEAD(&tpool->ioq.list);
		PR_REMOVE_AND_INIT_LINK(head);
		tpool->ioq.cnt--;
		jobp = JOB_LINKS_PTR(head);
		delete_job(jobp);
	}

	/* delete timer jobs */
	while (!PR_CLIST_IS_EMPTY(&tpool->timerq.list)) {
		PRJob *jobp;

		head = PR_LIST_HEAD(&tpool->timerq.list);
		PR_REMOVE_AND_INIT_LINK(head);
		tpool->timerq.cnt--;
		jobp = JOB_LINKS_PTR(head);
		delete_job(jobp);
	}

	PR_ASSERT(0 == tpool->jobq.cnt);
	PR_ASSERT(0 == tpool->ioq.cnt);
	PR_ASSERT(0 == tpool->timerq.cnt);

	delete_threadpool(tpool);
	return rval;
}