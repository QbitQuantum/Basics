	int Run()
	{
		// ----------- Thread_TcpCommClient_Recv -----------

		int iParam1 = 0;
		pthread_t pthread_TcpCommClient_Recv;
		if(pthread_create(&pthread_TcpCommClient_Recv, NULL, Thread_TcpCommClient_Recv, (void*)this) != 0)
		{
			printf("Failed:Thread_TcpCommClient_Recv\n");
		}
		else
		{
			printf("Initiate:Thread_TcpCommClient_Recv\n");
			usleep(100000);
		}


		// ----------- Thread_TcpCommClient_Send -----------

		int iParam2 = 0;
		pthread_t pthread_TcpCommClient_Send;
		if(pthread_create(&pthread_TcpCommClient_Send, NULL, Thread_TcpCommClient_Send, (void*)this) != 0)
		{
			printf("Failed:Thread_TcpCommClient_Send\n");
		}
		else
		{
			printf("Initiate:Thread_TcpCommClient_Send\n");
			usleep(100000);
		}


		while( ros::ok() )
		{
			ros::spinOnce();
			usleep(30000);
		}

		if( m_Socket.is_open() )
		{
			m_Socket.close();
		}

		return 0;
	}