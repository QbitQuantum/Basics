bool 
SoWinP::InitRawDevices(void) 
{
  PRAWINPUTDEVICELIST rawInputDeviceList;
  PRAWINPUTDEVICE rawInputDevices;
  int usagePage1Usage8Devices;
  
  // Find the Raw Devices
  UINT nDevices;
  // Get Number of devices attached
  if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0) { 
    return FALSE;
  }
  // Create list large enough to hold all RAWINPUTDEVICE structs
  rawInputDeviceList = (PRAWINPUTDEVICELIST) malloc(sizeof(RAWINPUTDEVICELIST) * nDevices);
  if (rawInputDeviceList == NULL) {
    return FALSE;
  }
  // Now get the data on the attached devices
  if (GetRawInputDeviceList(rawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST)) == -1) {
    return FALSE;
  }
  
  rawInputDevices = (PRAWINPUTDEVICE) malloc(nDevices * sizeof(RAWINPUTDEVICE));
  usagePage1Usage8Devices = 0;
  
  // Look through device list for RIM_TYPEHID devices with UsagePage == 1, Usage == 8
  for(UINT i=0; i<nDevices; i++) {
    if (rawInputDeviceList[i].dwType == RIM_TYPEHID) {
      UINT nchars = 300;
      TCHAR deviceName[300];      
      RID_DEVICE_INFO dinfo;
      UINT sizeofdinfo = sizeof(dinfo);
      dinfo.cbSize = sizeofdinfo;
      if (GetRawInputDeviceInfo(rawInputDeviceList[i].hDevice,
                                RIDI_DEVICEINFO, &dinfo, &sizeofdinfo ) >= 0) {
        if (dinfo.dwType == RIM_TYPEHID) {
          RID_DEVICE_INFO_HID *phidInfo = &dinfo.hid;          
          // Add this one to the list of interesting devices?
          // Actually only have to do this once to get input from all
          // usage 1, usagePage 8 devices This just keeps out the
          // other usages.  You might want to put up a list for users
          // to select amongst the different devices.  In particular,
          // to assign separate functionality to the different
          // devices.
          if (phidInfo->usUsagePage == 1 && phidInfo->usUsage == 8) {
            rawInputDevices[usagePage1Usage8Devices].usUsagePage = phidInfo->usUsagePage;
            rawInputDevices[usagePage1Usage8Devices].usUsage = phidInfo->usUsage;
            rawInputDevices[usagePage1Usage8Devices].dwFlags = 0;
            rawInputDevices[usagePage1Usage8Devices].hwndTarget = mainWidget;//NULL;
            usagePage1Usage8Devices++;
          }
        }
      }
    }
  }
  
  // Register for input from the devices in the list
  if (RegisterRawInputDevices(rawInputDevices, usagePage1Usage8Devices, 
                              sizeof(RAWINPUTDEVICE)) == FALSE) {
    return FALSE;
  }
  
  return TRUE;
}