std::vector<DeviceInfo> InputManagerImpl::EnumDevices()
{
	std::vector<DeviceInfo> result;

	auto hr = m_Dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, &InputManagerImpl::EnumDeviceCallback, &result, DIEDFL_ALLDEVICES);
	if(FAILED(hr))
		return result;

	std::vector<GUID> failedDevices;

	for(auto& devInfo : result)
	{
		CComPtr<IDirectInputDevice8> comDevice;
		hr = m_Dinput->CreateDevice(devInfo.ID, &comDevice, nullptr);
		if(FAILED(hr))
		{
			failedDevices.push_back(devInfo.ID);
			continue;
		}

		DIDEVCAPS caps;
		caps.dwSize = sizeof(caps);
		hr = comDevice->GetCapabilities(&caps);
		if(FAILED(hr))
		{
			failedDevices.push_back(devInfo.ID);
			continue;
		}

		devInfo.NumButtons = caps.dwButtons;
		devInfo.NumPOVs = caps.dwPOVs;

		hr = comDevice->EnumObjects(&InputManagerImpl::EnumDeviceObjectsCallback, &devInfo, DIDFT_ABSAXIS);
		if(FAILED(hr))		
		{
			failedDevices.push_back(devInfo.ID);
			continue;
		}
	}
	//remove any devices we couldn't get info for
	result.erase(RE::remove_if(result, [&](const DeviceInfo& _devInfo) {
		return RE::find(failedDevices, _devInfo.ID) != end(failedDevices);
	}), end(result));
	
	//get rid of any that have no usable axis or buttons. For example razer hydra reports 2 sticks. one has no buttons, axis
	//	or anything else. get rid of that one. If you cant use it for anything, no reason to report it.
	auto remIter = RE::remove_if(result, [](const DeviceInfo& _devInfo) -> bool {
		return _devInfo.NumButtons == 0 && _devInfo.NumPOVs == 0 && _devInfo.NumSliders == 0 && !_devInfo.XAxis &&
			!_devInfo.XRotation && !_devInfo.YAxis && !_devInfo.YRotation && !_devInfo.ZAxis && !_devInfo.ZRotation;
	});
	result.erase(remIter, end(result));

	return result;
}