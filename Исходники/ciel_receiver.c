/* main loop */
int main (void) {
	uint8_t string[SCANDALLONGSTRINGSIZE];
	/* can packet parameters */
	sion_entry entry;
	char dbfilename[MAX_LINE_LENGTH];
	struct timeval tstamp;

	/* set up signals */
	signal(SIGINT, shutdown_cleanly);
	signal(SIGINT, shutdown_cleanly);
	
	/* set up sqlite db */
	makedbfile(dbfilename, ACCURACY_DAY);
	FILE *textlog = fopen("../canlog/scandal.log", "a");


	if (checkdbfile(dbfilename)){
		init_sqlite3(&db, dbfilename, OLDDB);
		init_sqlite3(&dbsync, dbfilename, OLDDB);
		printf("CIEL: opening previous database....\n");
	}
	else {
		init_sqlite3(&db, dbfilename, NEWDB);
		init_sqlite3(&dbsync, dbfilename, OLDDB);
		printf("CIEL: creating new database...\n");
	}

	/* Set up sockets */
	int numbytes;
	int loopcounter;
	char receivequeue[MAX_SOCKET_BLOCK_LENGTH];

	//select() stuff
	fd_set master;
	fd_set read_fds;
	int fdmax;
	int fdcount;
	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	//socket for receiving SION data
	socket_init(&sockfd_sion, &sioninfo,
				CIELIN_SION_HOST, CIELIN_SION_PORT, SIONOUTHOST, SIONOUTPORT) ;
	//socket for sending sync requests and receiving their reply
	socket_init(&sockfd_sync, &syncinfo,
				CIELOUT_SYNC_HOST, CIELOUT_SYNC_PORT, SIONIN_SYNC_HOST, SIONIN_SYNC_PORT);
	//socket for receiving Seven data.
	socket_init(&sockfd_seven, &seveninfo, 
				CIELIN_SEVEN_HOST, CIELIN_SEVEN_PORT, SEVENOUTHOST, SEVENOUTPORT);
	//socket for sending these to something else eg scanalysis
	socket_init(&sockfd_telemout, &telemoutinfo,
				CIELOUT_OPEN_HOST, CIELOUT_OPEN_PORT, TELEM_TARGET_HOST , TELEM_TARGET_PORT) ;
	//socket for sending packed telemetry to something else eg sunswift live
	socket_init(&sockfd_telemout2, &telemoutinfo2,
				CIELOUT_OPEN_HOST2, CIELOUT_OPEN_PORT2, TELEM_TARGET_HOST2 , TELEM_TARGET_PORT2) ;


	//more select() stuff
	FD_SET(sockfd_sion, &master);
	FD_SET(sockfd_seven, &master);
	FD_SET(sockfd_sync, &master);
	fdmax = sockfd_sync;
	if (fdmax < sockfd_seven) //checking to make sure fdmax is the largest
		fdmax = sockfd_seven;
	if (fdmax < sockfd_sion)
		fdmax = sockfd_sion;
	fdmax++; //+1 as required by select()

	/* Set up threads */

	printf("CIEL: Setting up threads...\n ");
	pthread_t out_thread,  sync_thread_handler;
	int rc;
	rc = pthread_create(&out_thread, NULL, output_thread, NULL);
	if (rc) {
		printf("CIEL: ERROR: Return code from pthread_create for output thread is %d\n", rc);
		exit(-1);
	}
	/*
	rc = pthread_create(&sync_thread_handler, NULL, sync_thread, NULL);
	if (rc) {
		printf("CIEL: ERROR: Return code from pthread_create for sync thread is %d\n", rc);
		exit(-1);
	}
	*/


	//FIXME 
	/*
	int date_is_set=0;
	int number_of_seconds_since_epoch = 0;
	int delay = 0;
	*/

	printf("CIEL: Entering main receiver loop..\n");
	while ( loop ) {
		read_fds = master;
		if (select(fdmax, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(4);
		}

		for(fdcount = 0; fdcount <=fdmax; fdcount++ ) { //for all the socket descriptors....
			if(FD_ISSET(fdcount, &read_fds)) {
				if (fdcount == sockfd_sion ) {
					/* Receiving live telemetry stream */
					numbytes = socket_recv(&sockfd_sion, receivequeue, 
						SCANDALLONGSTRINGSIZE * SOCKET_BLOCK_LENGTH);
					gettimeofday(&tstamp, NULL); //hurry, grab the timestamp!
				}
				else if (fdcount == sockfd_seven) {
					/* Receiving live control car stream */
					numbytes = socket_recv(&sockfd_seven, receivequeue,
						SCANDALLONGSTRINGSIZE * SOCKET_BLOCK_LENGTH);
					gettimeofday(&tstamp, NULL); //hurry, grab the timestamp!
				}
				else if (fdcount == sockfd_sync) {
					/* Receiving solar car retransmission */
					numbytes = socket_recv(&sockfd_sync, receivequeue, 
						SCANDALLONGSTRINGSIZE * SOCKET_BLOCK_LENGTH);
					gettimeofday(&tstamp, NULL); //hurry, grab the timestamp!
				}
			}
		}

		/* Send packed frames to something else. Used in 2011 for sunswift live */
		socket_send(&sockfd_telemout2, receivequeue, SCANDALLONGSTRINGSIZE * SOCKET_BLOCK_LENGTH, telemoutinfo2);


		/*
		Since each ethernet packet contains multiple CAN packets, we unpack them
		one by one and process them individually.
		*/
		for (loopcounter=0; loopcounter < SOCKET_BLOCK_LENGTH; loopcounter++) {
			//extract an individual packet
			memmove(string, &receivequeue[(SCANDALLONGSTRINGSIZE*loopcounter)], SCANDALLONGSTRINGSIZE);

			//TODO: Fix the Scandal Channel messages etc timestamps to full 64-bit.

			
			longstringtoentry(string, &entry);
			entry.ciel_timestamp = (((uint64_t) tstamp.tv_sec) * 1000) +
				( (uint64_t) lrintf( ((float) tstamp.tv_usec) / 1000 ) ); 

			entrytostring(&entry, string); //we don't send everything to scanalysis
			socket_send(&sockfd_telemout, string, SCANDALSTRINGSIZE, telemoutinfo); //to scanalysis
			//FIXME: plaintext log, not needed
			
			fprintf(textlog,"%d\t%d\t%d\t%d\t%d\t%llu\t%llu\t%u\n\r", 
			entry.priority, 
			entry.message_type, 
			entry.source_address, 
			entry.specifics, 
			entry.value,
			entry.scandal_timestamp,
			entry.ciel_timestamp,
			entry.pkt_id);
			

			queue_can_packet(db, &entry, SQLITE_BLOCKLEN); //duplicate packets are ignored by sqlite

			/* Debug function. Do not print too much UART or you'll slow everything down. */
			#define SION_DEBUG
			#ifdef SION_DEBUG
				//printf_sion_entry(&entry);
				printf("%llu\t%u\n\r", entry.scandal_timestamp, entry.pkt_id); 
			#endif
		} //end processing individual packets
	}// end infinite loop
	
	shutdown_sqlite3(db);//why is this even here
	return 0; //makes compiler happy
}