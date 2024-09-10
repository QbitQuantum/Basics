void bench(std::string cmd){
	int total = (int)ds->size();
	int finished = 0;
	int num_sent = 0;
	
	printf("========== %s ==========\n", cmd.c_str());

	std::map<std::string, Data *>::iterator it;
	it = ds->begin();
	
	double stime = millitime();
	while(1){
		while(!free_links->empty()){
			if(num_sent == total){
				break;
			}
			num_sent ++;

			Link *link = free_links->back();
			free_links->pop_back();
			
			send_req(link, cmd, it->second);
			it ++;
		}

		const Fdevents::events_t *events;
		events = fdes->wait(50);
		if(events == NULL){
			log_error("events.wait error: %s", strerror(errno));
			break;
		}

		for(int i=0; i<(int)events->size(); i++){
			const Fdevent *fde = events->at(i);
			Link *link = (Link *)fde->data.ptr;

			int len = link->read();
			if(len <= 0){
				log_error("fd: %d, read: %d, delete link", link->fd(), len);
				exit(0);
			}

			const std::vector<Bytes> *resp = link->recv();
			if(resp == NULL){
				log_error("error");
				break;
			}else if(resp->empty()){
				continue;
			}else{
				if(resp->at(0) != "ok"){
					log_error("bad response: %s", resp->at(0).String().c_str());
					exit(0);
				}
				free_links->push_back(link);
				finished ++;
				if(finished == total){
					double etime = millitime();
					double ts = (stime == etime)? 1 : (etime - stime);
					double speed = total / ts;
					printf("qps: %d, time: %.3f s\n", (int)speed, ts);
					return;
				}
			}
		}
	}
}