void IEEE1588Port::processEvent(Event e)
{
	bool changed_external_master;
	OSTimer *timer = timer_factory->createTimer();
	
	switch (e) {
	case POWERUP:
	case INITIALIZE:
		XPTPD_INFO("Received POWERUP/INITIALIZE event");
		clock->getTimerQLock();

		{
			unsigned long long interval3;
			unsigned long long interval4;
			Event e3 = NULL_EVENT;
			Event e4 = NULL_EVENT;
			
			if( port_state != PTP_MASTER ) {
				_accelerated_sync_count = -1;
			}
			
			if( port_state != PTP_SLAVE && port_state != PTP_MASTER ) {
				fprintf( stderr, "Starting PDelay\n" );
				startPDelay();
			}

			if( clock->getPriority1() == 255 || port_state == PTP_SLAVE ) {
				becomeSlave( false );
			} else if( port_state == PTP_MASTER ) {
				becomeMaster( true );
			} else {
				//e3 = SYNC_RECEIPT_TIMEOUT_EXPIRES;
				e4 = ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES;
				interval3 = (unsigned long long)
					(SYNC_RECEIPT_TIMEOUT_MULTIPLIER*
					 pow((double)2,getSyncInterval())*1000000000.0);
				interval4 = (unsigned long long)
					(ANNOUNCE_RECEIPT_TIMEOUT_MULTIPLIER*
					 pow((double)2,getAnnounceInterval())*1000000000.0);
			}
      
			port_ready_condition->wait_prelock();
			listening_thread = thread_factory->createThread();
			if (!listening_thread->
				start (openPortWrapper, (void *)this))
			{
				XPTPD_ERROR("Error creating port thread");
				return;
			}
			port_ready_condition->wait();
			
			if (e3 != NULL_EVENT)
				clock->addEventTimer(this, e3, interval3);
			if (e4 != NULL_EVENT)
				clock->addEventTimer(this, e4, interval4);
		}
		
		clock->putTimerQLock();

		break;
	case STATE_CHANGE_EVENT:
		if ( clock->getPriority1() != 255 ) {
			int number_ports, j;
			PTPMessageAnnounce *EBest = NULL;
			char EBestClockIdentity[PTP_CLOCK_IDENTITY_LENGTH];

			IEEE1588Port **ports;
			clock->getPortList(number_ports, ports);

			

			/* Find EBest for all ports */
			j = 0;
			for (int i = 0; i < number_ports; ++i) {
				while (ports[j] == NULL)
					++j;
				if (ports[j]->port_state == PTP_DISABLED
				    || ports[j]->port_state == PTP_FAULTY) {
					continue;
				}
				if (EBest == NULL) {
					EBest = ports[j]->calculateERBest();
				} else {
					if (ports[j]->calculateERBest()->isBetterThan(EBest)) {
						EBest = ports[j]->calculateERBest();
					}
				}
			}

			/* Check if we've changed */
			{
			  
			  uint8_t LastEBestClockIdentity[PTP_CLOCK_IDENTITY_LENGTH];
			  clock->getLastEBestIdentity().
				  getIdentityString( LastEBestClockIdentity );
			  EBest->getGrandmasterIdentity( EBestClockIdentity );
			  if( memcmp
				  ( EBestClockIdentity, LastEBestClockIdentity,
					PTP_CLOCK_IDENTITY_LENGTH ) != 0 )
			  {
				  ClockIdentity newGM;
				  changed_external_master = true;
				  newGM.set((uint8_t *) EBestClockIdentity );
				  clock->setLastEBestIdentity( newGM );
			  } else {
				  changed_external_master = false;
			  }
			}
			
			if( clock->isBetterThan( EBest )) {
				// We're Grandmaster, set grandmaster info to me
				ClockIdentity clock_identity;
				unsigned char priority1;
				unsigned char priority2;
				ClockQuality clock_quality;
			  
				clock_identity = getClock()->getClockIdentity();
				getClock()->setGrandmasterClockIdentity( clock_identity );
				priority1 = getClock()->getPriority1();
				getClock()->setGrandmasterPriority1( priority1 );
				priority2 = getClock()->getPriority2();
				getClock()->setGrandmasterPriority2( priority2 );
				clock_quality = getClock()->getClockQuality();
				getClock()->setGrandmasterClockQuality( clock_quality );
			}

			j = 0;
			for (int i = 0; i < number_ports; ++i) {
				while (ports[j] == NULL)
					++j;
				if (ports[j]->port_state == PTP_DISABLED
				    || ports[j]->port_state == PTP_FAULTY) {
					continue;
				}
				if (clock->isBetterThan(EBest)) {
					// We are the GrandMaster, all ports are master
					EBest = NULL;	// EBest == NULL : we were grandmaster
					ports[j]->recommendState(PTP_MASTER,
								 changed_external_master);
				} else {
					if( EBest == ports[j]->calculateERBest() ) {
						// The "best" Announce was recieved on this port
						ClockIdentity clock_identity;
						unsigned char priority1;
						unsigned char priority2;
						ClockQuality *clock_quality;
						
						ports[j]->recommendState
							( PTP_SLAVE, changed_external_master );
						
						clock_identity = EBest->getGrandmasterClockIdentity();
						getClock()->setGrandmasterClockIdentity(clock_identity);
						priority1 = EBest->getGrandmasterPriority1();
						getClock()->setGrandmasterPriority1( priority1 );
						priority2 = EBest->getGrandmasterPriority2();
						getClock()->setGrandmasterPriority2( priority2 );
						clock_quality = EBest->getGrandmasterClockQuality();
						getClock()->setGrandmasterClockQuality(*clock_quality);
					} else {
						/* Otherwise we are the master because we have 
						   sync'd to a better clock */
						ports[j]->recommendState
							(PTP_MASTER, changed_external_master);
					}
				}
			}
		}
		break;
	case ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES:
	case SYNC_RECEIPT_TIMEOUT_EXPIRES:
		{
			if( clock->getPriority1() == 255 ) {
				// Restart timer
				if( e == ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES ) {
					clock->addEventTimer
						(this, ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES,
						 (ANNOUNCE_RECEIPT_TIMEOUT_MULTIPLIER*
						  (unsigned long long)
						  (pow((double)2,getAnnounceInterval())*
						   1000000000.0)));
				} else {
					clock->addEventTimer
						(this, SYNC_RECEIPT_TIMEOUT_EXPIRES,
						 (SYNC_RECEIPT_TIMEOUT_MULTIPLIER*
						  (unsigned long long)
						  (pow((double)2,getSyncInterval())*
						   1000000000.0)));
				}
				return;
			}
			if (port_state == PTP_INITIALIZING
			    || port_state == PTP_UNCALIBRATED
			    || port_state == PTP_SLAVE
			    || port_state == PTP_PRE_MASTER) {
					Timestamp tsTmp(0,0,0);
					if(NULL!=p_dbg_HoldLastFollowup) {
						tsTmp = p_dbg_HoldLastFollowup->getPreciseOriginTimestamp();
					}
				fprintf
					(stderr,
					 "*** %s Timeout Expired - Becoming Master LastFollowUpPOT=%16llu\n", 
					 e == ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES ? "Announce" :
					 "Sync",  tsTmp );
				{
				  // We're Grandmaster, set grandmaster info to me
				  ClockIdentity clock_identity;
				  unsigned char priority1;
				  unsigned char priority2;
				  ClockQuality clock_quality;
				  
				  clock_identity = getClock()->getClockIdentity();
				  getClock()->setGrandmasterClockIdentity( clock_identity );
				  priority1 = getClock()->getPriority1();
				  getClock()->setGrandmasterPriority1( priority1 );
				  priority2 = getClock()->getPriority2();
				  getClock()->setGrandmasterPriority2( priority2 );
				  clock_quality = getClock()->getClockQuality();
				  getClock()->setGrandmasterClockQuality( clock_quality );
				}
				port_state = PTP_MASTER;
				Timestamp system_time;
				Timestamp device_time;

				uint32_t local_clock, nominal_clock_rate;

				getDeviceTime(system_time, device_time,
					      local_clock, nominal_clock_rate);

				(void) clock->calcLocalSystemClockRateDifference
				  ( device_time, system_time );

				delete qualified_announce;
				qualified_announce = NULL;

				// Add timers for Announce and Sync, this is as close to immediately as we get
				clock->addEventTimer
					( this, SYNC_INTERVAL_TIMEOUT_EXPIRES, 16000000 );
				startAnnounce();
					// 
			}
		}

		break;
	case PDELAY_INTERVAL_TIMEOUT_EXPIRES:
			XPTPD_INFO("PDELAY_INTERVAL_TIMEOUT_EXPIRES occured");
			{
				int ts_good;
				Timestamp req_timestamp;
				int iter = TX_TIMEOUT_ITER;
				long req = TX_TIMEOUT_BASE;
				unsigned req_timestamp_counter_value;
				long long wait_time = 0;

				PTPMessagePathDelayReq *pdelay_req =
				    new PTPMessagePathDelayReq(this);
				PortIdentity dest_id;
				getPortIdentity(dest_id);
				pdelay_req->setPortIdentity(&dest_id);
				
				{
					Timestamp pending =
					    PDELAY_PENDING_TIMESTAMP;
					pdelay_req->setTimestamp(pending);
				}

				if (last_pdelay_req != NULL) {
					delete last_pdelay_req;
				}
				setLastPDelayReq(pdelay_req);

				getTxLock();
				pdelay_req->sendPort(this, NULL);
				XPTPD_INFO("Sent PDelay Request");

				ts_good =
				    getTxTimestamp
					(pdelay_req, req_timestamp, req_timestamp_counter_value,
					 false);
				while (ts_good != 0 && iter-- != 0) {
					timer->sleep(req);
					wait_time += req;
					if (ts_good != -72 && iter < 1)
						fprintf
							(stderr,
							 "Error (TX) timestamping PDelay request "
							 "(Retrying-%d), error=%d\n", iter, ts_good);
					ts_good =
					    getTxTimestamp
						(pdelay_req, req_timestamp,
						 req_timestamp_counter_value, iter == 0);
					req *= 2;
				}
				putTxLock();

				if (ts_good == 0) {
					pdelay_req->setTimestamp(req_timestamp);
				} else {
				  Timestamp failed = INVALID_TIMESTAMP;
				  pdelay_req->setTimestamp(failed);
				  fprintf( stderr, "Invalid TX\n" );
				}

				if (ts_good != 0) {
					char msg
					    [HWTIMESTAMPER_EXTENDED_MESSAGE_SIZE];
					getExtendedError(msg);
					XPTPD_ERROR(
						"Error (TX) timestamping PDelay request, error=%d\t%s",
						ts_good, msg);
				}
#ifdef DEBUG
				if (ts_good == 0) {
					XPTPD_INFO
					    ("Successful PDelay Req timestamp, %u,%u",
					     req_timestamp.seconds_ls,
					     req_timestamp.nanoseconds);
				} else {
					XPTPD_INFO
					    ("*** Unsuccessful PDelay Req timestamp");
				}
#endif

				{
					long long timeout;
					long long interval;

					timeout = PDELAY_RESP_RECEIPT_TIMEOUT_MULTIPLIER *
						((long long)
						 (pow((double)2,getPDelayInterval())*1000000000.0)) -
						wait_time*1000;
					timeout = timeout > EVENT_TIMER_GRANULARITY ?
						timeout : EVENT_TIMER_GRANULARITY;
					clock->addEventTimer
						(this, PDELAY_RESP_RECEIPT_TIMEOUT_EXPIRES, timeout );
					
					interval = 
						((long long)
						 (pow((double)2,getPDelayInterval())*1000000000.0)) -
						wait_time*1000;
					interval = interval > EVENT_TIMER_GRANULARITY ?
						interval : EVENT_TIMER_GRANULARITY;
					clock->addEventTimer
						(this, PDELAY_INTERVAL_TIMEOUT_EXPIRES, interval );
				}
			}
			break;
	case SYNC_INTERVAL_TIMEOUT_EXPIRES:

			XPTPD_INFO("SYNC_INTERVAL_TIMEOUT_EXPIRES occured");
fprintf(stderr, "STO\n");
			{
#ifdef OLD_GPTP
				/* Set offset from master to zero, update device vs
				   system time offset */
				Timestamp system_time;
				Timestamp device_time;
				FrequencyRatio local_system_freq_offset;
				int64_t local_system_offset;
				long long wait_time = 0;
				
				uint32_t local_clock, nominal_clock_rate;

				// Send a sync message and then a followup to broadcast
				if (asCapable) {
					PTPMessageSync *sync = new PTPMessageSync(this);
					PortIdentity dest_id;
					getPortIdentity(dest_id);
					sync->setPortIdentity(&dest_id);
					getTxLock();
					sync->sendPort(this, NULL);
					XPTPD_INFO("Sent SYNC message");
					
					int ts_good;
					Timestamp sync_timestamp;
					unsigned sync_timestamp_counter_value;
					int iter = TX_TIMEOUT_ITER;
					long req = TX_TIMEOUT_BASE;
					ts_good =
						getTxTimestamp(sync, sync_timestamp,
									   sync_timestamp_counter_value,
									   false);
					while (ts_good != 0 && iter-- != 0) {
						timer->sleep(req);
						wait_time += req;

						if (ts_good != -72 && iter < 1)
							XPTPD_ERROR(
								"Error (TX) timestamping Sync (Retrying), "
								"error=%d", ts_good);
						ts_good =
							getTxTimestamp
							(sync, sync_timestamp, 
							 sync_timestamp_counter_value, iter == 0);
						req *= 2;
					}
					putTxLock();
					
					if (ts_good != 0) {
						char msg
							[HWTIMESTAMPER_EXTENDED_MESSAGE_SIZE];
						getExtendedError(msg);
						fprintf
							(stderr,
							 "Error (TX) timestamping Sync, error="
							 "%d\n%s",
							 ts_good, msg );
 					}

					if (ts_good == 0) {
						XPTPD_INFO("Successful Sync timestamp");
						XPTPD_INFO("Seconds: %u",
								   sync_timestamp.seconds_ls);
						XPTPD_INFO("Nanoseconds: %u",
								   sync_timestamp.nanoseconds);
					} else {
						XPTPD_INFO
							("*** Unsuccessful Sync timestamp");
					}
					
					PTPMessageFollowUp *follow_up;
					if (ts_good == 0) {
						follow_up =
							new PTPMessageFollowUp(this);
						PortIdentity dest_id;
						getPortIdentity(dest_id);
						follow_up->setPortIdentity(&dest_id);
						follow_up->setSequenceId(sync->getSequenceId());
						follow_up->setPreciseOriginTimestamp(sync_timestamp);
						follow_up->sendPort(this, NULL);
						delete follow_up;
					} else {
					}
					delete sync;
				}
				/* Do getDeviceTime() after transmitting sync frame
				   causing an update to local/system timestamp */
				getDeviceTime
					(system_time, device_time, local_clock, nominal_clock_rate);
				
				XPTPD_INFO
					("port::processEvent(): System time: %u,%u Device Time: %u,%u",
					 system_time.seconds_ls, system_time.nanoseconds,
					 device_time.seconds_ls, device_time.nanoseconds);
				
				local_system_offset =
			    TIMESTAMP_TO_NS(system_time) -
			    TIMESTAMP_TO_NS(device_time);
			  local_system_freq_offset =
			    clock->calcLocalSystemClockRateDifference
			    ( device_time, system_time );
			  clock->setMasterOffset
				  (0, device_time, 1.0, local_system_offset,
				   system_time, local_system_freq_offset, sync_count,
				   pdelay_count, port_state , 0/*DEBUG*/, system_time, system_time, 0, 0, 0 );

			  /* If accelerated_sync is non-zero then start 16 ms sync
				 timer, subtract 1, for last one start PDelay also */
			  if( _accelerated_sync_count > 0 ) {
				  clock->addEventTimer
					  ( this, SYNC_INTERVAL_TIMEOUT_EXPIRES, 8000000 );
				  --_accelerated_sync_count;
			  } else {
				  syncDone();
				  if( _accelerated_sync_count == 0 ) {
					  --_accelerated_sync_count;
				  }
				  wait_time *= 1000; // to ns
				  wait_time =
					  ((long long)
					   (pow((double)2,getSyncInterval())*1000000000.0)) -
					  wait_time;
				  wait_time = wait_time > EVENT_TIMER_GRANULARITY ? wait_time :
					  EVENT_TIMER_GRANULARITY;
				  clock->addEventTimer
					  ( this, SYNC_INTERVAL_TIMEOUT_EXPIRES, wait_time );
			  }
#else
				/* Set offset from master to zero, update device vs
				   system time offset */
				Timestamp system_time;
				Timestamp device_time;
				Timestamp sync_timestamp;
				long long wait_time = 0;
				
				uint32_t local_clock, nominal_clock_rate;
				struct masterToLocal master_to_local;
				struct localToSystem local_to_system;

				// Send a sync message and then a followup to broadcast
				if (asCapable) {
					PTPMessageSync *sync = new PTPMessageSync(this);
					PortIdentity dest_id;
					getPortIdentity(dest_id);
					sync->setPortIdentity(&dest_id);
					getTxLock();
					sync->sendPort(this, NULL);
					XPTPD_INFO("Sent SYNC message");
					
					int ts_good;
					unsigned sync_timestamp_counter_value;
					int iter = TX_TIMEOUT_ITER;
					long req = TX_TIMEOUT_BASE;
					ts_good =
						getTxTimestamp(sync, sync_timestamp,
									   sync_timestamp_counter_value,
									   false);
					while (ts_good != 0 && iter-- != 0) {
						timer->sleep(req);
						wait_time += req;

						if (ts_good != -72 && iter < 1)
							XPTPD_ERROR(
								"Error (TX) timestamping Sync (Retrying), "
								"error=%d", ts_good);
						ts_good =
							getTxTimestamp
							(sync, sync_timestamp, 
							 sync_timestamp_counter_value, iter == 0);
						req *= 2;
					}
					putTxLock();
					
					if (ts_good != 0) {
						char msg
							[HWTIMESTAMPER_EXTENDED_MESSAGE_SIZE];
						getExtendedError(msg);
						fprintf
							(stderr,
							 "Error (TX) timestamping Sync, error="
							 "%d\n%s",
							 ts_good, msg );
 					}

					if (ts_good == 0) {
						XPTPD_INFO("Successful Sync timestamp");
						XPTPD_INFO("Seconds: %u",
								   sync_timestamp.seconds_ls);
						XPTPD_INFO("Nanoseconds: %u",
								   sync_timestamp.nanoseconds);
					} else {
						XPTPD_INFO
							("*** Unsuccessful Sync timestamp");
					}
					
					PTPMessageFollowUp *follow_up;
					if (ts_good == 0) {
						follow_up =
							new PTPMessageFollowUp(this);
						PortIdentity dest_id;
						getPortIdentity(dest_id);
						follow_up->setPortIdentity(&dest_id);
						follow_up->setSequenceId(sync->getSequenceId());
						follow_up->setPreciseOriginTimestamp(sync_timestamp);
						follow_up->sendPort(this, NULL);
						delete follow_up;
					} else {
					}
					delete sync;
				}
				/* Do getDeviceTime() after transmitting sync frame
				   causing an update to local/system timestamp */
				getDeviceTime
					(system_time, device_time, local_clock, nominal_clock_rate);
				
				XPTPD_INFO
					("port::processEvent(): System time: %u,%u Device Time: %u,%u",
					 system_time.seconds_ls, system_time.nanoseconds,
					 device_time.seconds_ls, device_time.nanoseconds);

				master_to_local.preciseOriginTimestamp = sync_timestamp;
				master_to_local.sync_arrival = sync_timestamp;
				master_to_local.freq_ratio =  1.0;
				local_to_system.device_time = device_time;
				local_to_system.system_time = system_time;
				local_to_system.freq_ratio = clock->calcLocalSystemClockRateDifference( device_time, system_time );;

				clock->setMasterOffset(master_to_local, local_to_system, sync_count,
										 pdelay_count, port_state );

				/* If accelerated_sync is non-zero then start 16 ms sync
				   timer, subtract 1, for last one start PDelay also */
				if( _accelerated_sync_count > 0 ) {
					clock->addEventTimer( this, SYNC_INTERVAL_TIMEOUT_EXPIRES, 8000000 );
					--_accelerated_sync_count;
				} else {
					syncDone();
					if( _accelerated_sync_count == 0 ) {
						--_accelerated_sync_count;
					}
					wait_time *= 1000; // to ns
					wait_time =
							((long long)
							(pow((double)2,getSyncInterval())*1000000000.0)) -
							wait_time;
					wait_time = wait_time > EVENT_TIMER_GRANULARITY ? wait_time :
								EVENT_TIMER_GRANULARITY;
					clock->addEventTimer
							( this, SYNC_INTERVAL_TIMEOUT_EXPIRES, wait_time );
				}
#endif
			}
			break;
	case ANNOUNCE_INTERVAL_TIMEOUT_EXPIRES:
		if (asCapable) {
			// Send an announce message
			PTPMessageAnnounce *annc = new PTPMessageAnnounce(this);
			PortIdentity dest_id;
			PortIdentity gmId;
			ClockIdentity clock_id = clock->getClockIdentity();
			gmId.setClockIdentity(clock_id);
			getPortIdentity(dest_id);
			annc->setPortIdentity(&dest_id);
			annc->sendPort(this, NULL);
			delete annc;
		}
		clock->addEventTimer
			(this, ANNOUNCE_INTERVAL_TIMEOUT_EXPIRES,
			 (unsigned)
			 (pow ((double)2, getAnnounceInterval()) * 1000000000.0));
		break;
	case FAULT_DETECTED:
		XPTPD_INFO("Received FAULT_DETECTED event");
		break;
	case PDELAY_DEFERRED_PROCESSING:
		pdelay_rx_lock->lock();
		if (last_pdelay_resp_fwup == NULL) {
			fprintf(stderr, "PDelay Response Followup is NULL!\n");
			abort();
		}
		last_pdelay_resp_fwup->processMessage(this);
		if (last_pdelay_resp_fwup->garbage()) {
			delete last_pdelay_resp_fwup;
			this->setLastPDelayRespFollowUp(NULL);
		}
		pdelay_rx_lock->unlock();
		break;
	case PDELAY_RESP_RECEIPT_TIMEOUT_EXPIRES:
		setAsCapable(false);
		pdelay_count = 0;
		break;
	default:
		XPTPD_INFO
		    ("Unhandled event type in IEEE1588Port::processEvent(), %d",
		     e);
		break;
	}

	delete timer;
	return;
}