//--------------------------------------------------------------------------
void WindowsVideoDevice::InitModes() noexcept
{
	VeInt32 pass;
	DWORD i, j, count;
	DISPLAY_DEVICEA device;

	device.cb = sizeof(device);

	for (pass = 0; pass < 2; ++pass)
	{
		for (i = 0;; ++i)
		{
			CHAR DeviceName[32];

			if (!EnumDisplayDevicesA(nullptr, i, &device, 0))
			{
				break;
			}
			if (!(device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
			{
				continue;
			}
			if (pass == 0)
			{
				if (!(device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
				{
					continue;
				}
			}
			else
			{
				if (device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
				{
					continue;
				}
			}
			VeMemoryCopy(DeviceName, device.DeviceName, sizeof(DeviceName));

			VeDebugOutputCore("Device: %s\n", DeviceName);

			count = 0;
			for (j = 0;; ++j)
			{
				if (!EnumDisplayDevicesA(DeviceName, j, &device, 0))
				{
					break;
				}
				if (!(device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
				{
					continue;
				}
				if (pass == 0)
				{
					if (!(device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
					{
						continue;
					}
				}
				else {
					if (device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
					{
						continue;
					}
				}
				count += AddDisplay(device.DeviceName);
			}
			if (count == 0)
			{
				AddDisplay(DeviceName);
			}
		}
	}

	VE_ASSERT(m_kDisplayList.size());
}