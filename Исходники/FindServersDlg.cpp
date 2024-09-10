void CFindServersDlg::AddServer(const WFindServers::SERVER_INFO& Info, CServerInfoArray& List)
{
	CServerInfo	si;
	si.m_HostName = Info.Name;
	si.m_HostName.MakeUpper();
	si.m_IPAddress = Info.IPAddress;
	si.m_BinIPAddr = ntohl(inet_addr(Info.IPAddress));
	si.m_Status = Info.Status;
	if (si.m_Status) {
		si.m_ClientHostName = GetHostByAddr(Info.ExtStatus.ClientIPAddress);
		si.m_ClientBinIPAddr = ntohl(Info.ExtStatus.ClientIPAddress.S_un.S_addr);
		si.m_ClientIPAddress = inet_ntoa(Info.ExtStatus.ClientIPAddress);
	}
	List.Add(si);
}