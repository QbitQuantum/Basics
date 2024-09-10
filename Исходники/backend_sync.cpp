void* BackendSync::_run_thread(void *arg){
	struct run_arg *p = (struct run_arg*)arg;
	BackendSync *backend = (BackendSync *)p->backend;
	Link *link = (Link *)p->link;
	delete p;

	//
	link->noblock(false);

	SSDB *ssdb = (SSDB *)backend->ssdb;
	SyncLogQueue *logs = ssdb->replication->logs;

	Client client(backend);
	client.link = link;
	client.init();

	int idle = 0;
	while(!backend->thread_quit){
		// TEST: simulate slow network
		#ifndef NDEBUG
		//usleep(1000 * 1000);
		#endif

		if(client.status == Client::OUT_OF_SYNC){
			// TODO: tell slave to clear database
			client.reset_sync();
		}

		bool is_empty = true;
		if(client.iter){
			is_empty = false;
			client.dump();
		}
		if(client.sync(logs)){
			is_empty = false;
		}
		if(is_empty){
			idle ++;
			if(idle == 10){
				idle = 0;
				if(link->send("noop") == -1){
					log_debug("fd: %d, send error", link->fd());
					break;
				}
			}
			// sleep longer to reduce logs.find
			usleep(200 * 1000);
		}else{
			idle = 0;
		}

		if(link->flush() == -1){
			log_debug("fd: %d, send error", link->fd());
			break;
		}
	}

	log_info("SyncClient quit, fd: %d, delete link", link->fd());
	delete link;

	Locking l(&backend->mutex);
	backend->workers.erase(pthread_self());
	return (void *)NULL;
}