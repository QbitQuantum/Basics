void play(pthread_cond_t *cond, struct service *service, struct horse *horses, size_t horse_num) {
	init_race(service);

	while(run) {
		_pthread_mutex_lock(service->mfinished);
		if (service->finished) {
			_pthread_mutex_unlock(service->mfinished);

			// send if someone is waiting
			_pthread_cond_broadcast(cond);
check_for_horses:
			_pthread_mutex_lock(service->mcur_run);
			if (!service->cur_run) {
				_pthread_mutex_unlock(service->mcur_run);	
				break;
			}
			else {
				_pthread_mutex_unlock(service->mcur_run);
				_sleep(1, 0);
				goto check_for_horses;
			}
		}
		_pthread_mutex_unlock(service->mfinished);	
		_sleep(1, 0);
		_pthread_cond_broadcast(cond);
	}

	post_race(service, horses, horse_num);
} 