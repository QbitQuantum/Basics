string get_reply(string ip, string msg){
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	//add thread id to the end of message
	msg = msg + "_" + uint_to_str((unsigned int)pthread_self());
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(ip.c_str(), SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return "";
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to bind socket\n");
		return "";
	}

	if ((numbytes = sendto(sockfd, msg.c_str(), strlen(msg.c_str()), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		return "";
	}
	freeaddrinfo(servinfo);
	close(sockfd);
	cond_wait cw;
	time(&cw.time);
	if (pthread_mutex_init(cw.mutex, NULL) != 0) {
		perror("pthread_mutex_init() error");
		return "";
	}
	if (pthread_cond_init(cw.cond, NULL) != 0) {
		perror("pthread_cond_init() error");
		return "";
	}
	if (pthread_mutex_lock(cw.mutex) != 0) {
		perror("pthread_mutex_lock() error");
		return "";
	}
	cw.thread_id = (unsigned int)pthread_self();
	waiting_list.push_back(cw);
	//cout<<"TID:"<<cw.thread_id<<","<<cw.cond<<","<<cw.mutex<<endl;
	if (pthread_cond_wait(cw.cond, cw.mutex) != 0) {
	    perror("pthread_cond_timedwait() error");
	    return "";
	}
	//cout<<"out of wait & wls="<<waiting_list.size()<<endl;
	string ret;
	for(int i = 0; i < waiting_list.size(); i++){
		if(waiting_list[i].thread_id == (unsigned int)pthread_self()){
			ret = waiting_list[i].return_val;
			waiting_list.erase(waiting_list.begin() + i);
			break;
		}
	}
	//cout<<"out of for & wls="<<waiting_list.size()<<endl;
	return ret;
}