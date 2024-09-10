uint32_t
MetroWidget::GetMaxTouchPoints() const
{
  ComPtr<IPointerDeviceStatics> deviceStatics;

  HRESULT hr = GetActivationFactory(
    HStringReference(RuntimeClass_Windows_Devices_Input_PointerDevice).Get(),
    deviceStatics.GetAddressOf());

  if (FAILED(hr)) {
    return 0;
  }

  ComPtr< IVectorView<PointerDevice*> > deviceList;
  hr = deviceStatics->GetPointerDevices(&deviceList);

  if (FAILED(hr)) {
    return 0;
  }

  uint32_t deviceNum = 0;
  deviceList->get_Size(&deviceNum);

  uint32_t maxTouchPoints = 0;
  for (uint32_t index = 0; index < deviceNum; ++index) {
    ComPtr<IPointerDevice> device;
    PointerDeviceType deviceType;

    if (FAILED(deviceList->GetAt(index, device.GetAddressOf()))) {
      continue;
    }

    if (FAILED(device->get_PointerDeviceType(&deviceType)))  {
      continue;
    }

    if (deviceType == PointerDeviceType_Touch) {
      uint32_t deviceMaxTouchPoints = 0;
      device->get_MaxContacts(&deviceMaxTouchPoints);
      maxTouchPoints = std::max(maxTouchPoints, deviceMaxTouchPoints);
    }
  }

  return maxTouchPoints;
}