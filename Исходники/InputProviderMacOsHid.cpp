void CInputProviderMacOsHid::OnDeviceMatched(IOReturn result, void* sender, IOHIDDeviceRef device)
{
	m_devices.push_back(DEVICE_INFO());
	auto& deviceInfo = *m_devices.rbegin();
	deviceInfo.provider = this;
	deviceInfo.device = device;
	deviceInfo.deviceId = GetDeviceID(device);

	auto InputReportCallbackStub = GetCallback(device);
	if(InputReportCallbackStub)
	{
		uint32_t max_input_report_size = GetIntProperty(device, CFSTR(kIOHIDMaxInputReportSizeKey));
		uint8_t* report_buffer = static_cast<uint8_t*>(calloc(max_input_report_size, sizeof(uint8_t)));
		IOHIDDeviceRegisterInputReportCallback(device, report_buffer, max_input_report_size, InputReportCallbackStub, &deviceInfo);
	}
	else
	{
		if(OnInput)
		{
			SetInitialBindValues(device);
		}
		IOHIDDeviceRegisterInputValueCallback(device, &InputValueCallbackStub, &deviceInfo);
	}
}