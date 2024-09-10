void peer_main()
{
	// initialize the tables
	tracker_conn = -1;
	fileTable_Initialize();
	peerpeerTable_Initialize();

	// initialize the mutex
	peer_file_table_mutex	= (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	peer_peer_table_mutex	= (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(peer_file_table_mutex, NULL);
	pthread_mutex_init(peer_peer_table_mutex, NULL);

	//register peer_stop
	signal(SIGINT,peer_stop);

	myIP = my_ip();
	printf("%s Local ip address is %s\n", peer_trace, myIP);

	// try to connect to the tracker
	tracker_conn = connectToTracker();
	if (-1 == tracker_conn) {
		printf("%s Can't connect to tracker", peer_trace);
		return;
	}
	printf("%s Connection to the tracker established.\n", peer_trace);

	ptp_peer_t pkt;
	p2T_pkt_set(&pkt, 0, NULL, REGISTER, NULL, myIP, PEER_PORT, 0, NULL);

	if (sendpkt(tracker_conn, &pkt) < 0) {
		printf("%s REGISTER sending failed!\n", peer_trace);
		peer_stop();
		return;
	}

	// create the alive thread
	pthread_t alive_thread;
	pthread_create(&alive_thread, NULL, Alive, NULL);
	printf("%s Alive thread created.\n", peer_trace);

	// create a P2P Listen thread
	pthread_t p2p_listen_thread;
	pthread_create(&p2p_listen_thread, NULL, P2PListen, NULL);
	printf("%s p2p listen thread created.\n", peer_trace);
	
	// create a file monitor thread
	char dir_name[FILE_NAME_LEN];
	printf("%s Please input the directory which you would like to monitor:", peer_trace);
	scanf("%s", dir_name);

	// create a loval file directory to monitor
	mkdir(dir_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	chdir(dir_name);
	
	DIR *dir = opendir(".");
	if (dir == NULL) {
		printf("%s The directory which you input is invalid.\n", peer_trace);
		peer_stop();
		return;
	}
        struct dirent *entry;
	pthread_mutex_lock(peer_file_table_mutex);
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
			continue;
		}
		filenode tmp;
		memset(&tmp, 0, sizeof(filenode));
		strcpy(tmp.filename, entry->d_name);
		tmp.filesize = getFileSize(tmp.filename);
		if (tmp.filesize < 0) {
			continue;
		}
		tmp.timestamp = 0;
		strcpy(tmp.peerIP, myIP);
		fileTable_Add(&tmp, myIP);
	}
	pthread_mutex_unlock(peer_file_table_mutex);
	
	pthread_t file_monitor_thread;
	pthread_create(&file_monitor_thread, NULL, FileMonitor, (void *) ".");
	printf("%s file monitor thread created.\n", peer_trace);
	

//	int setup = 0;


	filenode *global_table;
	for (;;) {
		if (fileTable_Receive(tracker_conn, &global_table) < 0) {
			printf("%s Connection to the tracker is lost. Exiting...\n", peer_trace);
			break;
		}
		printf("%s Received a file table from the tracker:\n", peer_trace);
		fileTable_Print(global_table);
		pthread_mutex_lock(peer_file_table_mutex);

		// based on the global file table, update the local file table
		filenode *cur = global_table;
		while (cur != NULL) {
			if (cur != fileTable_Exist(global_table, cur->filename, NULL)) {
				// this file has been processed before
				cur = cur->next;
				continue;
			}

			filenode *tmp = fileTable_Exist(file_table, cur->filename, NULL);

			if (tmp == NULL) {
				// if our local file table doesn't have this file, should we add it?
				if (fileTable_Exist(global_table, cur->filename, myIP) != NULL) {
					// if this ip used to have the file in the global table, that means we just deleted locally, but the tracker hasn't updated it yet
					// thus we should not add this file, cause the delete action is the latest one
					cur = cur->next;
					continue;
				}
				else {
					// if this ip never has this file, we should add it
					fileTable_Add(cur, "");
					Download(cur->filename, cur->filesize, global_table);
				}
			}

			// if out local file table has this file, should we update it?
			else {
				// if this file is newly created but hasn't been marked with a timestamp from the tracker
				if (tmp->timestamp == 0) {
//					filenode *p = fileTable_Exist(global_table, cur->filename, myIP);
//					if (p != NULL && p->timestamp == fileTable_latest(global_table, cur->filename)) {
//						// update the timestamp given from the tracker
						tmp->timestamp = cur->timestamp;
//					}
//					else {
//						// some peer created this new file with the same name first or updated it first
//						// then we shuold change our name
//						strcat(strcat(tmp->name, " from "), myIP);
//					}
				}
				else {
					if (difftime(tmp->timestamp, cur->timestamp) >= 0) {
						// this file is the latest one, do nothing
						cur = cur->next;
						continue;
					}
					else {
						// not the latest one
						// need to update
						//remove(cur->filename);
						//fileTable_Add(cur, myIP);
						tmp->filesize = cur->filesize;
						tmp->timestamp = cur->timestamp;
						memset(tmp->peerIP, 0, IP_LEN);
						Download(cur->filename, cur->filesize, global_table);
					}
				}
			}
			cur = cur->next;
		}

//		if (setup > 0) {
//		//traverse the local file table to see if there's anything need to be deleted
			cur = file_table;
			while (cur != NULL) {
				if (fileTable_Exist(global_table, cur->filename, NULL) == NULL/* && cur->timestamp != 0*/) {
					// the global table doesn't have this file and the timestamp used to be assigned by the tracker
					remove(cur->filename);
					fileTable_Delete(cur->filename, myIP);
					// what if we can't delete this file
				}
				cur = cur->next;
			}
//		}
//		setup++;
		
		printf("%s Updated local file table:\n", peer_trace);
		fileTable_Print(file_table);
		fileTable_Destroy(global_table);
		pthread_mutex_unlock(peer_file_table_mutex);
	}

	peer_stop();
}