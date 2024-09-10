BOOL CEnumerateSerial::EnumeratePorts()
{
  int SPDRPlist[] = {
    SPDRP_HARDWAREID, SPDRP_DEVICEDESC, SPDRP_FRIENDLYNAME, SPDRP_MFG,
    SPDRP_LOCATION_INFORMATION, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME, 
    -1};

  // Clear anything from previous enumerate...
  ResetPortList();

  // First need to convert the name "Ports" to a GUID using SetupDiClassGuidsFromName...
  DWORD dwGuids = 0;
  SetupDiClassGuidsFromName(_T("Ports"), NULL, 0, &dwGuids);
  if (dwGuids == 0) return FALSE;

  // Allocate the needed memory...
  CHeapPtr<GUID> GuidArray;
  GUID *pGuids = (GUID*)GuidArray.Allocate(sizeof(GUID) * dwGuids);
  if (pGuids==NULL) {
    SetLastError(ERROR_OUTOFMEMORY);
    return FALSE;
  }

  // Call the function again...
  if (!SetupDiClassGuidsFromName(_T("Ports"), pGuids, dwGuids, &dwGuids))
    return FALSE;

  // Now create a "device information set" which is required to enumerate all the ports...
  HDEVINFO hDevInfoSet = SetupDiGetClassDevs(pGuids, NULL, NULL, DIGCF_PRESENT);
  if (hDevInfoSet == INVALID_HANDLE_VALUE)
    return FALSE;

  // Finally do the enumeration...
  int nIndex = 0;
  SP_DEVINFO_DATA devInfo;
  CHeapPtr<TCHAR> tempstr(1000);
  CSerialPortInfo *portinfo = NULL;

  // Enumerate the current device...
  devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
  while (SetupDiEnumDeviceInfo(hDevInfoSet, nIndex, &devInfo))
  {
    portinfo = NULL;

    // Get the registry key which stores the ports settings...
    HKEY hDeviceKey = SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE);
    if (hDeviceKey) {
      tempstr.FillZero();
      DWORD dwSize = tempstr.SizeOf(); 
      DWORD dwType = 0;

      // Read name of port.  If formatted as "COMxx" then allocate a port slot...
  	  if ((RegQueryValueEx(hDeviceKey, _T("PortName"), NULL, &dwType, reinterpret_cast<LPBYTE>((TCHAR*)tempstr), &dwSize) == ERROR_SUCCESS) && (dwType == REG_SZ))
        if (_tcslen(tempstr) > 3)
          if ((_tcsnicmp(tempstr, _T("COM"), 3) == 0) && IsNumber(&(tempstr[3])))
            portinfo = AddPort(_ttoi(&(tempstr[3])));

      // Close the key now that we are finished with it...
      RegCloseKey(hDeviceKey);
    }

    // If a serial port, then try getting additional useful descriptive info...
    if (portinfo) {
      for (int i=0; SPDRPlist[i]>=0; i++) {
        tempstr.FillZero(); 
        DWORD dwSize = tempstr.SizeOf(); 
        DWORD dwType = 0;
        if (SetupDiGetDeviceRegistryProperty(hDevInfoSet, &devInfo, SPDRPlist[i], &dwType, reinterpret_cast<PBYTE>((TCHAR*)tempstr), dwSize, &dwSize) && ((dwType == REG_SZ) || (dwType == REG_MULTI_SZ)))
          switch (SPDRPlist[i]) {
            case SPDRP_MFG : portinfo->SetManufacturer(tempstr); break;
            case SPDRP_HARDWAREID : portinfo->SetHardwareID(tempstr); break;
            case SPDRP_DEVICEDESC : portinfo->SetDeviceDesc(tempstr); break;
            case SPDRP_FRIENDLYNAME : portinfo->SetFriendlyName(tempstr); break;
            case SPDRP_LOCATION_INFORMATION : portinfo->SetLocationInfo(tempstr); break;
            case SPDRP_PHYSICAL_DEVICE_OBJECT_NAME : portinfo->SetPhysLocation(tempstr); break;
          }
      }

      // Get COM port properties...
      HANDLE hPort = ::CreateFile(portinfo->GetPortDeviceName(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
      if (hPort != INVALID_HANDLE_VALUE) {
        COMMPROP cp;
        GetCommProperties(hPort, &cp);
        portinfo->SetCommProp(cp);
        TRACE ("Port %d:  CommProp: maxbaud=%08x  settablebaud=%08x\n",portinfo->GetPortNum(),cp.dwMaxBaud,cp.dwSettableBaud);
        CloseHandle(hPort);
      }
    }
    
    ++nIndex;
  }

  // Free up the "device information set" now that we are finished with it
  SetupDiDestroyDeviceInfoList(hDevInfoSet);

  // Return the success indicator
  return TRUE;
}