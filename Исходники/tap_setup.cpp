bool remove(const std::wstring& hardware_id, bool& reboot_required)
{
	bool result = false;

	HDEVINFO devices = SetupDiGetClassDevsEx(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT, NULL, NULL, NULL);

	if (devices != INVALID_HANDLE_VALUE)
	{
		std::wcerr << "Got device information set." << std::endl;

		SP_DEVINFO_LIST_DETAIL_DATA device_info_list_detail;
		memset(&device_info_list_detail, 0x00, sizeof(device_info_list_detail));
		device_info_list_detail.cbSize = sizeof(device_info_list_detail);

		if (SetupDiGetDeviceInfoListDetail(devices, &device_info_list_detail))
		{
			std::wcerr << "Got device information list details." << std::endl;

			SP_DEVINFO_DATA device_info;
			device_info.cbSize = sizeof(device_info);

			for (DWORD index = 0; SetupDiEnumDeviceInfo(devices, index, &device_info); ++index)
			{
				TCHAR device_id[MAX_DEVICE_ID_LEN];

				if (CM_Get_Device_ID_Ex(device_info.DevInst, device_id, MAX_DEVICE_ID_LEN, 0, device_info_list_detail.RemoteMachineHandle) == CR_SUCCESS)
				{
					std::list<std::wstring> device_hardware_id_list;

					if (getDeviceProperty(devices, device_info, SPDRP_HARDWAREID, device_hardware_id_list))
					{
						bool match = false;

						for (std::list<std::wstring>::const_iterator device_hardware_id = device_hardware_id_list.begin(); device_hardware_id != device_hardware_id_list.end(); ++device_hardware_id)
						{
							if (*device_hardware_id == hardware_id)
							{
								match = true;

								break;
							}
						}

						if (match)
						{
							std::wstring friendly_name;

							if (getDeviceProperty(devices, device_info, SPDRP_FRIENDLYNAME, friendly_name) && (friendly_name.length() > 0))
							{
								std::wcerr << "Removing device: " << friendly_name << " (" << device_id << ")" << std::endl;
							} else
							{
								std::wcerr << "Removing device: " << device_id << std::endl;
							}

							SP_REMOVEDEVICE_PARAMS remove_device_params;
							remove_device_params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
							remove_device_params.ClassInstallHeader.InstallFunction = DIF_REMOVE;
							remove_device_params.Scope = DI_REMOVEDEVICE_GLOBAL;
							remove_device_params.HwProfile = 0;

							result = true;

							if (!SetupDiSetClassInstallParams(devices, &device_info, &remove_device_params.ClassInstallHeader, sizeof(remove_device_params)) || 
									!SetupDiCallClassInstaller(DIF_REMOVE, devices, &device_info))
							{
								std::wcerr << "Failed to set the class installer." << std::endl;

								result = false;
							}

							if (result)
							{
								reboot_required = false;

								SP_DEVINSTALL_PARAMS device_params;

								if (SetupDiGetDeviceInstallParams(devices, &device_info, &device_params))
								{
									if (device_params.Flags & (DI_NEEDRESTART | DI_NEEDREBOOT))
									{
										reboot_required = true;
									}
								}
							}
						}
					}
				}
			}
		}

		SetupDiDestroyDeviceInfoList(devices);
	}

	return result;
}