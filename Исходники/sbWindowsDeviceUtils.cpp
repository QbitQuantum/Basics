nsresult
sbWinDeviceEject(DEVINST aDevInst)
{
  CONFIGRET cfgRet;

  // Try ejecting the device three times.
  WCHAR         vetoName[MAX_PATH];
  PNP_VETO_TYPE vetoType;
  bool        ejected = PR_FALSE;
  for (int i = 0; i < 3; i++) {
    // Try ejecting using CM_Request_Device_Eject.
    cfgRet = CM_Request_Device_EjectW(aDevInst,
                                      &vetoType,
                                      vetoName,
                                      MAX_PATH,
                                      0);
    if (cfgRet == CR_SUCCESS) {
      ejected = PR_TRUE;
      break;
    }
    // Wait for 1/10 second to give the device time to handle the eject.
    // This probably isn't needed, but all the examples I saw that used
    // the functions always put in a delay between calls at least for retries
    Sleep(100);
    // Try ejecting using CM_Query_And_Remove_SubTree.
    cfgRet = CM_Query_And_Remove_SubTreeW(aDevInst,
                                          &vetoType,
                                          vetoName,
                                          MAX_PATH,
                                          CM_REMOVE_NO_RESTART);
    if (cfgRet == CR_SUCCESS) {
      ejected = PR_TRUE;
      break;
    }
    // Wait 1/2 before retrying so we don't just slam the device with a bunch
    // of eject/remove requests and fail out.
    Sleep(500);
  }

  // Try one last time and let the PnP manager notify the user of failure.
  if (!ejected) {
    cfgRet = CM_Request_Device_Eject(aDevInst, NULL, NULL, 0, 0);
    NS_ENSURE_TRUE(cfgRet == CR_SUCCESS, NS_ERROR_FAILURE);
  }

  return NS_OK;
}