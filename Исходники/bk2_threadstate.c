/****************************************************************************
*
*						Subroutine main
*
*****************************************************************************/
int main(int argc, char *argv[])
{
	int tlkilled,tlpid, rc,status;  /*tlpid=trace logger pid */
	struct traceparser_state * tp_state;
	char message[200];
	pthread_t cur_thread;

	/*
	 * Start the tests.
	 */
	teststart(argv[0]);
 
	/* Get rid of tracelogger if it is running  */
	tlkilled=kill_tl();
	/* Setup a channel for the MsgSend Events */
	chid=ChannelCreate(0);
	assert(chid!=-1);

	mypid=getpid();
	
	/* Setup the barrier used to syncronize */
	pthread_barrier_init(&global_barrier, NULL, 2);

	/* Setup the mutex for the mutex/condvar state test */
	rc=pthread_mutex_init(&mymutex,NULL);	
	assert(rc==EOK);

	/* Setup the condvar for the condvar state test */
	rc=pthread_cond_init(&mycondvar,NULL);	
	assert(rc==EOK);

	/* setup the sem tfor the sem state test */
	rc=sem_init(&mysem, 0,0);
	assert(rc==0);

	/* Get io-privity */
	rc=ThreadCtl( _NTO_TCTL_IO, 0 );
	assert(rc!=-1);

	/* Setup the needed child */
	child_pid=fork();
	assert(child_pid!=-1);
	if (child_pid==0) {
		/* This child is used only in the stopped state test.
 		 * it will just sit and loop
		 */
		while (1) {
			delay(10);
		}
		exit(0);
	}
	/* and create a thread to go into various states */
	rc=pthread_create(&cur_thread, NULL, state_thread, NULL);
	assert(rc==EOK);
	for (cur_state=STATE_DEAD;cur_state<=STATE_SEM;cur_state++) {
		/* these states can not be reliably and or safely triggered. */
		if ((cur_state==STATE_STACK) || (cur_state==STATE_WAITPAGE) || cur_state==STATE_INTR)
			continue;
		/***********************************************************************/
	
		/***********************************************************************/
		/*
		 * Make sure that if we trigger a thread state, that it gets logged
		 * properly (all the information in the tracelogger is correct)
		 * This tests the information provided in wide mode.
		 */
		snprintf(message, sizeof(message),"%s in wide mode", state_str[cur_state]);
	 	testpntbegin(message);

		correct_values_eh=0;
		exp_thread=cur_thread;
			
		/* We need to start up the tracelogger in daemon mode, 1 itteration.
		 * we will filter out everything other then thread states, then 
		 * start logging. 
		 * We then will trigger a thread state change, and flush the trace buffer. 
		 * This  should create a VERY minimal trace buffer that will be easily parsed
		 */
		tlpid=start_logger();
		sleep(1);
		/* Set the logger to wide emmiting mode */
		rc=TraceEvent(_NTO_TRACE_SETALLCLASSESWIDE);
		assert(rc!=-1);
		fast_mode=WIDE;
		/* Add the given thread event in the thread class back in */
		rc=TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_THREAD,(1<<cur_state));
		assert(rc!=-1);
		/* Filter out all tids other then the state_thread */
		if  (cur_state==STATE_STOPPED) {
			rc=TraceEvent(_NTO_TRACE_SETCLASSTID, _NTO_TRACE_THREAD, child_pid, 1);
		} else {
			rc=TraceEvent(_NTO_TRACE_SETCLASSTID, _NTO_TRACE_THREAD, getpid(),cur_thread);
		}
		assert(rc!=-1);

		/* Setup the event handler */
		memset(&my_event_data, 0, sizeof(my_event_data));
		memset(data_array, 0, sizeof(data_array));
		my_event_data.data_array=data_array;
		rc=TraceEvent(_NTO_TRACE_ADDEVENTHANDLER, _NTO_TRACE_THREAD,(1<<cur_state), event_handler, &my_event_data);
		assert(rc!=-1);


		/* then trigger an event.  Logging is started inside the state thread
		 * right before it tries to trigger the given state.
		 * the two barrier waits are to 
		 * 1) Tell the state thread that everything is setup so it should trigger the event
		 * 2) Wait for the state thread to tell us it has finished.
		 */
		pthread_barrier_wait(&global_barrier);

		if ((cur_state==STATE_SEND)|| (cur_state==STATE_REPLY)) {
			/* If the thread is going into the send state, we should receive and reply */
			sleep(1);
			status=MsgReceive(chid, message, sizeof(message), NULL);
			MsgReply(status, EOK, "ok", 3);
		} else if (cur_state==STATE_RECEIVE) {
			/* If the thread is going to call reveive, we should send it a message */
			sleep(1);
			status=ConnectAttach(0, getpid(), chid, _NTO_SIDE_CHANNEL, 0);
			MsgSend(status, message, 10, message,10);
		} else if (cur_state==STATE_MUTEX) {
			pthread_mutex_lock(&mymutex);
			sleep(2);
			pthread_mutex_unlock(&mymutex);
		} else if (cur_state==STATE_CONDVAR) {
			sleep(2);
			pthread_cond_signal(&mycondvar);
		} else if (cur_state==STATE_SEM) {
			sleep(2);
			sem_post(&mysem);
		}
		
		
		/* If the state thread is going to try to trigger the dead state, it will have to
		 * exit, so we can not expect it to call barrier_wait to tell us it's done. 
		 */
		if ((1<<cur_state)!=_NTO_TRACE_THDEAD) {
			pthread_barrier_wait(&global_barrier);
		} else {
			/* If the state thread is going to exit, then we should just
 			 * give it time to exit, then restart it.
			 */
			sleep(2); 
			rc=pthread_join(cur_thread, (void **)&status);
			assert(rc==EOK);
			rc=pthread_create(&cur_thread, NULL, state_thread, NULL);
		}
		delay(100);
		
		/* flush the trace buffer and wait for the tracelogger to exit*/
		rc=TraceEvent(_NTO_TRACE_FLUSHBUFFER);	
		assert(rc!=-1);
		rc=waitpid(tlpid, &status, 0);
		assert(tlpid==rc);
	
		/* Now, setup the traceparser lib to pull out the thread state events, 
		 * and make sure our event shows up 
		 */
		tp_state=traceparser_init(NULL);
		assert(tp_state!=NULL);
		traceparser_cs(tp_state, NULL, parse_cb, _NTO_TRACE_THREAD, (1<<cur_state));
	
		/* Since we don't want a bunch of output being displayed in the 
		 * middle of the tests, turn off verbose output.
		 */
		traceparser_debug(tp_state, stdout, _TRACEPARSER_DEBUG_NONE);
		/* Set correct_values to 0, so we can see if the callback actually
		 * got called. 
		 */
		correct_values=0;
		/* And parse the tracebuffer */
		traceparser(tp_state, NULL, "/dev/shmem/tracebuffer");
		
		if (correct_values==0) 
			testpntfail("Our callback never got called, no events?");
		else if (correct_values==-1)
			testpntfail("Got the wrong thread state");
		else if (correct_values==-2) 
			testpntfail("Got the wrong pid");
		else if (correct_values==-3)
			testpntfail("Got the wrong tid");
		else if (correct_values_eh<-1)
			testpntfail("Got bad values in the event handler");
		else if (correct_values_eh==0)
			testpntfail("Event handler not called");
		else if (correct_values_eh==1)
			testpntpass("Good");
		else {
			snprintf(message,sizeof(message),"correct_values_eh : %d",correct_values_eh);
			testnote(message);
		snprintf(message,sizeof(message),"correct_values : %d",correct_values);
		testnote(message);	
			testpntfail("This should not happen");
			}
		traceparser_destroy(&tp_state);
	 	testpntend();
		/***********************************************************************/
	
		/***********************************************************************/
		/*
		 * Make sure that if we trigger a thread state, that it gets logged
		 * properly (all the information in the tracelogger is correct)
		 * This tests the information provided in fast mode.
		 */
		snprintf(message, sizeof(message),"%s in fast mode", state_str[cur_state]);
	 	testpntbegin(message);

		correct_values_eh=0;
		exp_thread=cur_thread;
			
		/* We need to start up the tracelogger in daemon mode, 1 itteration.
		 * we will filter out everything other then thread states, then 
		 * start logging. 
		 * We then will trigger a thread state change, and flush the trace buffer. 
		 * This  should create a VERY minimal trace buffer that will be easily parsed
		 */
		tlpid=start_logger();
		sleep(1);
		/* Set the logger to fast emmiting mode */
		rc=TraceEvent(_NTO_TRACE_SETALLCLASSESFAST);
		assert(rc!=-1);
		fast_mode=FAST;
		/* Add the given thread event in the thread class back in */
		rc=TraceEvent(_NTO_TRACE_ADDEVENT, _NTO_TRACE_THREAD,(1<<cur_state));
		assert(rc!=-1);
		/* Filter out all tids other then the state_thread */
		if  (cur_state==STATE_STOPPED) {
			rc=TraceEvent(_NTO_TRACE_SETCLASSTID, _NTO_TRACE_THREAD, child_pid, 1);
		} else {
			rc=TraceEvent(_NTO_TRACE_SETCLASSTID, _NTO_TRACE_THREAD, getpid(),cur_thread);
		}
		assert(rc!=-1);

		/* Setup the event handler */
		memset(&my_event_data, 0, sizeof(my_event_data));
		memset(data_array, 0, sizeof(data_array));
		my_event_data.data_array=data_array;
		rc=TraceEvent(_NTO_TRACE_ADDEVENTHANDLER, _NTO_TRACE_THREAD,(1<<cur_state), event_handler, &my_event_data);
		assert(rc!=-1);


		/* then trigger an event.  Logging is started inside the state thread
		 * right before it tries to trigger the given state.
		 * the two barrier waits are to 
		 * 1) Tell the state thread that everything is setup so it should trigger the event
		 * 2) Wait for the state thread to tell us it has finished.
		 */
		pthread_barrier_wait(&global_barrier);

		if ((cur_state==STATE_SEND)|| (cur_state==STATE_REPLY)) {
			/* If the thread is going into the send state, we should receive and reply */
			sleep(1);
			status=MsgReceive(chid, message, sizeof(message), NULL);
			MsgReply(status, EOK, "ok", 3);
		} else if (cur_state==STATE_RECEIVE) {
			/* If the thread is going to call reveive, we should send it a message */
			sleep(1);
			status=ConnectAttach(0, getpid(), chid, _NTO_SIDE_CHANNEL, 0);
			MsgSend(status, message, 10, message,10);
		} else if (cur_state==STATE_MUTEX) {
			pthread_mutex_lock(&mymutex);
			sleep(2);
			pthread_mutex_unlock(&mymutex);
		} else if (cur_state==STATE_CONDVAR) {
			sleep(2);
			pthread_cond_signal(&mycondvar);
		} else if (cur_state==STATE_SEM) {
			sleep(2);
			sem_post(&mysem);
		}
		
		
		/* If the state thread is going to try to trigger the dead state, it will have to
		 * exit, so we can not expect it to call barrier_wait to tell us it's done. 
		 */
		if ((1<<cur_state)!=_NTO_TRACE_THDEAD) {
			pthread_barrier_wait(&global_barrier);
		} else {
			/* If the state thread is going to exit, then we should just
 			 * give it time to exit, then restart it.
			 */
			sleep(2); 
			rc=pthread_join(cur_thread, (void **)&status);
			assert(rc==EOK);
			rc=pthread_create(&cur_thread, NULL, state_thread, NULL);
		}
		delay(100);
		
		/* flush the trace buffer and wait for the tracelogger to exit*/
		rc=TraceEvent(_NTO_TRACE_FLUSHBUFFER);	
		assert(rc!=-1);
		rc=waitpid(tlpid, &status, 0);
		assert(tlpid==rc);
	
		/* Now, setup the traceparser lib to pull out the thread state events, 
		 * and make sure our event shows up 
		 */
		tp_state=traceparser_init(NULL);
		assert(tp_state!=NULL);
		traceparser_cs(tp_state, NULL, parse_cb, _NTO_TRACE_THREAD, (1<<cur_state));
	
		/* Since we don't want a bunch of output being displayed in the 
		 * middle of the tests, turn off verbose output.
		 */
		traceparser_debug(tp_state, stdout, _TRACEPARSER_DEBUG_NONE);
		/* Set correct_values to 0, so we can see if the callback actually
		 * got called. 
		 */
		correct_values=0;
		/* And parse the tracebuffer */
		traceparser(tp_state, NULL, "/dev/shmem/tracebuffer");
		
		if (correct_values==0) 
			testpntfail("Our callback never got called, no events?");
		else if (correct_values==-1)
			testpntfail("Got the wrong thread state");
		else if (correct_values==-2) 
			testpntfail("Got the wrong pid");
		else if (correct_values==-3)
			testpntfail("Got the wrong tid");
		else if (correct_values_eh<-1)
			testpntfail("Got bad values in the event handler");
		else if (correct_values_eh==0)
			testpntfail("Event handler not called");
		else if (correct_values_eh==1)
			testpntpass("Good");
		else 
			testpntfail("This should not happen");

		traceparser_destroy(&tp_state);
	 	testpntend();
		/***********************************************************************/

	}
	/* If the tracelogger was running when we started, we should restart it again */
	if (tlkilled==1) 
		system("reopen /dev/null ; tracelogger -n 0 -f /dev/null &");
	/* Kill off the child we had forked earler */
	kill (child_pid, SIGKILL);
	teststop(argv[0]);
	return 0;
}