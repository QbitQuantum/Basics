//代理测试
VOID CCollocateProxy::OnBnClickedProxyTest()
{
	//代理类型
	BYTE cbProxyType=(BYTE)m_cmProxyType.GetItemData(m_cmProxyType.GetCurSel());

	//代理信息
	tagProxyServer ProxyServer;
	ZeroMemory(&ProxyServer,sizeof(ProxyServer));
	ProxyServer.wProxyPort=GetDlgItemInt(IDC_PROXY_PORT);
	GetDlgItemText(IDC_PROXY_USER,ProxyServer.szUserName,CountArray(ProxyServer.szUserName));
	GetDlgItemText(IDC_PROXY_PASS,ProxyServer.szPassword,CountArray(ProxyServer.szPassword));
	GetDlgItemText(IDC_PROXY_SERVER,ProxyServer.szProxyServer,CountArray(ProxyServer.szProxyServer));

	//效验代理
	if (cbProxyType!=PROXY_NONE)
	{
		//代理地址
		if (ProxyServer.szProxyServer[0]==0)
		{
			//错误提示
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("代理服务器地址不能为空，请重新输入！"),MB_ICONERROR,30);

			//设置焦点
			m_edProxyServer.SetFocus();

			return;
		}

		//代理端口
		if (ProxyServer.wProxyPort==0)
		{
			//错误提示
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("请输入代理服务器端口号，例如：1080！"),MB_ICONERROR,30);

			//设置焦点
			m_edProxyPort.SetFocus();

			return;
		}
	}
	else 
	{
		//错误提示
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请先选择代理服务器类型与代理服务器连接信息！"),MB_ICONERROR,30);

		//设置焦点
		m_cmProxyType.SetFocus();

		return;
	}

	//创建组件
	CWHNetworkHelper WHNetworkModule;
	if (WHNetworkModule.CreateInstance()==false)
	{
		ShowInformation(TEXT("网络服务管理组件创建失败，测试失败！"),MB_ICONERROR,30);
		return;
	}

	//代理测试
	switch (WHNetworkModule->ProxyServerTesting(cbProxyType,ProxyServer))
	{
	case CONNECT_SUCCESS:				//连接成功
		{
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("代理服务器工作正常！"),MB_ICONINFORMATION);
			return;
		}
	case CONNECT_PROXY_USER_INVALID:	//用户错误
		{
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("代理服务器用户名或者密码错误！"),MB_ICONERROR);
			return;
		}
	default:							//默认处理
		{
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("代理服务器不存在或者连接失败！"),MB_ICONERROR);
			return;
		}
	}

	return;
}