/****************************************************************************
*
*						Subroutine start_logger
*
*	Purpose: 	This function will start up the tracelogger, and
*				clear any filters that may be in place.
*
*	Returns: 	Pid of the tracelogger
*
*****************************************************************************/
int start_logger(void) 
{
	int tlpid,rc;
	char buf[100];
	snprintf(buf, sizeof(buf), "-n%d", NUM_ITER);

	tlpid=spawnlp(P_NOWAIT, "tracelogger", "tracelogger",buf, "-d", NULL);
	if (tlpid==-1) {
		snprintf(buf,sizeof(buf), "Unable to start tracelogger (%s)", strerror(errno));
		testerror(buf);
		teststop("Bad");
		exit(0);
	}
	rc=TraceEvent(_NTO_TRACE_DELALLCLASSES);
	assert(rc!=-1);
	rc=TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_KERCALL);
	assert(rc!=-1);
	rc=TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_KERCALL);
	assert(rc!=-1);
	rc=TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_THREAD);
	assert(rc!=-1);
	rc=TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_THREAD);
	assert(rc!=-1);
	rc=TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_VTHREAD);
	assert(rc!=-1);
	rc=TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_VTHREAD);
	assert(rc!=-1);
	return(tlpid);
}