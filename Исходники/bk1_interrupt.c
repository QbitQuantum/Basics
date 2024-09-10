/****************************************************************************
*
*						Subroutine main
*
*****************************************************************************/
int main(int argc, char *argv[])
{
	int tlkilled,tlpid, rc,status;  //tlpid=trace logger pid
	struct traceparser_state * tp_state;

	/*
	 * Start the tests.
	 */
	teststart(argv[0]);
	/* Get rid of tracelogger if it is running  */
	tlkilled=kill_tl();
	/***********************************************************************/

	/***********************************************************************/
	/*
	 * Make sure that interrupt events get logged
	 * This tests the information provided in wide mode.
	 */
 	testpntbegin("Get interrupt entry in wide mode");
		
	/* We need to start up the tracelogger in daemon mode, 1 itteration.
	 * we will filter out everything other then interrupt events, and
	 * start logging. 
	 */
	tlpid=start_logger();
	sleep(1);
	/* Set the logger to wide emmiting mode */
	rc=TraceEvent(_NTO_TRACE_SETALLCLASSESWIDE);
	assert(rc!=-1);
	/* Add interrupt entry's */
	rc=TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_INTENTER);
	assert(rc!=-1);
	
	rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
	assert(rc!=-1);
	/* Wait a bit, so some timer interrupts should fire */
	delay(100);
	
	/* flush the trace buffer */
	rc=TraceEvent(_NTO_TRACE_FLUSHBUFFER);	
	assert(rc!=-1);
	rc=waitpid(tlpid, &status, 0);
	assert(tlpid==rc);

	/* Now, setup the traceparser lib to pull out the interrupt events
	 * and make sure our event shows up 
	 */
	tp_state=traceparser_init(NULL);
	assert(tp_state!=NULL);
	traceparser_cs_range(tp_state, NULL, parse_cb, _NTO_TRACE_INTENTER, _NTO_TRACE_INTFIRST, _NTO_TRACE_INTLAST);

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
		testpntfail("Wrong parameters in the event");
	else if (correct_values==1)
		testpntpass("Got the correct values");
	else 
		testpntfail("This should not happen");

	traceparser_destroy(&tp_state);
 	testpntend();
	/***********************************************************************/

	/***********************************************************************/
	/*
	 * Make sure that if we trigger a event, that it gets logged properly
	 * (all the information in the tracelogger is correct)
	 * This tests the information provided in fast mode.
	 */
 	testpntbegin("Get interrupt entry in fast mode");
		
	/* We need to start up the tracelogger in daemon mode, 1 itteration.
	 * we will filter out everything other then interrupts, then start
	 * logging. 
	 */
	tlpid=start_logger();
	sleep(1);
	/* Set the logger to wide emmiting mode */
	rc=TraceEvent(_NTO_TRACE_SETALLCLASSESFAST);
	assert(rc!=-1);
	/* Add interrupt entry's */
	rc=TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_INTENTER);
	assert(rc!=-1);

	rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
	assert(rc!=-1);
	/* Wait a bit, so some timer interrupts should fire */
	delay(1000);

	rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
	assert(rc!=-1);
	
	/* flush the trace buffer */
	rc=TraceEvent(_NTO_TRACE_FLUSHBUFFER);	
	assert(rc!=-1);
	rc=waitpid(tlpid, &status, 0);
	assert(tlpid==rc);

	/* Now, setup the traceparser lib to pull out the interrupt events
	 * and make sure our event shows up 
	 */
	tp_state=traceparser_init(NULL);
	assert(tp_state!=NULL);
	traceparser_cs_range(tp_state, NULL, parse_cb, _NTO_TRACE_INTENTER, _NTO_TRACE_INTFIRST, _NTO_TRACE_INTLAST);

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
		testpntfail("Wrong parameters in the event");
	else if (correct_values==1)
		testpntpass("Got the correct values");
	else 
		testpntfail("This should not happen");

	traceparser_destroy(&tp_state);
 	testpntend();
	/***********************************************************************/

	/***********************************************************************/
	/*
	 * Make sure that if we trigger a event, that it gets logged properly
	 * (all the information in the tracelogger is correct)
	 * This tests the information provided in wide mode.
	 */
 	testpntbegin("Get interrupt exit in wide mode");
		
	/* We need to start up the tracelogger in daemon mode, 1 itteration.
	 * we will filter out everything other then interrupts, then start
	 * logging. 
	 */
	tlpid=start_logger();
	sleep(1);
	/* Set the logger to wide emmiting mode */
	rc=TraceEvent(_NTO_TRACE_SETALLCLASSESWIDE);
	assert(rc!=-1);
	/* Add interrupt entry's */
	rc=TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_INTEXIT);
	assert(rc!=-1);

	rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
	assert(rc!=-1);
	/* Wait a bit, so some timer interrupts should fire */
	delay(1000);
	
	/* flush the trace buffer */
	rc=TraceEvent(_NTO_TRACE_FLUSHBUFFER);	
	assert(rc!=-1);
	rc=waitpid(tlpid, &status, 0);
	assert(tlpid==rc);

	/* Now, setup the traceparser lib to pull out the interrupt events
	 * and make sure our event shows up 
	 */
	tp_state=traceparser_init(NULL);
	assert(tp_state!=NULL);
	traceparser_cs_range(tp_state, NULL, parse_cb, _NTO_TRACE_INTEXIT, _NTO_TRACE_INTFIRST, _NTO_TRACE_INTLAST);

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
		testpntfail("Wrong parameters in the event");
	else if (correct_values==1)
		testpntpass("Got the correct values");
	else 
		testpntfail("This should not happen");

	traceparser_destroy(&tp_state);
 	testpntend();

	/***********************************************************************/

	/***********************************************************************/
	/*
	 * Make sure that if we trigger a event, that it gets logged properly
	 * (all the information in the tracelogger is correct)
	 * This tests the information provided in fast mode.
	 */
 	testpntbegin("Get interrupt exit in fast mode");
		
	/* We need to start up the tracelogger in daemon mode, 1 itteration.
	 * we will filter out everything other then interrupts, then 
	 * start logging. 
	 */
	tlpid=start_logger();
	sleep(1);
	/* Set the logger to wide emmiting mode */
	rc=TraceEvent(_NTO_TRACE_SETALLCLASSESFAST);
	assert(rc!=-1);
	/* Add interrupt entry's */
	rc=TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_INTEXIT);
	assert(rc!=-1);

	rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
	assert(rc!=-1);
	/* Wait a bit, so some timer interrupts should fire */
	delay(1000);
	
	/* flush the trace buffer */
	rc=TraceEvent(_NTO_TRACE_FLUSHBUFFER);	
	assert(rc!=-1);
	rc=waitpid(tlpid, &status, 0);
	assert(tlpid==rc);

	/* Now, setup the traceparser lib to pull out the interrupt events
	 * and make sure our event shows up 
	 */
	tp_state=traceparser_init(NULL);
	assert(tp_state!=NULL);
	traceparser_cs_range(tp_state, NULL, parse_cb, _NTO_TRACE_INTEXIT, _NTO_TRACE_INTFIRST, _NTO_TRACE_INTLAST);

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
		testpntfail("Wrong parameters in the event");
	else if (correct_values==1)
		testpntpass("Got the correct values");
	else 
		testpntfail("This should not happen");

	traceparser_destroy(&tp_state);
 	testpntend();

	/***********************************************************************/
	/* If the tracelogger was running when we started, we should restart it again */
	if (tlkilled==1) 
		system("reopen /dev/null ; tracelogger -n 0 -f /dev/null &");

	teststop(argv[0]);
	return 0;
}