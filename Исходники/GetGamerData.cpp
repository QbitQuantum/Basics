string GetGamerData::GetHTML(const string& strServerName, const string& strFileName)
{
	string strGET  = "";
	string strHTML = "";
	
	// ホストの検索
	LPHOSTENT lpHostEntry;
	lpHostEntry = gethostbyname(this->GamerCardServer.c_str());
	if (lpHostEntry == NULL)
	{
		//PRINTERROR("gethostbyname()");
		return strHTML;
	}

	// サーバーアドレス構造体を埋める
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	sa.sin_port = htons(80);	//HTTPポート

	// TCP/IPストリームソケットを作成する
	SOCKET	Socket;
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		//PRINTERROR("socket()"); 
		return strHTML;
	}

	// このソケットで使用するイベントオブジェクトを作成する
	WSAEVENT hEvent;
	hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT)
	{
		//PRINTERROR("WSACreateEvent()");
		closesocket(Socket);
		return strHTML;
	}

	// ソケットを非ブロッキングにし、ネットワークイベントを関連付ける
	int nRet;
	nRet = WSAEventSelect(Socket,hEvent,FD_READ|FD_CONNECT|FD_CLOSE);
	if (nRet == SOCKET_ERROR)
	{
		//PRINTERROR("EventSelect()");
		closesocket(Socket);
		WSACloseEvent(hEvent);
		return strHTML;
	}

	// 接続を要求する
	nRet = connect(Socket,(LPSOCKADDR)&sa,sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		nRet = WSAGetLastError();
		if (nRet == WSAEWOULDBLOCK)
		{
			//fprintf(stderr,"\nConnect would block");
		}
		else
		{
			//PRINTERROR("connect()");
			closesocket(Socket);
			WSACloseEvent(hEvent);
			return strHTML;
		}
	}
	
	// 非同期ネットワークイベントを処理する
	char szBuffer[4096];
	char szBufferZ[8192];
	WSANETWORKEVENTS events;
	while(1)
	{
		// 何か発生するのを待機する
		DWORD dwRet;
		dwRet = WSAWaitForMultipleEvents(1, &hEvent, FALSE,10000,FALSE);
		if (dwRet == WSA_WAIT_TIMEOUT)
		{
			break;
		}

		// どのイベントが発生したかを判別する
		nRet = WSAEnumNetworkEvents(Socket, hEvent, &events);
		if (nRet == SOCKET_ERROR)
		{
			//PRINTERROR("WSAEnumNetworkEvents()");
			break;
		}

		// イベントを処理する

		// 接続イベントかどうか？
		if (events.lNetworkEvents & FD_CONNECT)
		{
			// http要求を送信する
			strGET = "";
			strGET += "GET ";
			strGET += strFileName;
			strGET += " HTTP/1.1\r\nHost: ";
			strGET += strServerName;
			strGET += "\r\nKeep-Alive: timeout=5, max=20\r\nConnection: close\r\n\r\n";
			nRet = send(Socket, strGET.c_str(), strGET.size(), 0);
			if (nRet == SOCKET_ERROR)
			{
				//PRINTERROR("send()");
				break;
			}
		}

		// 読み取りイベントかどうか？
		if (events.lNetworkEvents & FD_READ)
		{
			// データを読み取り、stdoutに書き込む
			nRet = recv(Socket, szBuffer, sizeof(szBuffer), 0);
			if (nRet == SOCKET_ERROR)
			{
				//PRINTERROR("recv()");
				break;
			}
			ZeroMemory(szBufferZ,sizeof(szBufferZ));
			memcpy(szBufferZ,szBuffer,nRet);
			strHTML.append(szBufferZ);
		}

		// 終了イベントかどうか？
		if (events.lNetworkEvents & FD_CLOSE)
		{
			break;
		}

		// 書き込みイベントかどうか？
		if (events.lNetworkEvents & FD_WRITE)
		{
		}

	}
	closesocket(Socket);	
	WSACloseEvent(hEvent);
	return strHTML;
}