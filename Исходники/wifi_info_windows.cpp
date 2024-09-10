void WiFiInfo::Impl::RequestWiFiBSSIDs(WifiRequestCallbackT callback)
{
  m_callback = callback;
  // if it's XP without necessary api... use gateway instead
  if (!pWlanGetNetworkBssList)
  {
    vector<WiFiInfo::AccessPoint> apns;
    GatewaysInfo(apns);
    callback(apns);
    return;
  }

  if (!m_isNotificationSupported)
  { // request timer after 4 seconds, when scanning completes
    CreateTimerQueueTimer(&m_timer, NULL, &WaitOrTimerCallback, this,
                          4100, 0, WT_EXECUTEONLYONCE);
  }
  else
  { // subscribe to notification when scanning is completed
    WlanRegisterNotification(m_hClient,
                             WLAN_NOTIFICATION_SOURCE_ACM,
                             TRUE,
                             &OnWlanScanCompleted,
                             this,
                             NULL,
                             NULL);
  }
  // start scanning
  PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
  DWORD dwResult = WlanEnumInterfaces(m_hClient, NULL, &pIfList);
  if (dwResult == ERROR_SUCCESS)
  {
    for (int ifIndex = 0; ifIndex < static_cast<int>(pIfList->dwNumberOfItems); ++ifIndex)
    {
      PWLAN_INTERFACE_INFO pIfInfo = (PWLAN_INTERFACE_INFO)&pIfList->InterfaceInfo[ifIndex];
      WlanScan(m_hClient, &pIfInfo->InterfaceGuid, NULL, NULL, NULL);
    }
    WlanFreeMemory(pIfList);
  }
}