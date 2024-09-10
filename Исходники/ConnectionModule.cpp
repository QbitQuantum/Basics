void ConnectionModule::ConnectToHosts(vector<SupernodeHost> &hosts)
{
	
	if(p_critical_section==NULL)
	{
		return;
	}

	int i;

	// Tell the thread to connect to these hosts
	CSingleLock singleLock(p_critical_section);
	singleLock.Lock();
	if(singleLock.IsLocked())
	{
		*p_thread_data->p_connect_hosts=hosts;
		WSASetEvent(p_thread_data->m_reserved_events[1]);	// vector data
		singleLock.Unlock();
	}

	// Keep track of the connect to hosts for when we are checking to see if we can add an ip to the cache
	v_connect_to_ips.clear();
	for(i=0;i<(int)hosts.size();i++)
	{
		v_connect_to_ips.push_back(hosts[i].m_ip);
	}
	
	sort(v_connect_to_ips.begin(),v_connect_to_ips.end());

	// Add these hosts to the connected hosts vector, just so that another mod won't connect to them since i am connecting to them
//	for(i=0;i<hosts.size();i++)
//	{
//		v_connected_host_ips.push_back(hosts[i].IP());
//	}

}