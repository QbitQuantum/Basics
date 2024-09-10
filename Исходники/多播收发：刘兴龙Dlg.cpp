void C多播收发：刘兴龙Dlg::OnBnClickedRadio1()
{
	// 接收消息上线
	if (Setinfo==0){
		MessageBox(L"还未设置好，请先设置！");
		CButton* radio = (CButton*)GetDlgItem(IDC_RADIO1);
		radio->SetCheck(0);
	}
	else{
		if (flag == 0){
			flag = 1;
			str = L"";
			UpdateData(FALSE);
			/* struct ip_mreq mcast;// Winsock1.0 */

			//初始化 WinSock2.2
			if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0){
				//printf("WSAStartup() failed\n");
				flag = 0;
				MessageBox(L"Sock 初始化失败！");
				return;
			}
			/*
			创建一个SOCK_DGRAM类型的SOCKET
			其中，WSA_FLAG_MULTIPOINT_C_LEAF 表示 IP 多播在控制面层上属于“无根”类型；
			WSA_FLAG_MULTIPOINT_D_LEAF 表示 IP 多播在数据面层上属于“无根”，有关控制面层和
			数据面层有关概念请阅读MSDN说明
			*/
			if ((sock = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF | WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET){
				//printf("socket failed with:%d\n", WSAGetLastError());
				WSACleanup();
				flag = 0;
				MessageBox(L"Socket 创建失败！");
				return;
			}
			//将 sock 绑定到本机某端口上。
			local.sin_family = AF_INET;
			local.sin_port = htons(MCASTPORT);
			local.sin_addr.s_addr = INADDR_ANY;

			if (bind(sock, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR){
				//printf("bind failed with:%d\n", WSAGetLastError());		
				closesocket(sock);
				WSACleanup();
				flag = 0;
				//	AfxEndThread(0);
				MessageBox(L"Sock 绑定本机端口失败！");
				return;
			}
			//加入多播组
			remote.sin_family = AF_INET;
			remote.sin_port = htons(MCASTPORT);
			remote.sin_addr.s_addr = inet_addr(MCASTADDR);

			/* Winsock2.0 */
			if ((sockM = WSAJoinLeaf(sock, (SOCKADDR*)&remote, sizeof(remote), NULL, NULL, NULL, NULL, JL_BOTH)) == INVALID_SOCKET){
				//printf("WSAJoinLeaf() failed:%d\n", WSAGetLastError());
				closesocket(sock);
				WSACleanup();
				flag = 0;
				MessageBox(L"加入播数组失败！");
				return;
			}
			MessageBox(L"上线成功！");
			AfxBeginThread(TestThreadFun, this);
		}else{
			MessageBox(L"以是上线状态了！");
		}
	}
}