LRESULT CALLBACK SharedSocketDataReceiverWndProc(HWND wnd,UINT message,WPARAM wp,LPARAM lp)
{
	switch (message)
	{
		case WM_SHARED_SOCKET_EVENT:
			{
				switch (WSAGETSELECTEVENT(lp))
				{
					case FD_READ:
						{
							SOCKET data_socket=(SOCKET)wp;
							char type;
							DWORD length;
						
							PBYTE data=RecvTLVData(data_socket,&type,&length);
							if(data)
							{
								gSharedSocketDataReceiver(data_socket,type,length,data);
							}else{
								//msg("Got Error on Socket\n");
							}
						
							//WSAAsyncSelect: READ|CLOSE
							if (WSAAsyncSelect(data_socket ,
								wnd,
								WM_SHARED_SOCKET_EVENT,
								FD_READ|FD_CLOSE
							) == SOCKET_ERROR)
							{
								/*
								print_function("failed to async select client %d, %X data_socket=%d, message_window=%X\n", 
									data_socket,
									WSAGetLastError(),
									data_socket,
									message_window);
								*/
							}							
						}
						break;
					case FD_CLOSE:
						closesocket((SOCKET)wp);
						break;
				}
			}
			break;
		default:
			return DefWindowProc(wnd, message, wp, lp);
	}
	return 0;
}