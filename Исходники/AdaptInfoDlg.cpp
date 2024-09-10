void CAdaptInfoDlg::ShowAdaptersInfo()
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD errValue = 0;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	if (!pAdapterInfo)//malloc失败
		return;
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) //空间不够，重新分配
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
		if (!pAdapterInfo) //malloc失败
			return;
	}
	CString info;
	if ((errValue = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			info += CString(_T("Adapter Name:")) + CString(pAdapter->AdapterName) + CString(_T("\r\n"));//名字
			info += CString(_T("Adapter Desc:")) + CString(pAdapter->Description) + CString(_T("\r\n"));//描述
			CString mac;
			mac.Format(_T("%02X%02X%02X%02X%02X%02X"), pAdapter->Address[0], pAdapter->Address[1], \
				pAdapter->Address[2], pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
			info += CString(_T("Adapter Mac:")) + mac + CString(_T("\r\n"));//MAC地址
			CString type;
			switch (pAdapter->Type) //类型，列举了几种
			{
			case MIB_IF_TYPE_OTHER:
				type = _T("其他");
				break;
			case MIB_IF_TYPE_ETHERNET:
				type = _T("以太网接口");
				break;
			case IF_TYPE_ISO88025_TOKENRING:
				type = _T("ISO88025令牌环");
				break;
			case MIB_IF_TYPE_PPP:
				type = _T("PPP接口");
				break;
			case MIB_IF_TYPE_LOOPBACK:
				type = _T("软件回路接口");
				break;
			case MIB_IF_TYPE_SLIP:
				type = _T("ATM网络接口");
				break;
			case IF_TYPE_IEEE80211:
				type = _T("无线网络接口");
				break;
			default:
				type = _T("未知接口");
				break;
			}
			info += CString(_T("网卡类型：")) + type + CString(_T("\r\n"));
			info += CString(_T("IP地址：")) + CString(pAdapter->IpAddressList.IpAddress.String) + CString(_T("\r\n"));
			info += CString(_T("子网掩码：")) + CString(pAdapter->IpAddressList.IpMask.String) + CString(_T("\r\n"));
			info += CString(_T("默认网关：")) + CString(pAdapter->GatewayList.IpAddress.String) + CString(_T("\r\n"));
			info += CString(_T("是否DHCP：")) + CString(pAdapter->DhcpEnabled ? _T("是") : _T("否")) + CString(_T("\r\n"));
			info += CString(_T("DHCP地址：")) + CString(pAdapter->DhcpServer.IpAddress.String) + CString(_T("\r\n"));
			//Dns
			IP_PER_ADAPTER_INFO* pPerAdapt = NULL;
			ULONG ulLen = 0;
			int err = GetPerAdapterInfo(pAdapter->Index, pPerAdapt, &ulLen);
			if (err == ERROR_BUFFER_OVERFLOW)
			{
				pPerAdapt = (IP_PER_ADAPTER_INFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ulLen);
				err = GetPerAdapterInfo(pAdapter->Index, pPerAdapt, &ulLen);
				if (err == ERROR_SUCCESS)
				{
					IP_ADDR_STRING* pNext = &(pPerAdapt->DnsServerList);
					if (pNext && strcmp(pNext->IpAddress.String, "") != 0)//手动DNS
					{
						info = info + CString(_T("DNS：")) + CString(pNext->IpAddress.String) + _T("\r\n");
						if (pNext->Next)
						{
							pNext = pNext->Next;
							info = info + CString(_T("备用DNS：")) + CString(pNext->IpAddress.String) + _T("\r\n");
						}
					}
				}
				HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pPerAdapt);
			}
			info += "\r\n";
			pAdapter = pAdapter->Next;
		}
	}
	else
	{
		CString s;
		s.Format(_T("GetAdaptersInfo failed with error: %d\r\n"), errValue);
		info += s;
	}
	if (pAdapterInfo)
		free(pAdapterInfo);
	SetDlgItemText(IDC_EDIT, info);
}