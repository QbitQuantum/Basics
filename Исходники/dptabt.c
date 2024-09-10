/*-------------------------------------------------------------------------
 Run a single copy of the test.
 Return value is 0 on success.

 If childnum is > 0, this is a slave; otherwise, this is the master.

 Does the following steps:
 1. Initialize dpio and dptab
 2. Create a table
 3. Establish connections.
	a. Open a handle to address and subscribe the table from that peer.
	   Master subscribes as table2, all else as standard table.
	b. Send an "SU" packet to address requesting peer to publish the table to us
 4. Wait for a "SU" packet.
 5. publish the table to whoever sent "SU" to us.
 Loop appropriate number of times, doing:
	 6. Master sends an "IT" packet to next. On receipt of an "IT" packet,
		slaves send an "IT" packet to next. Master waits for "IT" packet.
	    Watch for iteration number in the IT packet.  If this is the time,
		freeze the dpio and dptab, spawn a replacement, and exit using the
		replacement's exit code.
	 7. If childnum == 0, this child is the master:
		c. Set a value in the table.  Use a max hop count of N.
		d. Wait until value appears in table2 (watch the callback).
		e. Print out how long it took to get there.
 Once the correct number of loops is done,
 8. If childnum == 0: Send a QQ packet to next, wait for QQ packet.
    If childnum > 0: Wait until QQ packet recieved, send QQ to next.
 9. Exit.

 N must be 2 or greater.

 For example:

 If N == 2, the launcher executes:
	dptabt wloop.dll 0 2.0.0.0          (host 1 = master)
	dptabt wloop.dll 1 1.0.0.0          (host 2 = slave)
 the sequence of events is
    host step action
    h1   #4  waits for SU
	h2   #3  subscribes to 1 from h1, sends "SU" to h1, waits for "sU"
	h1   #5  Gets "SU", publishes table 1 to h2
	h1   #6  subscribe's h2's table 1 onto table 2, sends "SU" to h2
	h2   #5  Gets "SU", publishes table 1 to h1
 and the variable's trip around the ring looks like this:
    master -> slave -> master again
 The only reason it doesn't continue on to the slave is that the
 max hop count was set to 2.
 (Interestingly, if another host connects to the master's table,
  whether or not they get a copy of the variable depends on whether
  they connect before the variable comes around again (yes), or after (no).
  This is a good reason to never use rings like this in real systems!)

 If N == 4, the launcher executes:
	dptabt wloop.dll 0 2.0.0.0          (host 1 = master)
	dptabt wloop.dll 1 3.0.0.0          (host 2 = slave)
	dptabt wloop.dll 2 4.0.0.0          (host 3 = slave)
	dptabt wloop.dll 3 1.0.0.0          (host 4 = slave)
 the sequence of events is
    host step action
    h1   #4  waits for SU
	h2   #3  subscribes to 1 from next, sends "SU" to next, waits for "SU"
	h3   #3  subscribes to 1 from next, sends "SU" to next, waits for "SU"
	h4   #3  subscribes to 1 from next, sends "SU" to next, waits for "SU"
	h1   #5  Gets "SU" from prev, publishes table 1 to prev
	h1   #6  subscribe's next's table 1 onto table 2, sends "SU" to next
	h2   #5  Gets "SU" from prev, publishes table 1 to prev
	h3   #5  Gets "SU" from prev, publishes table 1 to prev
	h4   #5  Gets "SU" from prev, publishes table 1 to prev
 and the variable's trip around the ring looks like this:
    h1 -> h2 -> h3 -> h4 -> h1 again
-------------------------------------------------------------------------*/
int
run_one_node(
	int childNum,
	char *sNextAdr,
	int loopTotal,
	int endLoopAt)
{
	dptab_t *tab;
	dp_result_t err;
	char key[10];
	char subkey[10];
	dptab_table_t *table;
	dptab_table_t *table2;
	dpio_t *dpio;
	playerHdl_t dest;
	unsigned char adrBuf[dp_MAX_ADR_LEN];
	commInitReq_t commInitReq;
	commScanAddrReq_t		scanReq;
	commScanAddrResp_t		scanResp;
	dp_transport_t dll;
	char nbuf[dpio_MAXLEN_UNRELIABLE];
	char dplogname[200];

	char fname[256];
	int startLoopAt = 0;
	int i;

	/* Set a timeout of 30 seconds */
	signal(SIGTIMER, timer_handler);
	alarm(30);

	results.thisHost = childNum;

	sprintf(fname, LOGNAME, childNum);
	if(loopTotal < 1) {	/* thawing */
		assert ((logFile = fopen(fname, "a")) != NULL);
		fprintf(logFile, "--Thawing--\n");
	} else
		assert ((logFile = fopen(fname, "w")) != NULL);
	#ifdef WIN32
		srand(GetTickCount());
	#endif

	/* 1. Initialize dpio and dptab */
	dpio_now = eclock();
	if(loopTotal < 1) {	/* thawing */
		/* Find our file */
		FILE* thawFile;
		sprintf(fname, FREEZENAME, childNum);
		printf("Node %d: Thawing from file %s.\n", childNum, fname);
		thawFile = fopen(fname, "r");
		assert (thawFile != NULL);

		/* Read everything from our file */
		fread(&startLoopAt,sizeof(int),1,thawFile);
		fread(&loopTotal,sizeof(int),1,thawFile);
		fread(&it_num,sizeof(int),1,thawFile);
		fread(&(results.n_hosts),sizeof(int),1,thawFile);
		sprintf(dplogname, "dpt%d.%d.log", childNum, startLoopAt);
		dp_setLogFname(dplogname);

		err = dpio_create(&dpio, NULL, NULL, &dpio_now, thawFile);
		assert(err == dp_RES_OK);
		err = dpio_thawHdl(dpio, &dest, thawFile);
		assert(err == dp_RES_OK);

		tab = dptab_create(dpio);
		assert(tab);
		err = dptab_thaw(tab, thawFile);
		assert(err == dp_RES_OK);
		fclose(thawFile);

		/* Re-set any callbacks */
		key[0] = 1;
		table = dptab_getTable(tab, key, 1);
		assert(table != NULL);
		err = dptab_setTableCallback(table, table_cb, NULL);
		assert(err == dp_RES_OK);
		if(childNum == 0) {
			key[0] = 2;
			table2 = dptab_getTable(tab, key, 1);
			assert(table != NULL);
			err = dptab_setTableCallback(table2, table_cb, NULL);
			assert(err == dp_RES_OK);
		}
	} else {	/* not thawing */
		sprintf(dplogname, "dpt%d.%d.log", childNum,startLoopAt);
		dp_setLogFname(dplogname);
		printf("Node %d step 1\n", childNum);

		/* Create our dpio */
		memset(&dll, 0, sizeof(dll));
		strcpy(dll.fname, results.driver);
		memset(&commInitReq, 0, sizeof(commInitReq));
		commInitReq.sessionId = childNum + 1;			/* claim our address */
		commInitReq.portnum = childNum + PORT_OFFSET;	/* claim our port */
		commInitReq.reqLen = sizeof(commInitReq_t);
		err = dpio_create(&dpio, &dll, &commInitReq, &dpio_now, NULL);
		assert(err == dp_RES_OK);

		/* Find our next-in-ring */
		scanReq.printable = sNextAdr;
		scanReq.address = adrBuf;
		scanReq.size = sizeof(adrBuf);
		if (!commScanAddr(&scanReq, &scanResp)) {
			printf("Unable to scan next host address %s, err: %d",
					scanReq.printable, scanResp.status);
			assert(FALSE);
		}
		results.packetLoss = dpio->rxDropPercent;

		/* Create our table collection (dptab) */
		tab = dptab_create(dpio);
		assert(tab);

		/* 2. Create tables */
		printf("Node %d step 2\n", childNum);
		key[0] = 1;
		err = dptab_createTable(tab, &table, key, 1, sizeof(int), NULL, NULL, table_cb, NULL);
		assert(err == dp_RES_OK);
		if(childNum == 0) {
			key[0] = 2;
			err = dptab_createTable(tab, &table2, key, 1, sizeof(int), NULL, NULL, table_cb, NULL);
			assert(err == dp_RES_OK);
		}

		/* 3. Establish connections */
		printf("Node %d step 3\n", childNum);
		/*  Open a comm handle to the partner's address */
		dest = dpio_openHdl(dpio, adrBuf, NULL, NULL);
		if (dest == PLAYER_NONE) {
			printf("Unable to connect to address %s", scanReq.printable);
			assert(FALSE);
		}
		printf("Node %d: Opening address %s returns handle %d/%x\n", childNum, scanReq.printable, dest, dest);
		if (dest == PLAYER_ME) {
			printf("Executed out of order - got handle to myself\n");
			assert(FALSE);
		}

		/* Add the next machine to the party */
		err = dptab_addPeer(tab, dest);
		/* only master should have received packet from unknown source. */
		if ((childNum == 0) && (su_src == dest))
			assert(err == dp_RES_ALREADY);
		else
			assert(err == dp_RES_OK);

		/* Let the next machine publish on top of our table */
		key[0] = 1;
		if(childNum == 0)
			err = dptab_addPublisher(tab, table2, key, 1, dest);
		else
			err = dptab_addPublisher(tab, table, key, 1, dest);
		assert(err == dp_RES_OK);

		/* Request the next machine publish table to us */
		(*(dp_packetType_t *)nbuf) = PKT_SU;
		err = dpio_put_reliable(dpio, &dest, 1, nbuf, sizeof(dp_packetType_t)+2, NULL);
		assert(err == dp_RES_OK);
		printf("Node %d sent SU to h:%x\n", childNum, dest);

		/* 4. Wait for an "SU" packet. */
		printf("Node %d step 4: waiting for su.\n", childNum);
		su_src = PLAYER_NONE;
		do {
			poll_test(dpio, tab);
		} while (su_src == PLAYER_NONE);

		/* 5. publish the table to whoever sent "SU" to us. */
		printf("Node %d step 5\n", childNum);
		err = dptab_addPeer(tab, su_src);
		if (su_src == dest)
			assert(err == dp_RES_ALREADY);
		else
			assert(err == dp_RES_OK);
		err = dptab_addSubscriber(tab, table, su_src);
		assert(err == dp_RES_OK);
	}	/* not thawing */

	for(i = startLoopAt; i < loopTotal; i++) {
		/* 6. Send an IT packet around the ring. */
		printf("Node %d step 6.%d\n", childNum, i);
		if(childNum == 0) {	/* Master sends first IT. */
			(*(dp_packetType_t *)nbuf) = PKT_IT;
			nbuf[sizeof(dp_packetType_t)] = (char) (i & 0x7F);
			err = dpio_put_reliable(dpio, &dest, 1, nbuf,
						sizeof(dp_packetType_t)+sizeof(char), NULL);
			assert(err == dp_RES_OK);
		}
		printf("Node %d waiting for IT(%d).\n", childNum, i);
		do {				/* Wait for IT */
			poll_test(dpio, tab);
		} while (((int) it_num) < (i & 0x7F));
		if(childNum != 0) {	/* Slaves send IT after getting one. */
			(*(dp_packetType_t *)nbuf) = PKT_IT;
			nbuf[sizeof(dp_packetType_t)] = (char) i;
			err = dpio_put_reliable(dpio, &dest, 1, nbuf,
						sizeof(dp_packetType_t)+sizeof(char), NULL);
			assert(err == dp_RES_OK);
		}

		/* 7. If master, set a value and wait for it to come back around. */
		if(childNum == 0) {
			printf("Node %d step 7\n", childNum);
			subkey[0] = SUBKEY_SINGLE_SMALL;
			sprintf(nbuf, "a%03d", i);
			printf("Node %d: setting variable to %s\n", childNum, nbuf);
			results.sentSingleSmallTime = dpio_now;
			err = dptab_set(tab, table, subkey, 1, nbuf, strlen(nbuf), results.n_hosts, PLAYER_ME);
			if (err != dp_RES_OK) {
				printf("Node %d: dptab_set returns err %d!\n", childNum, err);
				assert(err == dp_RES_OK);
			}
		}

		/* Freeze and spawn if it's the right iteration. */
		/* Do it here to force an xfer to be saved and restored. */
		if(i == endLoopAt) {
			FILE* freezeFile;
			int result;
			int proc;

			/* Find our file */
			sprintf(fname, FREEZENAME, childNum);
			printf("Node %d: Iteration %d, Freezing to file %s.\n", childNum, i, fname);
			freezeFile = fopen(fname, "w");
			assert (freezeFile != NULL);

			/* Write everything to our file */
			fwrite(&i,sizeof(int),1,freezeFile);
			fwrite(&loopTotal,sizeof(int),1,freezeFile);
			fwrite(&it_num,sizeof(int),1,freezeFile);
			fwrite(&(results.n_hosts),sizeof(int),1,freezeFile);

			err = dpio_freeze(dpio, freezeFile);
			assert(err == dp_RES_OK);
			err = dpio_freezeHdl(dpio, dest, freezeFile);
			assert(err == dp_RES_OK);

			err = dptab_freeze(tab, freezeFile);
			assert(err == dp_RES_OK);
			fclose(freezeFile);
			dptab_destroy(tab);
			dpio_destroy(dpio, 1);

			/* Spawn and return child's return code */
			sprintf(buf, "%d", childNum);
			proc = _spawnl(_P_NOWAIT, results.exe, results.exe, buf, fname, NULL);
			_cwait(&result, proc, 0);
			printf("Node %d.%d returned %d.\n", childNum, i, result);
			return result;
		}

		if(childNum == 0) {
			/* d. Wait until value appears in table2 (callback). */
			printf("Node %d waiting for value to appear.\n", childNum);
			results.gotSingleSmallTime = -1;
			do {
				poll_test(dpio, tab);
			} while (results.gotSingleSmallTime == -1);
		}
	}

	/* 8. Send a QQ packet around the ring. */
	printf("Node %d step 8\n", childNum);
	qq_src = PLAYER_NONE;
	if(childNum == 0) {	/* Master sends first QQ */
		(*(dp_packetType_t *)nbuf) = PKT_QQ;
		err = dpio_put_reliable(dpio, &dest, 1, nbuf, sizeof(dp_packetType_t), NULL);
		assert(err == dp_RES_OK);
	}
	/* Wait for QQ */
	printf("Node %d waiting for QQ.\n", childNum);
	do {
		poll_test(dpio, tab);
	} while (qq_src == PLAYER_NONE);
	if(childNum != 0) {	/* Slaves wait for a QQ and then send QQ */
		(*(dp_packetType_t *)nbuf) = PKT_QQ;
		err = dpio_put_reliable(dpio, &dest, 1, nbuf, sizeof(dp_packetType_t), NULL);
		assert(err == dp_RES_OK);
	}

	/* 9. Exit. */
	printf("Node %d step 9\n", childNum);
	/* Ack packets for four more seconds just in case */
	{
		clock_t start = eclock();
		while ((long)(eclock() - start) < 4 * ECLOCKS_PER_SEC) {
			dpio_now = eclock();
			dpio_update(dpio);
		}
	}
	printf("Node %d exiting\n", childNum);
	return 0;
}