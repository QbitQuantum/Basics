void
WindowsGamepadService::ScanForRawInputDevices()
{
  if (!mHID) {
    return;
  }

  UINT numDevices;
  if (GetRawInputDeviceList(nullptr, &numDevices, sizeof(RAWINPUTDEVICELIST))
      == kRawInputError) {
    return;
  }
  nsTArray<RAWINPUTDEVICELIST> devices(numDevices);
  devices.SetLength(numDevices);
  if (GetRawInputDeviceList(devices.Elements(), &numDevices,
                            sizeof(RAWINPUTDEVICELIST)) == kRawInputError) {
    return;
  }

  for (unsigned i = 0; i < devices.Length(); i++) {
    if (devices[i].dwType == RIM_TYPEHID) {
      GetRawGamepad(devices[i].hDevice);
    }
  }
}