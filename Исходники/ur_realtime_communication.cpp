void UrRealtimeCommunication::run() {
	uint8_t buf[2048];
	int bytes_read;
	memset(buf, 0, 2048);
	struct timeval timeout;
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(sockfd_, &readfds);
	print_debug("Realtime port: Got connection");
	connected_ = true;
	while (keepalive_) {
		while (connected_ && keepalive_) {
			timeout.tv_sec = 0; //do this each loop as selects modifies timeout
			timeout.tv_usec = 500000; // timeout of 0.5 sec
			select(sockfd_ + 1, &readfds, NULL, NULL, &timeout);
			bytes_read = recv(sockfd_, (char*) buf, 2048, 0);
			if (bytes_read > 0) {
				setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, (char *) &flag_, sizeof(int));
				robot_state_->unpack(buf);
				if (safety_count_ == safety_count_max_) {
					setSpeed(0., 0., 0., 0., 0., 0.);
				}
				safety_count_ += 1;
			} else {
				connected_ = false;
				CloseSocket(sockfd_);
			}
		}
		if (keepalive_) {
			//reconnect
            ofLog()<<"Realtime port: No connection. Is controller crashed? Will try to reconnect in 10 seconds..."<<endl;
			sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd_ < 0) {
				print_fatal("ERROR opening socket");
			}
			flag_ = 1;
			setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, (char *) &flag_,
					sizeof(int));
			setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, (char *) &flag_, 
					sizeof(int));
	
			setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, (char *) &flag_,
					sizeof(int));
			SetNonBlocking(sockfd_, true);
			while (keepalive_ && !connected_) {
				std::this_thread::sleep_for(std::chrono::seconds(10));
				fd_set writefds;

				connect(sockfd_, (struct sockaddr *) &serv_addr_,
						sizeof(serv_addr_));
				FD_ZERO(&writefds);
				FD_SET(sockfd_, &writefds);
				select(sockfd_ + 1, NULL, &writefds, NULL, NULL);
				int flag_len;
				getsockopt(sockfd_, SOL_SOCKET, SO_ERROR, (char*)&flag_, &flag_len);
				if (flag_ < 0) {
					print_error("Error re-connecting to RT port 30003. Is controller started? Will try to reconnect in 10 seconds...");
				} else {
					connected_ = true;
					print_info("Realtime port: Reconnected");
				}
			}
		}
	}
	setSpeed(0., 0., 0., 0., 0., 0.);
	CloseSocket(sockfd_);
}