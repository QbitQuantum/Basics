void build_volumes_v2(t_volumes & volumes)
{
	HDEVINFO di = SetupDiGetClassDevs(&GUID_DEVINTERFACE_DISK, NULL, NULL, DIGCF_PRESENT|DIGCF_DEVICEINTERFACE);

	if (di != INVALID_HANDLE_VALUE)
	{
		SP_DEVINFO_DATA did;
		memset(&did, 0, sizeof(did));
		did.cbSize = sizeof(did);

		DWORD i;
		for (i=0; SetupDiEnumDeviceInfo(di, i, &did); i++)
		{
			if (did.ClassGuid == GUID_DEVCLASS_DISKDRIVE)
			{
				ULONG DevLen = 0, DevDiskLen=0;
				pfc::array_t<WCHAR> Dev, DevDisk, DevRoot;
				DEVINST pParent = NULL, ppParent = NULL;
				CM_Get_Parent_Ex(&pParent, did.DevInst, NULL, NULL);
				CM_Get_Parent_Ex(&ppParent, pParent, NULL, NULL);
				CM_Get_Device_ID_Size(&DevLen, pParent, NULL);
				CM_Get_Device_ID_Size(&DevDiskLen, did.DevInst, NULL);
				Dev.set_size(DevLen+1);
				Dev.fill_null();
				DevDisk.set_size(DevDiskLen+1);
				DevDisk.fill_null();
				CM_Get_Device_ID(pParent, Dev.get_ptr(), Dev.get_size(), NULL);
				CM_Get_Device_ID(did.DevInst, DevDisk.get_ptr(), DevDisk.get_size(), NULL);

				{
					ULONG len = 0;
					CM_Get_Device_ID_Size(&len, ppParent, NULL);
					DevRoot.set_size(len+1);
					DevRoot.fill_null();
					CM_Get_Device_ID(ppParent, DevRoot.get_ptr(), len, NULL);
				}
				bool b_shuffle;
				t_ipod_model model;
				if (g_check_devid_is_ipod(Dev.get_ptr(), model, b_shuffle))
				{
					pfc::array_t<WCHAR> DriverSymbolicPath;
					if (!wcsncmp(Dev.get_ptr(), DevRoot.get_ptr(), 7))
					{
						ULONG len=0;

						CM_Get_Device_Interface_List_Size(&len, (LPGUID)&GUID_DEVINTERFACE_USBAPPL_DEVICE, DevRoot.get_ptr(), CM_GET_DEVICE_INTERFACE_LIST_PRESENT);

						DriverSymbolicPath.set_size(len+1);
						DriverSymbolicPath.fill_null();
						CM_Get_Device_Interface_List((LPGUID)&GUID_DEVINTERFACE_USBAPPL_DEVICE, DevRoot.get_ptr(), DriverSymbolicPath.get_ptr(), len, CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
						//console::formatter() << pfc::stringcvt::string_utf8_from_os(buff.get_ptr());
					}
					else
					{
						DriverSymbolicPath.set_size(1);
						DriverSymbolicPath.fill_null();
					}

					{
						ULONG DevRemovalListSize = NULL, DevBusListSize = NULL;
						pfc::array_t<WCHAR> DevRemovalList, DevBusList;
						CM_Get_Device_ID_List_Size_Ex(&DevRemovalListSize, DevDisk.get_ptr(), CM_GETIDLIST_FILTER_REMOVALRELATIONS, NULL);
						CM_Get_Device_ID_List_Size_Ex(&DevBusListSize, DevDisk.get_ptr(), CM_GETIDLIST_FILTER_BUSRELATIONS, NULL);
						DevRemovalList.set_size(DevRemovalListSize);
						DevBusList.set_size(DevBusListSize);
						CM_Get_Device_ID_List_Ex(DevDisk.get_ptr(), DevRemovalList.get_ptr(), DevRemovalListSize, CM_GETIDLIST_FILTER_REMOVALRELATIONS, NULL);
						CM_Get_Device_ID_List_Ex(DevDisk.get_ptr(), DevBusList.get_ptr(), DevBusListSize, CM_GETIDLIST_FILTER_BUSRELATIONS, NULL);
						WCHAR * ptr = DevRemovalList.get_ptr(), *pvolume=NULL;
						{
							t_size ptrlen= NULL;
							while (ptr && (ptrlen = wcslen(ptr)))
							{
								if (!wcsicmp_partial(ptr, L"STORAGE\\"))
								{
									pvolume = ptr;
									break;
								}
								ptr+=ptrlen;
								ptr++;
							}
						}

						if (!pvolume)
						{
							ptr = DevBusList.get_ptr();
							t_size ptrlen= NULL;
							while (ptr && (ptrlen = wcslen(ptr)))
							{
								if (!wcsicmp_partial(ptr, L"STORAGE\\"))
								{
									pvolume = ptr;
									break;
								}
								ptr+=ptrlen;
								ptr++;
							}
						}

						if (pvolume)
						{
							SP_DEVINFO_DATA pdid;
							memset(&pdid, 0, sizeof(pdid));
							pdid.cbSize = sizeof(pdid);
							HDEVINFO pdi = SetupDiGetClassDevs(&GUID_DEVINTERFACE_VOLUME, NULL, NULL, DIGCF_PRESENT|DIGCF_DEVICEINTERFACE);;
							SetupDiOpenDeviceInfo(pdi, pvolume, NULL, NULL, &pdid);
							{
								{
									DWORD j;
									SP_DEVICE_INTERFACE_DATA dia;
									memset(&dia, 0, sizeof(dia));
									dia.cbSize = sizeof(dia);
									for (j=0; SetupDiEnumDeviceInterfaces(pdi, &pdid, &GUID_DEVINTERFACE_VOLUME, j, &dia); j++)
									{
										DWORD required_size = 0;

										pfc::array_t<t_uint8> data;

										SetupDiGetDeviceInterfaceDetail(pdi, &dia, NULL, NULL, &required_size, &pdid);
										data.set_size(required_size);
										data.fill_null();
										if (required_size >= sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA))
										{
											SP_DEVICE_INTERFACE_DETAIL_DATA * didd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)data.get_ptr();
											didd->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
											if (SetupDiGetDeviceInterfaceDetail(pdi, &dia, didd, required_size, NULL, &pdid))
											{

												pfc::array_t<WCHAR> path;
												t_size len = wcslen(didd->DevicePath);
												path.append_fromptr(didd->DevicePath, len);
												path.grow_size (len + sizeof(WCHAR)*2);
												path[len] = '\\';
												path[len+1] = 0;

												WCHAR volumename[129];
												memset(&volumename, 0, sizeof(volumename));
												if (GetVolumeNameForVolumeMountPoint(path.get_ptr(), volumename, 128))
												{
													volumes.add_item(t_volume(volumename, Dev.get_ptr(), model, b_shuffle, pParent, DriverSymbolicPath.get_ptr()));
												}
											}
										}
									}
								}
							}
							SetupDiDestroyDeviceInfoList(pdi);
						}
					}

				}
			}
		}

		SetupDiDestroyDeviceInfoList(di);
	}
}