static bool IsDeviceHotplug(DEVINST hDevInst)
{
	bool Result = false;
	dev_info Info;
	if (Info.Create(hDevInst))
	{
		SP_DEVINFO_DATA DeviceInfoData = {sizeof(DeviceInfoData)};
		if(Info.OpenDeviceInfo(DeviceInfoData))
		{
			DWORD Capabilities = 0;
			if(Info.GetDeviceRegistryProperty(DeviceInfoData, SPDRP_CAPABILITIES, nullptr, reinterpret_cast<PBYTE>(&Capabilities), sizeof(Capabilities), nullptr))
			{
				DWORD Status = 0, Problem = 0;
				if (CM_Get_DevNode_Status(&Status, &Problem, hDevInst, 0) == CR_SUCCESS)
				{
					if ((Problem != CM_PROB_DEVICE_NOT_THERE) &&
							(Problem != CM_PROB_HELD_FOR_EJECT) && //возможно, надо провер¤ть на наличие проблем вообще
							(Problem != CM_PROB_DISABLED) &&
							(Capabilities & CM_DEVCAP_REMOVABLE) &&
							(!(Capabilities & CM_DEVCAP_SURPRISEREMOVALOK) || IsChildDeviceHotplug(hDevInst)) &&
							!(Capabilities & CM_DEVCAP_DOCKDEVICE))
						Result = true;
				}
			}
		}
	}
	return Result;
}