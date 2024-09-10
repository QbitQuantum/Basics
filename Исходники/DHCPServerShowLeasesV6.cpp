DWORD __cdecl main(int argc, char* argv[])
{
    DHCP_RESUME_HANDLE ResumeHandle = 0;
	LPDHCPV6_IP_ARRAY EnumScopesV6 = NULL;
	DWORD nReadV6 = 0, nTotalV6 = 0;
	DHCP_RESUME_IPV6_HANDLE ResumeHandleV6 = {0,0};
	LPDHCP_CLIENT_INFO_ARRAY_V6 ClientsV6 = NULL;
    DWORD  nClientsReadV6 = 0, nClientsTotalV6 = 0;
	DWORD error1 = ERROR_SUCCESS, error2 = ERROR_SUCCESS;
    WCHAR *szDateTimeStr = NULL, *szDuid = NULL, *szClientIp = NULL, *szScopeIp = NULL;

    WCHAR szServer[SERVERNAME_BUF_SIZE] = {0};
    if (2 != argc)
    {
        wprintf(L"Usage: DhcpServerShowLeasesV6.exe <Server IpAdd/Name>");
        return ERROR_INVALID_PARAMETER;
    }
    MultiByteToWideChar(0, 0, argv[1], (int)strlen(argv[1]), szServer, SERVERNAME_BUF_SIZE);      
    do {
        // enumerate all the IpV6 scopes on the server.
        error1 = DhcpEnumSubnetsV6(szServer, &ResumeHandle, (DWORD)~0, &EnumScopesV6, &nReadV6, &nTotalV6);
        if (0 == nTotalV6)
        {
            wprintf(L"No scopes on this server.\n");
        }
        if (ERROR_NO_MORE_ITEMS == error1) // there are no IpV6 scopes
        {
            break;
        }
	    if (ERROR_SUCCESS != error1 && ERROR_MORE_DATA != error1)
	    {
            wprintf(L"DhcpServerShowLeasesV6 returned with error: %d\n",error1); 
            return error1;
	    }
        // iterating over all the scopes one by one to get the clients for each scope.
	    for (unsigned int count=0; count < EnumScopesV6->NumElements; count++)
	    {
            // converting scope IP address from DHCP_IPV6_ADDRESS to LPWSTR
            szScopeIp = ConvertIpV6AddtoWstr(EnumScopesV6->Elements[count]);
            wprintf(L"\nScope : %s\n\n", szScopeIp ? szScopeIp : L" ");
 		    do {
                // enumerating the clients on a specific IpV6 scope
                //the leases shown include all the leases present and can be filtered out on the basic of Address State attribute of client.
		        error2 = DhcpEnumSubnetClientsV6(szServer, EnumScopesV6->Elements[count], &ResumeHandleV6, (DWORD)~0, &ClientsV6, &nClientsReadV6, &nClientsTotalV6);
                if (0 == nClientsTotalV6)
                {
                    wprintf(L"No clients on this scope.\n");
                }
                if (ERROR_NO_MORE_ITEMS == error2)
                {
                    break;
                }
		        if (ERROR_SUCCESS != error2 && ERROR_MORE_DATA != error2)
		        {
                    wprintf(L"DhcpServerShowLeasesV6 returned with error: %d\n",error2); 
                    return error2;
		        }
                //iterating over all the clients on a speicified scope.
                for (unsigned int count = 0; count < ClientsV6->NumElements; count++)
  	            {
                    //converting client Ip from DHCP_IPV6_ADDRESS to LPWSTR
                    szClientIp = ConvertIpV6AddtoWstr(ClientsV6->Clients[count]->ClientIpAddress);
                    wprintf(L"ClientAddress   : %s\n",szClientIp ? szClientIp : L" ");
                    //converting client DUID from byte * to LPWSTR
                    szDuid = GetHardwareAddress(ClientsV6->Clients[count]->ClientDUID);
                    wprintf(L"DUID            : %s\n",szDuid ? szDuid : L" ");
                    wprintf(L"IAID            : %d\n",ClientsV6->Clients[count]->IAID);
                    // if lease duration is infinite then lease never expires. 
                    if (DHCP_DATE_TIME_INFINITE_LOW == ClientsV6->Clients[count]->ClientValidLeaseExpires.dwLowDateTime && 
                        DHCP_DATE_TIME_INFINITE_HIGH == ClientsV6->Clients[count]->ClientValidLeaseExpires.dwHighDateTime)
                    {
                        wprintf(L"Lease Expires   : Never\n\n");
                    }
                    // if lease duration is 0 the client is inactive.
                    else if (DHCP_DATE_TIME_ZERO_LOW == ClientsV6->Clients[count]->ClientValidLeaseExpires.dwLowDateTime && 
                             DHCP_DATE_TIME_ZERO_HIGH == ClientsV6->Clients[count]->ClientValidLeaseExpires.dwHighDateTime)
                    {
                        wprintf(L"Lease Expires   : Inactive\n\n");
                    }
                    else
                    {
                        // converting the date time information from FILETIME * to LPWSTR.
                        szDateTimeStr = GetDateTimeString(*(FILETIME *)(&ClientsV6->Clients[count]->ClientValidLeaseExpires));
                        wprintf(L"Lease Expires   : %s\n\n", szDateTimeStr ? szDateTimeStr : L" ");
                    }
                    if (NULL != szClientIp)
                    {
                        free(szClientIp);
                        szClientIp = NULL;
                    }
                    if (NULL != szDuid)
                    {
                        free(szDuid);
                        szDuid = NULL;
                    }
                    if (NULL != szDateTimeStr)
                    {
                        free(szDateTimeStr);
                        szDateTimeStr = NULL;
                    }
	            }
                if (NULL != ClientsV6)
                {
                    DhcpRpcFreeMemory(ClientsV6);
                    ClientsV6 = NULL;
                }
                nClientsReadV6 = 0;
		        nClientsTotalV6 = 0;
            } while (ERROR_MORE_DATA == error2);
            if (NULL != szScopeIp)
            {
                free(szScopeIp);
                szScopeIp = NULL;
            }
	    }
        nReadV6 = 0;
        nTotalV6 = 0;
        if (NULL != EnumScopesV6)
        {
            DhcpRpcFreeMemory(EnumScopesV6);    
            EnumScopesV6 = NULL;
        }
    } while (ERROR_MORE_DATA == error1);
	return 0;
}