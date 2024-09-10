cNetZone * CNetWatcherTask::NewZoneByNet(NETWATCH::Network * netw)
{
	//if (netw->m_nFlags & IP_ADAPTER_DHCP_ENABLED && netw->DnsSuffix[0]==0)
	//	return 1;
	cNetAdapter *pAdapter=FindAdapterByID(netw->adapter_ID);
	if(!pAdapter)
	{
		PR_TRACE((g_root, prtERROR, TR "CNetWatcherTask::NewZoneByNet Error: cant find adapter with ID=%d",netw->adapter_ID));
		return 0;
	}

	Lock_settings();
	DWORD max_ID=m_settings.m_NextZoneID;
	while(TRUE)
	{
		DWORD x=0;
		while(x<m_adapters.size() || x<m_zones.size())
		{
			if(x<m_adapters.size() && m_adapters[x].m_nZoneID>=max_ID)
				break;
			if(x<m_zones.size() && m_zones[x].m_nID>=max_ID)
				break;
			x++;
		}
		if(x>=m_adapters.size() && x>=m_zones.size())
			break;
		max_ID++;
	}
	m_settings.m_NextZoneID=max_ID+1;
	Unlock_settings();

	cNetZone zone;
	cNetZone *pZona=&zone;
	if(netw->m_nIfType!=IF_TYPE_SOFTWARE_LOOPBACK)
	{
		if(pAdapter->m_nSettings & cNetAdapter::fAskWhenNewZones)
		{
			pZona->m_nSettings|=cNetZone::fNeedToAsk;
		}
		else
		{
			if(FindZoneByID(pAdapter->m_nUndefZoneID))
			{
				zone=*FindZoneByID(pAdapter->m_nUndefZoneID);
				pZona->SetState(fTemporary,TRUE);
			}
			else
			{
				PR_TRACE((g_root, prtIMPORTANT, TR "CNetWatcherTask:: Cant find default zone for adapter %S.",pAdapter->m_sAdapterFrendlyName.data()));
				pZona->m_nSettings|=cNetZone::fNeedToAsk;
			}	
		}
	}
	pZona->m_nID=max_ID;
	pZona->SetState(fVisible,TRUE); 
	pZona->SetConnected(TRUE);
	pZona->m_sAdapterWinName=netw->m_sAdapterWinName;
	pZona->m_nIfType=netw->m_nIfType;
	pZona->m_nAdapterID=netw->adapter_ID;
	_time32((__time32_t*)&pZona->m_nTimeCreated);
	pZona->m_sDnsSuffix=netw->DnsSuffix;
	pZona->m_nFlags=netw->m_nFlags;
	pZona->m_nTypeOfInterface=pAdapter->m_nTypeOfInterface;
	if(netw->HasIPv4)
	{
		if(netw->m_nIP4Net>0)
		{
			pZona->m_IP.SetV4(netw->m_nIP4Net);
			pZona->m_IP.SetV4MaskByIp(netw->m_nIP4NetMask);
		}
		pZona->m_nDhcpIPv4=netw->m_nDhcpIPv4;
		pZona->m_nDhcpMac=netw->m_nDhcpMac;
		pZona->m_nDhcpMacLen=netw->m_nDhcpMacLen;
		pZona->m_nGwIPv4=netw->m_nGwIPv4;
		pZona->m_nGwMac=netw->m_nGwMac;
		pZona->m_nGwMacLen=netw->m_nGwMacLen;
	}
	switch(netw->m_nIfType)
	{
		case MIB_IF_TYPE_PPP:
			pZona->m_sConnectionName=netw->AdapterFrendlyName;
			pZona->m_sFrendlyName=netw->AdapterFrendlyName;
			pZona->m_nSettings-=pZona->m_nSettings & cNetZone::fUptoGateway;
			pZona->m_nSeverity = cNetZone::znUntrusted;
			pZona->m_sRASPeer=netw->m_sRASPeer;
			break;
		case IF_TYPE_IEEE80211:
			pZona->m_sConnectionName=netw->SSID;
			pZona->m_sFrendlyName=netw->SSID;
			if(pZona->m_sDnsSuffix.size()>1)
			{
				if(pZona->m_sConnectionName.size()>0)
					pZona->m_sFrendlyName+="(";
				pZona->m_sFrendlyName+=pZona->m_sDnsSuffix;
				if(pZona->m_sConnectionName.size()>0)
					pZona->m_sFrendlyName+=")";
			}
			pZona->m_nWiFiSecurity=netw->m_nWiFiSecurity;
			pZona->m_nWiFiAuthMode=netw->m_nWiFiAuthMode;
			pZona->m_nWiFiType=netw->m_nWiFiType;
			if(!IsLocalArea(&pZona->m_IP) || pZona->m_nWiFiAuthMode==Ndis802_11AuthModeOpen || (
				pZona->m_nWiFiSecurity==Ndis802_11EncryptionNotSupported ||
				pZona->m_nWiFiSecurity==Ndis802_11EncryptionDisabled ||
				pZona->m_nWiFiSecurity==Ndis802_11Encryption1KeyAbsent
				))
				pZona->m_nSeverity = cNetZone::znUntrusted;
			else
				pZona->m_nSeverity=cNetZone::znNetBIOS;

			break;
		case IF_TYPE_SOFTWARE_LOOPBACK: 
			pZona->m_nTypeOfInterface=If_LoopBack;
			pZona->m_sFrendlyName="localhost";
			//pZona->SetState(fVisible,FALSE);
			pZona->m_nSeverity=cNetZone::znTrusted;
			pZona->m_nSettings-=pZona->m_nSettings & cNetZone::fNeedToAsk;
			break;

		default:  //ethernet
			if(IsLocalArea(&pZona->m_IP))
				pZona->m_nSeverity=cNetZone::znNetBIOS;		
			else
				pZona->m_nSeverity=cNetZone::znUntrusted;
			pZona->m_nMac=netw->m_nMac;
			pZona->m_nMacLen=netw->m_nMacLen;
			pZona->m_sConnectionName=netw->AdapterDesc;
			pZona->m_sFrendlyName=netw->AdapterFrendlyName;

			if(netw->m_nFlags & IP_ADAPTER_DHCP_ENABLED && pZona->m_sDnsSuffix.size()>0)
			{
				pZona->m_sFrendlyName=pZona->m_sDnsSuffix;
				pZona->m_sFrendlyName+="(";
				pZona->m_sFrendlyName+=netw->AdapterFrendlyName;
				pZona->m_sFrendlyName+=")";
			}
			else
			{
				if(netw->m_nIP4Net>0)
				{
					cIpMask ip; 
					ip.SetV4(netw->m_nIP4Net);
					ip.SetV4MaskByIp(netw->m_nIP4NetMask);
					char str1[100];
					ip.ToStr(str1,100);
					pZona->m_sFrendlyName=str1;
					pZona->m_sFrendlyName+="(";
					pZona->m_sFrendlyName+=netw->AdapterFrendlyName;
					pZona->m_sFrendlyName+=")";
				}
			}
			pZona->m_nSettings|=cNetZone::fARPWatch;
	}
	PR_TRACE((g_root, prtIMPORTANT, TR "CNetWatcherTask:: Add new zone %S\n",zone.m_sFrendlyName));
	if(pZona->QState(fTemporary))
		pZona->m_sFrendlyName+="(temporary)";
	pZona=&m_zones.push_back(zone);
	return pZona;
}