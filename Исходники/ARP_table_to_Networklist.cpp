BOOL CNetWatcherTask::UpdateARPWatch(PMIB_IPNETTABLE ARPTable)
{
	if(!ARPTable)
		return 0;
	DWORD ArpChanged=0;
	PMIB_IPNETROW table=ARPTable->table;
	DWORD dwNumEntries=ARPTable->dwNumEntries;
	DWORD ARPSize=m_ARPWatch.size();
	DWORD last_index=0;
	DWORD zone_ID=0;
	for(DWORD x=0;x<dwNumEntries;x++)
	{
		PMIB_IPNETROW IpMac=&table[x];
		if(IpMac->dwType<3)
			continue;
		if(IpMac->dwIndex!=last_index)
		{
			last_index=IpMac->dwIndex;
			zone_ID=m_ArpWatchZones[last_index];	
		}
		if(zone_ID==0)
			continue;	
		DWORD ip=IpMac->dwAddr;
		DWORD y;
		cARPWatch *row=0;
		for(y=0;y<ARPSize;y++)
		{
			row=&m_ARPWatch[y];
			if(row->m_nTimeDeleted==0 && 
				 zone_ID==row->m_nZoneID && ip==row->m_nIP4)
			{
				if(row->m_nMacLen!=min(IpMac->dwPhysAddrLen,sizeof(row->m_nMac)) ||
				memcmp(&row->m_nMac,IpMac->bPhysAddr,row->m_nMacLen)!=0)
				{
					_time32((__time32_t*)&row->m_nTimeDeleted);
				}
				break;
			}
		}
		if(y==ARPSize || row==0 || row->m_nTimeDeleted)
		{
			ArpChanged=1;
			cARPWatch new_row;
			new_row.m_nIP4=ip;
			new_row.m_nZoneID=zone_ID;
			new_row.m_nMacLen=min(IpMac->dwPhysAddrLen,sizeof(new_row.m_nMac));
			memcpy(&new_row.m_nMac,IpMac->bPhysAddr,new_row.m_nMacLen);
			_time32((__time32_t*)&new_row.m_nTimeCreated);
			if(y!=ARPSize)
			{
				//message to user. ARP changed!
				//old m_ARPWatch[y], new new_row
				m_ARPWatch.push_back(new_row);
				PR_TRACE((g_root, prtIMPORTANT, TR "CNetWatcherTask:: ARP changed"));

			}
			else
			{
				//New ARP! new_row
				m_ARPWatch.push_back(new_row);
			}
			//aSize=m_ARPWatch.size();
		}
		
	}
	return ArpChanged;
}