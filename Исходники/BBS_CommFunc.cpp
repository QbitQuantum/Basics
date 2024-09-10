//
// Get Default Information (IP, GateWay, DNS, HostName, DHCP, etc..)
void GetWlanDefaultInformation(PBBS_ADAPTER_INFO pInformation)
{
	
	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	PFIXED_INFO pNetworkParams = NULL;

	ULONG ulSizeAdapterInfo = 0;
	DWORD dwReturnvalueGetAdapterInfo = 0;
	TCHAR tszAdapterNameTemp[MAX_ADAPTER_NAME_LENGTH + 4] = {'\0',};
	ULONG uSizeNetworkParams = 0;
	DWORD dwReturnvalueGetNetworkParams;

	BOOL bFindWirelessAdapter = FALSE;

	pInformation->tszAdapterName[0] = L'\0';
	memset( pInformation, 0x0, sizeof(BBS_ADAPTER_INFO) );

	// -----------------------GetAdaptersInfo-----------------------------------------

	dwReturnvalueGetAdapterInfo = GetAdaptersInfo( pAdapterInfo, &ulSizeAdapterInfo );
	if ( dwReturnvalueGetAdapterInfo == ERROR_BUFFER_OVERFLOW)
	{
		if (!(pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulSizeAdapterInfo)))
		{
			return;
		}

		dwReturnvalueGetAdapterInfo = GetAdaptersInfo( pAdapterInfo, &ulSizeAdapterInfo);
		if (dwReturnvalueGetAdapterInfo != ERROR_SUCCESS)
		{
			free(pAdapterInfo);
			return;
		}

		while (pAdapterInfo != NULL)
		{
			mbstowcs( tszAdapterNameTemp, pAdapterInfo->AdapterName, MAX_ADAPTER_NAME_LENGTH + 4 );

			// Wireless 아답터 인지 확인
			// Nids의 OID_GEN_PHYSICAL_MEDIUM 로 NdisPhysicalMediumWirelessLan 임을 확인하는 방법이 있으나, 아답터 전원Off 상태에서는 조회 되지 않음
			// Summit 모듈도 확인하기 위해서, Wzctool은 사용하지 않음

			for(int i=0; i< sizeof(ManageableAdapters) / sizeof(ManageableAdapters[0]); i++)
			{
				if( _tcscmp(tszAdapterNameTemp, ManageableAdapters[i]) == 0 )
				{
					bFindWirelessAdapter = TRUE;
				}
			}

			if( bFindWirelessAdapter ) 
			{
				// Adapter Name
				_tcscpy(pInformation->tszAdapterName, tszAdapterNameTemp);

				// IPAddr
				mbstowcs( pInformation->tszIPAddr, pAdapterInfo->IpAddressList.IpAddress.String, sizeof(pAdapterInfo->IpAddressList.IpAddress.String) );

				// Subnet Mask
				mbstowcs( pInformation->tszSubNetMask, pAdapterInfo->IpAddressList.IpMask.String, sizeof(pAdapterInfo->IpAddressList.IpMask.String) );

				// Default GateWay
				mbstowcs( pInformation->tszDefaultGateWay, pAdapterInfo->GatewayList.IpAddress.String, sizeof(pAdapterInfo->GatewayList.IpAddress.String) );

				// Mac Address
				_stprintf( pInformation->tszMacAddr, _T("%02X:%02X:%02X:%02X:%02X:%02X"), pAdapterInfo->Address[0],pAdapterInfo->Address[1],pAdapterInfo->Address[2],pAdapterInfo->Address[3],pAdapterInfo->Address[4],pAdapterInfo->Address[5] );

				// DHCP Enabled
				pInformation->bDHCPEnabled = (BOOL)pAdapterInfo->DhcpEnabled;

				break;
			}
			pAdapterInfo = pAdapterInfo->Next;
		}
	}

	if(pAdapterInfo)
	{
		free(pAdapterInfo);
	}


	// ---------------------GetNetwork Params --------------------------

	dwReturnvalueGetNetworkParams = GetNetworkParams(pNetworkParams , &uSizeNetworkParams);
	if (dwReturnvalueGetNetworkParams == ERROR_BUFFER_OVERFLOW)
	{
		if (!(pNetworkParams = (PFIXED_INFO) malloc(uSizeNetworkParams)))
		{
			return;
		}

		dwReturnvalueGetNetworkParams = GetNetworkParams(pNetworkParams, &uSizeNetworkParams);
		if (dwReturnvalueGetNetworkParams != ERROR_SUCCESS)
		{
			free(pNetworkParams);
			return;
		}
	}

	// Host Name
	mbstowcs( pInformation->tszHostName, pNetworkParams->HostName, sizeof(pNetworkParams->HostName) );

	// Dns Server
	mbstowcs( pInformation->tszDnsAddr, pNetworkParams->DnsServerList.IpAddress.String, sizeof(pNetworkParams->DnsServerList.IpAddress.String) );


	if(pNetworkParams)
	{
		free(pNetworkParams);
	}

	return;
}