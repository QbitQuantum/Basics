//	===============================Select Server===============================
LSelectServer::LSelectServer()
{
#ifndef WIN32
	pthread_mutex_init(&m_mutexForCloseSessionQueue, NULL);
	pthread_mutex_init(&m_mutexForConnectToServer, NULL);
#else
	InitializeCriticalSectionAndSpinCount(&m_mutexForCloseSessionQueue, 4000);
	InitializeCriticalSectionAndSpinCount(&m_mutexForConnectToServer, 4000);
#endif
#ifdef __EPOLL_TEST_STATISTIC__
	atomic_set(&g_nSelectServerRecvPacketAllocCount, 0);
	atomic_set(&g_nSelectServerRecvPacketFreeCount, 0);
	atomic_set(&g_nSelectServerSendPacketAllocCount, 0);
	atomic_set(&g_nSelectServerSendPacketFreeCount, 0);
#endif
}