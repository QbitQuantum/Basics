// 回调函数
DWORD WINAPI EM_UserLogin::Proc_BC_Recv(LPVOID lParam)
{
	//CEIM02Dlg* pDlg = ((CEIM02Dlg*)AfxGetMainWnd());
	CEIM02Dlg *pDlg = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;

	HWND hWnd = pDlg->GetSafeHwnd();

	char buf[4096];
	char ip[128];
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (INVALID_SOCKET == sock)
	{
		AfxMessageBox(_T("socket() error in thread BCReceiver::MsgRecvProc"));
		return -1;
	}

	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(BROADCAST_RECV_PORT);

	int fromlen = sizeof(sin);

	if (SOCKET_ERROR == bind(sock, (PSOCKADDR)&sin, fromlen))
	{
		AfxMessageBox(_T("Broadcast receiver bind failed"));
		return -1;
	}
	int recvlen = 0;

	while (TRUE)
	{
		recvlen = recvfrom(sock, buf, 4096, 0, (PSOCKADDR)&sin, &fromlen);
		// 需要优化
		EM_DATA data(buf, recvlen);
		if (data.msg == EM_USERLOGIN
			|| data.msg == EM_USERLOGOUT
			|| data.msg == EM_USERRENAME
			|| data.msg == EM_USERREGROUP)
		{
			FreeEIM_USER *pUser;
			strcpy(ip, inet_ntoa(sin.sin_addr));
			char name[512];
			char hostname[128];
			char groupname[128];
			EM_UserInfo *ui = ((EM_UserInfo*)data.buf);
			ui->GetDisplayName(name);
			ui->GetHostName(hostname);
			ui->GetGroupName(groupname);
			EM_USERINFO uinfo(strupr(hostname), ip, groupname);

			if (data.msg == EM_USERLOGIN)
			{
				char *tmp = new char[128];
				strcpy(tmp, ip);
				// Add to tree ---------------------------------------------------
				pDlg->_User_AddNewUser(name, uinfo);
				// ===============================================================
				// Reply that i am online.---------------------------------------
				pDlg->SendMessage(WM_REPLYBCMSG, (WPARAM)tmp, NULL);
				// ===============================================================
			}
			else if (data.msg == EM_USERLOGOUT)
			{
				char *tmp = new char[128];
				strcpy(tmp, ip);
				::PostMessage(hWnd, WM_USERLOGOUT, (WPARAM)tmp, NULL);
				// pDlg->_User_DeleteUser(uinfo);
			}
			else
			{
				// 重新分配内存
				pUser = new FreeEIM_USER;

				if (data.msg == EM_USERRENAME)
					strcpy(pUser->m_szName, data.buf);
				else
					strcpy(pUser->m_szGroup, data.buf);

				strcpy(pUser->m_szIP, inet_ntoa(sin.sin_addr));

				::PostMessage(hWnd, WM_DESKUPDATEINFO, data.msg, (LPARAM)pUser);
			}
		}
	}
	return 1;
}