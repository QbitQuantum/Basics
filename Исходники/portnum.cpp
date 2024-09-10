int GetPortNum(
    HDEVINFO hDevInfo,
    PSP_DEVINFO_DATA pDevInfoData)
{
  HKEY hKey;

  hKey = SetupDiOpenDevRegKey(hDevInfo, pDevInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);

  if (hKey == INVALID_HANDLE_VALUE)
    return -1;

  int num;
  DWORD len;
  DWORD portNum;

  len = sizeof(portNum);

  if (RegQueryValueEx(hKey, C0C_REGSTR_VAL_PORT_NUM, NULL, NULL, (PBYTE)&portNum, &len) == ERROR_SUCCESS)
    num = portNum;
  else
    num = -1;

  RegCloseKey(hKey);

  return num;
}