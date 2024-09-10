static void eventpool_execute(uv_async_t *handle) {
	/*
	 * Make sure we execute in the main thread
	 */
	const uv_thread_t pth_cur_id = uv_thread_self();
	assert(uv_thread_equal(&pth_main_id, &pth_cur_id));

	struct threadpool_tasks_t **node = NULL;
	int nrlisteners1[REASON_END] = {0};
	int nr1 = 0, nrnodes = 16, nrnodes1 = 0, i = 0;

	if((node = MALLOC(sizeof(struct threadpool_tasks_t *)*nrnodes)) == NULL) {
		OUT_OF_MEMORY /*LCOV_EXCL_LINE*/
	}

	uv_mutex_lock(&listeners_lock);

	struct eventqueue_t *queue = NULL;
	while(eventqueue) {
		queue = eventqueue;
		uv_sem_t *ref = NULL;

#ifdef _WIN32
		if((nr1 = InterlockedExchangeAdd(&nrlisteners[queue->reason], 0)) == 0) {
#else
		if((nr1 = __sync_add_and_fetch(&nrlisteners[queue->reason], 0)) == 0) {
#endif
			if(queue->done != NULL) {
				queue->done((void *)queue->data);
			}
		} else {
			if(threads == EVENTPOOL_THREADED) {
				if((ref = MALLOC(sizeof(uv_sem_t))) == NULL) {
					OUT_OF_MEMORY /*LCOV_EXCL_LINE*/
				}
				uv_sem_init(ref, nr1-1);
			}

			struct eventpool_listener_t *listeners = eventpool_listeners;
			if(listeners == NULL) {
				if(queue->done != NULL) {
					queue->done((void *)queue->data);
				}
			}

			while(listeners) {
				if(listeners->reason == queue->reason) {
					if(nrnodes1 == nrnodes) {
						nrnodes *= 2;
						/*LCOV_EXCL_START*/
						if((node = REALLOC(node, sizeof(struct threadpool_tasks_t *)*nrnodes)) == NULL) {
							OUT_OF_MEMORY
						}
						/*LCOV_EXCL_STOP*/
					}
					if((node[nrnodes1] = MALLOC(sizeof(struct threadpool_tasks_t))) == NULL) {
						OUT_OF_MEMORY /*LCOV_EXCL_LINE*/
					}
					node[nrnodes1]->func = listeners->func;
					node[nrnodes1]->userdata = queue->data;
					node[nrnodes1]->done = queue->done;
					node[nrnodes1]->ref = ref;
					node[nrnodes1]->reason = listeners->reason;
					nrnodes1++;
					if(threads == EVENTPOOL_THREADED) {
						nrlisteners1[queue->reason]++;
					}
				}
				listeners = listeners->next;
			}
		}
		eventqueue = eventqueue->next;
		FREE(queue);
	}
	uv_mutex_unlock(&listeners_lock);

	if(nrnodes1 > 0) {
		for(i=0;i<nrnodes1;i++) {
			if(threads == EVENTPOOL_NO_THREADS) {
				nrlisteners1[node[i]->reason]++;
				node[i]->func(node[i]->reason, node[i]->userdata);

#ifdef _WIN32
				if(nrlisteners1[node[i]->reason] == InterlockedExchangeAdd(&nrlisteners[node[i]->reason], 0)) {
#else
				if(nrlisteners1[node[i]->reason] == __sync_add_and_fetch(&nrlisteners[node[i]->reason], 0)) {
#endif
					if(node[i]->done != NULL) {
						node[i]->done((void *)node[i]->userdata);
					}
					nrlisteners1[node[i]->reason] = 0;
				}
			} else {
				struct threadpool_data_t *tpdata = NULL;
				tpdata = MALLOC(sizeof(struct threadpool_data_t));
				if(tpdata == NULL) {
					OUT_OF_MEMORY /*LCOV_EXCL_LINE*/
				}
				tpdata->userdata = node[i]->userdata;
				tpdata->func = node[i]->func;
				tpdata->done = node[i]->done;
				tpdata->ref = node[i]->ref;
				tpdata->reason = node[i]->reason;
				tpdata->priority = reasons[node[i]->reason].priority;

				uv_work_t *tp_work_req = MALLOC(sizeof(uv_work_t));
				if(tp_work_req == NULL) {
					OUT_OF_MEMORY /*LCOV_EXCL_LINE*/
				}
				tp_work_req->data = tpdata;
				if(uv_queue_work(uv_default_loop(), tp_work_req, reasons[node[i]->reason].reason, fib, fib_free) < 0) {
					if(node[i]->done != NULL) {
						node[i]->done((void *)node[i]->userdata);
					}
					FREE(tpdata);
					FREE(node[i]->ref);
				}
			}
			FREE(node[i]);
		}
	}
	for(i=0;i<REASON_END;i++) {
		nrlisteners1[i] = 0;
	}
	FREE(node);
	uv_mutex_lock(&listeners_lock);
	if(eventqueue != NULL) {
		uv_async_send(async_req);
	}
	uv_mutex_unlock(&listeners_lock);
}