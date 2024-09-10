/****************************************************************************
*
*						Subroutine state_thread
*
*	Purpose: 	This is a thread that is used to trigger the various thread
*				states
*
*	Parameters:	None
*
*	Returns:	Nothing
*			
*
*****************************************************************************/
void * state_thread(void * arg)
{
	int rc,x,coid;
	sigset_t myset;
	uint64_t timeout;
	struct sigevent myevent;
	pthread_t mythread;
	char buf[100];
	while(1) {
		/* Syncronize with the main thread. */
		pthread_barrier_wait(&global_barrier);
		switch (cur_state) {
			case STATE_DEAD: 
				/* Start the logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				/* Trigger the dead state by calling pthread_exit */
				pthread_exit(NULL);
				/* Should never get here */
				abort();
			case STATE_READY: 
				exit_now=0;
				for (x=0;x<_syspage_ptr->num_cpu;x++)
					pthread_create(NULL, NULL, ready_thread, NULL);
				/*  Let the new threads get started */
				sleep(1);
			case STATE_RUNNING: 
				/* Start the logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				/* Trigger the running state by just doing some work. 
				 * this should also trigger a ready state before
				 * we are running
				 */
				x=0;
				while(x<10)
					x++;
				exit_now=1;
				while(x<1000)
					x++;
				exit_now=1;
				/* and unblock the parent */
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_STOPPED: 

				/* Start the logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(100);
				kill (child_pid, SIGSTOP);
				delay(10);
				kill (child_pid, SIGCONT);
				delay(100);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_SEND: 
			case STATE_REPLY: 
				coid=ConnectAttach(0, getpid(), chid, _NTO_SIDE_CHANNEL, 0);
				/* Start the logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				/* Trigger the SEND/REPLY blocked states */
				MsgSend(coid, buf, 10, buf,10);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_RECEIVE: 
				/* Start the logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				/* Trigger a receive state  */
				rc=MsgReceive(chid, buf, sizeof(buf), NULL);
				MsgReply(rc, EOK, "ok", 3);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_WAITTHREAD: 
				/* Start the logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				/* Trigger a waitthread state  */
				pthread_create(NULL, NULL, nothing_thread, NULL);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_SIGSUSPEND: 
				memset(&myevent, 0, sizeof(myevent));
				myevent.sigev_notify = SIGEV_UNBLOCK;
				timeout = 1*1000000000L;
	
				sigemptyset(&myset);
				sigaddset(&myset, SIGHUP);
				sigaddset(&myset, SIGBUS);
				sigaddset(&myset, SIGSEGV);
				sigaddset(&myset, SIGXCPU);
				sigaddset(&myset, SIGRTMIN);
				sigaddset(&myset, SIGRTMAX);
		
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				TimerTimeout( CLOCK_REALTIME, _NTO_TIMEOUT_SIGSUSPEND,&myevent, &timeout, NULL );
				SignalSuspend(&myset);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_SIGWAITINFO: 
				memset(&myevent, 0, sizeof(myevent));
				myevent.sigev_notify = SIGEV_UNBLOCK;
				timeout = 1*1000000000L;
	
				sigemptyset(&myset);
				sigaddset(&myset, SIGHUP);
				sigaddset(&myset, SIGBUS);
				sigaddset(&myset, SIGSEGV);
				sigaddset(&myset, SIGXCPU);
				sigaddset(&myset, SIGRTMIN);
				sigaddset(&myset, SIGRTMAX);
		
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				TimerTimeout( CLOCK_REALTIME, _NTO_TIMEOUT_SIGWAITINFO,&myevent, &timeout, NULL );
				SignalWaitinfo(&myset,NULL);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_NANOSLEEP:
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				sleep(1);
				sleep(1);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_MUTEX:
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				sleep(1);
				pthread_mutex_lock(&mymutex);
				pthread_mutex_unlock(&mymutex);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_CONDVAR:
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				sleep(1);
				pthread_mutex_lock(&mymutex);
				pthread_cond_wait(&mycondvar, &mymutex);
				pthread_mutex_unlock(&mymutex);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_JOIN:
				pthread_create(&mythread, NULL, nothing_thread, NULL);
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				delay(10);
				pthread_join(mythread, NULL);
				pthread_barrier_wait(&global_barrier);
				break;
			case STATE_SEM:
				/* Start logging */
				rc=TraceEvent(_NTO_TRACE_STARTNOSTATE);
				assert(rc!=-1);
				sleep(1);
				sem_wait(&mysem);
				pthread_barrier_wait(&global_barrier);
				break;
			
		}
	}
	
}