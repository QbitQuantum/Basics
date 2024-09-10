int MainWindow::checkWlanHosteed(){
    DWORD dwError = 0;
    DWORD dwServiceVersion = 0;
    HANDLE hClient = NULL;

    if (ERROR_SUCCESS != (dwError = WlanOpenHandle(
                        WLAN_API_VERSION,
                        NULL,               // reserved
                        &dwServiceVersion,
                        &hClient
                        )))
    {
        return dwError;
    }

    // check service version
    if (WLAN_API_VERSION_MAJOR(dwServiceVersion) < WLAN_API_VERSION_MAJOR(WLAN_API_VERSION_2_0))
    {
        WlanCloseHandle(hClient, NULL);
        return -1;
    }


    std::string strSSID = "test";
    std::string strSecondaryKey = "123456780";

    // Set the network mode to allow
    BOOL bIsAllow = TRUE;
    WLAN_HOSTED_NETWORK_REASON dwFailedReason;
    DWORD dwReturnValue = WlanHostedNetworkSetProperty(hClient,
                                                       wlan_hosted_network_opcode_enable,
                                                       sizeof(BOOL),
                                                       &bIsAllow,
                                                       &dwFailedReason,
                                                       NULL);

    if(ERROR_SUCCESS != dwReturnValue)
    {
        return dwReturnValue;
    }

    // Set the network SSID and the maximum number of connections
    WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS wlanConnectionSetting;
    memset(&wlanConnectionSetting, 0, sizeof(WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS));

    // The SSID field in WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS must be of type ANSI, so if the program uses the Unicode, you need to do the conversion.
#ifdef _UNICODE
    WideCharToMultiByte(CP_ACP,
                        0,
                        strSSID.c_str(),   // Save SSID CString types
                        strSSID.length(),    // SSID the length of a string
                        (LPSTR)wlanConnectionSetting.hostedNetworkSSID.ucSSID,
                        32,
                        NULL,
                        NULL);
#else
    memcpy(wlanConnectionSetting.hostedNetworkSSID.ucSSID, strSSID.c_str(), strlen(strSSID.c_str()));
#endif

    wlanConnectionSetting.hostedNetworkSSID.uSSIDLength = strlen((const char*)wlanConnectionSetting.hostedNetworkSSID.ucSSID);
    wlanConnectionSetting.dwMaxNumberOfPeers = 100;

    dwReturnValue = WlanHostedNetworkSetProperty(hClient,
                                                 wlan_hosted_network_opcode_connection_settings,
                                                 sizeof(WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS),
                                                 &wlanConnectionSetting,
                                                 &dwFailedReason,
                                                 NULL);
    if(ERROR_SUCCESS != dwReturnValue)
    {
        return dwReturnValue;
    }

    UCHAR keyBuf[100] = {0};
#ifdef _UNICODE
    WideCharToMultiByte(CP_ACP,
                        0,
                        strSecondaryKey.c_str(),
                        strSecondaryKey.length(),
                        (LPSTR)keyBuf,
                        100,
                        NULL,
                        NULL);
#else
    memcpy(keyBuf, strSecondaryKey.c_str(), strSecondaryKey.length());
#endif
    dwReturnValue = WlanHostedNetworkSetSecondaryKey(hClient,
                                                     strlen((const char*)keyBuf) + 1,
                                                     keyBuf,
                                                     TRUE,
                                                     FALSE,
                                                     &dwFailedReason,
                                                     NULL);
    if(ERROR_SUCCESS != dwReturnValue)
    {
        return dwReturnValue;
    }

    dwReturnValue = WlanHostedNetworkStartUsing(hClient, &dwFailedReason, NULL);
    if(ERROR_SUCCESS != dwReturnValue)
    {
        if (wlan_hosted_network_reason_interface_unavailable == dwFailedReason)
        {
            return dwFailedReason;
        }
        return dwReturnValue;
    }



    /*PIP_ADAPTER_INFO pAdapterInfo;
      pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
      ULONG buflen = sizeof(IP_ADAPTER_INFO);

      if(GetAdaptersInfo(pAdapterInfo, &buflen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc(buflen);
      }

      if(GetAdaptersInfo(pAdapterInfo, &buflen) == NO_ERROR) {
        PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
        while (pAdapter) {
          QString str = QString("\tAdapter Name: \t%1\n\
\tAdapter Desc: \t%2\n\
\tIP Address: \t%3\n\
\tGateway: \t%4\n").arg(pAdapter->AdapterName)
                  .arg(pAdapter->Description)
                  //.arg((byte*)pAdapter->Address)
                  .arg(pAdapter->IpAddressList.IpAddress.String)
                  .arg(pAdapter->GatewayList.IpAddress.String);
          pAdapter = pAdapter->Next;
          QMessageBox msg(this);
          msg.setText(str);
          msg.exec();
        }
      } else {
        printf("Call to GetAdaptersInfo failed.\n");
      }*/



    CoInitialize (NULL);

    // init security to enum RAS connections
    CoInitializeSecurity (NULL, -1, NULL, NULL,
                          RPC_C_AUTHN_LEVEL_PKT,
                          RPC_C_IMP_LEVEL_IMPERSONATE,
                          NULL, EOAC_NONE, NULL);

    INetSharingManager * pNSM = NULL;
    HRESULT hr = ::CoCreateInstance (__uuidof(NetSharingManager),
                                     NULL,
                                     CLSCTX_ALL,
                                     __uuidof(INetSharingManager),
                                     (void**)&pNSM);
    if(hr == S_OK){
            // in case it exists already
            //DeletePortMapping (pNSM, NAT_PROTOCOL_TCP, 555);

            // add a port mapping to every shared or firewalled connection.
                    hr = DoTheWork (pNSM);
                   pNSM->Release();
            if (hr!= S_OK){
                return hr;
            }

    }else return hr;

    return 0;
}