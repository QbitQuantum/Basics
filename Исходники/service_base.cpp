msg_driven_service::msg_driven_service()
:m_semaphore(NULL),
m_hthread(NULL),
m_b_notify_exit(false),
m_timer(NULL),
m_ap_event_mgr(NULL)
{
	InitializeCriticalSection(&m_cs);
	m_semaphore=CreateSemaphoreA(NULL,0,1000,NULL);
	m_timer=CreateWaitableTimerA(NULL,FALSE,NULL);
	LARGE_INTEGER start_time;
	start_time.QuadPart=-1;
	SetWaitableTimer(m_timer,&start_time,1000,NULL,NULL,TRUE);
	m_ap_event_mgr.reset(new time_event_mgr);
}