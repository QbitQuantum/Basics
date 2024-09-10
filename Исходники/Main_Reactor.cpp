CMain_Reactor::~CMain_Reactor()
{  
	pthread_cancel(accept_id_);
	delete Acceptor_;
	for(int i = 0; i < 1; i++)
	{  
		CEventLoop *loop = LoopList_[i];
		loop->Exit();
		delete loop;
		loop = NULL;
	}
	printf("total msg = %d\n", g_count);
	printf("Main_Reactor Exit\n");
	free(LoopList_);
	ReleasePendingMsg();
	pthread_cond_destroy(&Msg_Cont_);
	pthread_mutex_destroy(&Msg_mutex_);
}