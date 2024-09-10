// Moves up one node in the device tree and returns its device info data along with an info set only
// including that device for further processing
// See https://msdn.microsoft.com/en-us/library/windows/hardware/ff549417(v=vs.85).aspx
static bool GetParentDevice(const DEVINST& child_device_instance, HDEVINFO* parent_device_info,
                            PSP_DEVINFO_DATA parent_device_data)
{
  ULONG status;
  ULONG problem_number;
  CONFIGRET result;

  // Check if that device instance has device node present
  result = CM_Get_DevNode_Status(&status, &problem_number, child_device_instance, 0);
  if (result != CR_SUCCESS)
  {
    return false;
  }

  DEVINST parent_device;

  // Get the device instance of the parent
  result = CM_Get_Parent(&parent_device, child_device_instance, 0);
  if (result != CR_SUCCESS)
  {
    return false;
  }

  std::vector<WCHAR> parent_device_id(MAX_DEVICE_ID_LEN);
  ;

  // Get the device id of the parent, required to open the device info
  result =
      CM_Get_Device_ID(parent_device, parent_device_id.data(), (ULONG)parent_device_id.size(), 0);
  if (result != CR_SUCCESS)
  {
    return false;
  }

  // Create a new empty device info set for the device info data
  (*parent_device_info) = SetupDiCreateDeviceInfoList(nullptr, nullptr);

  // Open the device info data of the parent and put it in the emtpy info set
  if (!SetupDiOpenDeviceInfo((*parent_device_info), parent_device_id.data(), nullptr, 0,
                             parent_device_data))
  {
    SetupDiDestroyDeviceInfoList(parent_device_info);
    return false;
  }

  return true;
}