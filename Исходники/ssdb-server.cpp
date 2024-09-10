void run(int argc, char **argv){
	typedef std::vector<Link *> ready_list_t;
	ready_list_t ready_list;
	ready_list_t ready_list_2;
	ready_list_t::iterator it;
	const Fdevents::events_t *events;

	Fdevents select;
	select.set(serv_link->fd(), FDEVENT_IN, 0, serv_link);
	CommandProc proc(ssdb);

	while(!quit){
		if(!ready_list.empty()){
			// give links that are not in ready_list a chance
			events = select.wait(0);
		}else{
			events = select.wait(200);
		}
		if(events == NULL){
			log_fatal("events.wait error: %s", strerror(errno));
			break;
		}
		for(int i=0; i<(int)events->size(); i++){
			const Fdevent *fde = events->at(i);
			if(fde->data.ptr == serv_link){
				Link *link = serv_link->accept();
				if(link == NULL){
					log_error("accept fail!");
					continue;
				}
				//
				link->nodelay();
				link->noblock();
				//
				select.set(link->fd(), FDEVENT_IN, 1, link);
				log_info("new link: %d", link->fd());
			}else{
				Link *link = (Link *)fde->data.ptr;
				// 不能同时监听读和写事件, 只能监听其中一个
				if(fde->events & FDEVENT_IN){
					int len = link->read();
					log_trace("fd: %d read: %d", link->fd(), len);
					if(len <= 0){
						log_info("fd: %d, read: %d, delete link", link->fd(), len);
						select.del(link->fd());
						delete link;
					}else{
						ready_list.push_back(link);
					}
				}else if(fde->events & FDEVENT_OUT){
					int len = link->write();
					log_trace("fd: %d write: %d", link->fd(), len);
					if(len < 0){
						log_info("fd: %d, write: %d, delete link", link->fd(), len);
						select.del(link->fd());
						delete link;
					}else if(link->output->empty()){
						//log_trace("delete %d from select.out", link->fd());
						select.clr(link->fd(), FDEVENT_OUT);
						if(!link->input->empty()){
							ready_list.push_back(link);
						}else{
							//log_trace("add %d to select.in", link->fd());
							select.set(link->fd(), FDEVENT_IN, 1, link);
						}
					}
				}
			}
		}

		ready_list_2.clear();
		for(it = ready_list.begin(); it != ready_list.end(); it ++){
			Link *link = *it;

			const Request *req = link->recv();
			if(req == NULL){
				log_warn("fd: %d, link parse error, delete link", link->fd());
				select.del(link->fd());
				delete link;
				continue;
			}
			if(req->empty()){
				if(!select.isset(link->fd(), FDEVENT_IN)){
					//log_trace("add %d to select.in", link->fd());
					select.set(link->fd(), FDEVENT_IN, 1, link);
				}
				continue;
			}

			Response resp;
			int status = proc.proc(*link, *req, &resp);
			if(status == PROC_ERROR){
				log_info("fd: %d, proc error, delete link", link->fd());
				select.del(link->fd());
				delete link;
				continue;
			}else if(status == PROC_BACKEND){
				select.del(link->fd());
				continue;
			}

			if(link->send(resp) == -1){
				log_info("fd: %d, send error, delete link", link->fd());
				select.del(link->fd());
				delete link;
				continue;
			}

			if(!link->output->empty()){
				//log_trace("add %d to select.out", link->fd());
				select.set(link->fd(), FDEVENT_OUT, 1, link);
				if(select.isset(link->fd(), FDEVENT_IN)){
					//log_trace("delete %d from select.in", link->fd());
					select.clr(link->fd(), FDEVENT_IN);
				}
			}else{
				if(link->input->empty()){
					if(!select.isset(link->fd(), FDEVENT_IN)){
						//log_trace("add %d to select.in", link->fd());
						select.set(link->fd(), FDEVENT_IN, 1, link);
					}
				}else{
					if(select.isset(link->fd(), FDEVENT_IN)){
						//log_trace("delete %d from select.in", link->fd());
						select.clr(link->fd(), FDEVENT_IN);
					}
					ready_list_2.push_back(link);
				}
			}
		} // end foreach ready link
		ready_list.swap(ready_list_2);
	}
}