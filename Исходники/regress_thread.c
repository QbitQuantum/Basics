static void
thread_conditions_simple(void *arg)
{
	struct timeval tv_signal, tv_timeout, tv_broadcast;
	struct alerted_record alerted[NUM_THREADS];
	THREAD_T threads[NUM_THREADS];
	struct cond_wait cond;
	int i;
	struct timeval launched_at;
	struct event wake_one;
	struct event wake_all;
	struct basic_test_data *data = arg;
	struct event_base *base = data->base;
	int n_timed_out=0, n_signal=0, n_broadcast=0;

	tv_signal.tv_sec = tv_timeout.tv_sec = tv_broadcast.tv_sec = 0;
	tv_signal.tv_usec = 30*1000;
	tv_timeout.tv_usec = 150*1000;
	tv_broadcast.tv_usec = 500*1000;

	EVTHREAD_ALLOC_LOCK(cond.lock, EVTHREAD_LOCKTYPE_RECURSIVE);
	EVTHREAD_ALLOC_COND(cond.cond);
	tt_assert(cond.lock);
	tt_assert(cond.cond);
	for (i = 0; i < NUM_THREADS; ++i) {
		memset(&alerted[i], 0, sizeof(struct alerted_record));
		alerted[i].cond = &cond;
	}

	/* Threads 5 and 6 will be allowed to time out */
	memcpy(&alerted[5].delay, &tv_timeout, sizeof(tv_timeout));
	memcpy(&alerted[6].delay, &tv_timeout, sizeof(tv_timeout));

	evtimer_assign(&wake_one, base, wake_one_timeout, &cond);
	evtimer_assign(&wake_all, base, wake_all_timeout, &cond);

	evutil_gettimeofday(&launched_at, NULL);

	/* Launch the threads... */
	for (i = 0; i < NUM_THREADS; ++i) {
		THREAD_START(threads[i], wait_for_condition, &alerted[i]);
	}

	/* Start the timers... */
	tt_int_op(event_add(&wake_one, &tv_signal), ==, 0);
	tt_int_op(event_add(&wake_all, &tv_broadcast), ==, 0);

	/* And run for a bit... */
	event_base_dispatch(base);

	/* And wait till the threads are done. */
	for (i = 0; i < NUM_THREADS; ++i)
		THREAD_JOIN(threads[i]);

	/* Now, let's see what happened. At least one of 5 or 6 should
	 * have timed out. */
	n_timed_out = alerted[5].timed_out + alerted[6].timed_out;
	tt_int_op(n_timed_out, >=, 1);
	tt_int_op(n_timed_out, <=, 2);

	for (i = 0; i < NUM_THREADS; ++i) {
		const struct timeval *target_delay;
		struct timeval target_time, actual_delay;
		if (alerted[i].timed_out) {
			TT_BLATHER(("%d looks like a timeout\n", i));
			target_delay = &tv_timeout;
			tt_assert(i == 5 || i == 6);
		} else if (evutil_timerisset(&alerted[i].alerted_at)) {
			long diff1,diff2;
			evutil_timersub(&alerted[i].alerted_at,
			    &launched_at, &actual_delay);
			diff1 = timeval_msec_diff(&actual_delay,
			    &tv_signal);
			diff2 = timeval_msec_diff(&actual_delay,
			    &tv_broadcast);
			if (labs(diff1) < labs(diff2)) {
				TT_BLATHER(("%d looks like a signal\n", i));
				target_delay = &tv_signal;
				++n_signal;
			} else {
				TT_BLATHER(("%d looks like a broadcast\n", i));
				target_delay = &tv_broadcast;
				++n_broadcast;
			}
		} else {
			TT_FAIL(("Thread %d never got woken", i));
			continue;
		}
		evutil_timeradd(target_delay, &launched_at, &target_time);
		test_timeval_diff_leq(&target_time, &alerted[i].alerted_at,
		    0, 50);
	}
	tt_int_op(n_broadcast + n_signal + n_timed_out, ==, NUM_THREADS);
	tt_int_op(n_signal, ==, 1);

end:
	EVTHREAD_FREE_LOCK(cond.lock, EVTHREAD_LOCKTYPE_RECURSIVE);
	EVTHREAD_FREE_COND(cond.cond);
}