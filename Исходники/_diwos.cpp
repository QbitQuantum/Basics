void update() {
	int i;

	// ACCUMUALTE contribution statistics for those accounts that have open work orders
	int weightingSum = 0;
	for( i=0; i<accounts.count; i++ ) {
		if( accounts[i]->activeWorkOrderCount > 0 ) {
			weightingSum += accounts[i]->workOrdersCompleted;
		}
	}

	ZTimeUTC now = zTimeUTC();

	// ASSIGN workorders to available workers
	for( int ci=0; ci<connections.count; ci++ ) {
		Connection *c = connections[ci];
		assert( c );
			// The list should never be sprase

		if( jobs.count > 0 && c->availForWork ) {

			// PICK a random account according to weighting statistics
			int r = zrandI( 0, weightingSum );

			int sum = 0;
			for( i=0; i<accounts.count; i++ ) {
				if( accounts[i]->activeWorkOrderCount > 0 ) {
					sum += accounts[i]->workOrdersCompleted;
					if( sum > r ) {
						break;
					}
				}
			}

			Account *lotteryWinner = accounts[i];

			// LOOP through the jobs starting at a random place to distriubute scheduling looking
			// for a work order that belongs to a job owned by the lotteryWinner
			int found = 0;
			int jobRand = zrandI(0,jobs.count);
			for( int ji=0; !found && ji<jobs.count; ji++ ) {
				Job *j = jobs[ (jobRand+ji) % jobs.count ];

				if( strcmp(j->creator,lotteryWinner->loginName) ) {
					// SKIP jobs which are not owned by the winner of the scheduling lottery
					continue;
				}

				if( j->workOrdersRequested - j->workOrdersCompleted <= 0 ) {
					// SKIP jobs which have all of their work orders completed
					continue;
				}

				// FIND a work order belonging to this job
				for( int wi=0; wi<workOrders.count; wi++ ) {
					WorkOrder *w = workOrders[wi];

					if( w->jobId == j->jobId && strstr(workOrders[wi]->protocol, c->protocols) ) {
						// This workorder is for the job and the worker supports the protocol

						// SEND the work order if it has never been sent or if it has been abandoned
						if(
							w->whenSent == 0.0
							|| (
								now - w->whenSent > (ZTimeUTC)w->assumeAbandonedAfterSeconds
								&& w->whenCompleted == 0
							)
						) {
							j->workOrdersSent++;
							c->availForWork = 0;
							
							static int workSentOrderCounter = 1;
							w->sentUniqId = ++workSentOrderCounter;
							strcpy( w->sentWhoToCredit, c->loginName );
							w->whenSent = zTimeUTC();

							ZMsg *newMsg = new ZMsg;
							newMsg->copyFrom( w->instructions );
							newMsg->putS( "type", "WorkOrderBegin" );
							newMsg->putI( "toRemote", c->zocketId );
							newMsg->putI( "workOrderUniqId", w->sentUniqId );

							zMsgQueue( newMsg );

							saveAll();

							found = 1;
							break;
						}
					}									  
				}
			}
		}

		// GARBAGE collect any connections that are either marked for delete
		// or are connected but who are not marked as avilable for work within 30 seconds
		if( (c->markedForDelete && now > c->markedForDelete) /*|| (now > c->connectTime+10 && !c->loginName[0])*/ ) {
			trace( "Dropped %d\n", c->zocketId );
			int zid = c->zocketId;
			ZMsgZocket::dropId( zid );
			connectionDelete( zid );
			ci--;
				// The list just got one shorter
		}
	}
}