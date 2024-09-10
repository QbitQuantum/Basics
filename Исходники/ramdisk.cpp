static
void
create_ramdisk_device(std::string full_inf_file_path,
                      std::string hardware_id) {
  GUID class_guid;
  WCHAR class_name_w[MAX_CLASS_NAME_LEN];
  auto success =
    SetupDiGetINFClassW(w32util::widen(full_inf_file_path).c_str(),
                        &class_guid,
                        class_name_w, safe::numelementsf(class_name_w),
                        nullptr);
  if (!success) w32util::throw_windows_error();

  /* don't install device if it already exists */
  auto create_device = true;
  {
    HDEVINFO device_info_set =
      SetupDiGetClassDevsEx(&class_guid, nullptr, nullptr, 0,
			    nullptr, nullptr, nullptr);
    if (device_info_set == INVALID_HANDLE_VALUE) {
      w32util::throw_setupapi_error();
    }

    SP_DEVINFO_DATA device_info_data;
    zero_object(device_info_data);
    device_info_data.cbSize = sizeof(device_info_data);
    for (DWORD idx = 0;
	 create_device &&
	 SetupDiEnumDeviceInfo(device_info_set, idx, &device_info_data);
	 ++idx) {
      /* first get hardware id reg key for this device info */
      CHAR buffer[1024];
      BOOL success_prop =
	SetupDiGetDeviceRegistryPropertyA(device_info_set,
					  &device_info_data,
					  SPDRP_HARDWAREID,
					  nullptr,
					  (PBYTE) buffer,
					  sizeof(buffer),
					  nullptr);
      if (!success_prop) w32util::throw_setupapi_error();

      PCHAR bp = buffer;
      while(*bp) {
	if (!strcmp(bp, hardware_id.c_str())) {
	  create_device = false;
	  break;
	}
	bp += strlen(bp) + 1;
      }
    }
  }

  // device already exists, no need to create it
  if (!create_device) return;

  auto device_info_set =
    SetupDiCreateDeviceInfoList(&class_guid, NULL);
  if (device_info_set == INVALID_HANDLE_VALUE) w32util::throw_setupapi_error();
  auto _destroy_device_info_set =
    safe::create_deferred(SetupDiDestroyDeviceInfoList, device_info_set);

  SP_DEVINFO_DATA device_info_data;
  zero_object(device_info_data);
  device_info_data.cbSize = sizeof(device_info_data);
  auto success_create_device_info =
    SetupDiCreateDeviceInfoW(device_info_set, class_name_w,
                             &class_guid, nullptr, 0,
                             DICD_GENERATE_ID, &device_info_data);
  if (!success_create_device_info) w32util::throw_setupapi_error();

  // TODO: runtime stack array is a GCC extension
  auto reg_hardware_id_len = hardware_id.size() + 2;
  auto reg_hardware_id_size = reg_hardware_id_len * sizeof(WCHAR);
  auto reg_hardware_id = std::unique_ptr<WCHAR[]>(new WCHAR[reg_hardware_id_len]);
  memset(reg_hardware_id.get(), 0, reg_hardware_id_size);
  memcpy(reg_hardware_id.get(), w32util::widen(hardware_id).data(),
         hardware_id.size() * sizeof(WCHAR));

  auto success_set_hardware_id =
    SetupDiSetDeviceRegistryPropertyW(device_info_set,
                                      &device_info_data,
                                      SPDRP_HARDWAREID,
                                      (BYTE *) reg_hardware_id.get(),
                                      reg_hardware_id_size);
  if (!success_set_hardware_id) w32util::throw_setupapi_error();

  auto success_class_installer =
    SetupDiCallClassInstaller(DIF_REGISTERDEVICE, device_info_set,
                              &device_info_data);
  if (!success_class_installer) w32util::throw_setupapi_error();

  create_ramdisk_hardware_keys(device_info_set, &device_info_data);
}