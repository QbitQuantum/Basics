static void* run(void* arg)
{
	IntruderThread* obj = (IntruderThread*)arg;
	char recv_buf[5];
	while(true)
	{
		try
		{
			//connect to the socket to get intruder data; this obj is client
			ClientSocket client = ClientSocket(src_str, src_port);
			//if yes, then notify the ServerObj
			while(true)
			{
				int recv_size = client.recv(&(recv_buf[0]), 5);
				if(recv_size<=0)
				{
					throw SocketException ( "Could not read from socket." );
				}
				//				printf("Receiving %d bytes from server:", recv_size);
				//				for(int i=0;i<5;i++)
				//				{
				//					printf("%2.2x",(char)recv_buf[i]);
				//				}
				if(recv_buf[4]==0x01)
				{
//					cout << "\t ====> Intruder!" << endl;
					(obj->intruderDetected)(obj->handler, SRC_INTRUDER);
				}
				//				printf("\n");
			}
		}
		catch(SocketException &ex)
		{
			cout << "Error " << ex.description() << endl;
			sleep(1);
		}
	}
	return NULL;
}