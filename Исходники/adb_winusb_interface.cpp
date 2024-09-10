ADBAPIHANDLE AdbWinUsbInterfaceObject::CreateHandle() {
  // Open USB device for this inteface Note that WinUsb API
  // requires the handle to be opened for overlapped I/O.
  usb_device_handle_ = CreateFile(interface_name().c_str(),
                                  GENERIC_READ | GENERIC_WRITE,
                                  FILE_SHARE_READ | FILE_SHARE_WRITE,
                                  NULL, OPEN_EXISTING,
                                  FILE_FLAG_OVERLAPPED, NULL);
  if (INVALID_HANDLE_VALUE == usb_device_handle_)
    return NULL;

  // Initialize WinUSB API for this interface
  if (!WinUsb_Initialize(usb_device_handle_, &winusb_handle_))
    return NULL;

  // Cache current interface number that will be used in
  // WinUsb_Xxx calls performed on this interface.
  if (!WinUsb_GetCurrentAlternateSetting(winusb_handle(), &interface_number_))
    return false;

  // Cache interface properties
  unsigned long bytes_written;

  // Cache USB device descriptor
  if (!WinUsb_GetDescriptor(winusb_handle(), USB_DEVICE_DESCRIPTOR_TYPE, 0, 0,
                            reinterpret_cast<PUCHAR>(&usb_device_descriptor_),
                            sizeof(usb_device_descriptor_), &bytes_written)) {
    return false;
  }

  // Cache USB configuration descriptor
  if (!WinUsb_GetDescriptor(winusb_handle(), USB_CONFIGURATION_DESCRIPTOR_TYPE,
                            0, 0,
                            reinterpret_cast<PUCHAR>(&usb_config_descriptor_),
                            sizeof(usb_config_descriptor_), &bytes_written)) {
    return false;
  }

  // Cache USB interface descriptor
  if (!WinUsb_QueryInterfaceSettings(winusb_handle(), interface_number(),
                                     &usb_interface_descriptor_)) {
    return false;
  }

  // Save indexes and IDs for bulk read / write endpoints. We will use them to
  // convert ADB_QUERY_BULK_WRITE_ENDPOINT_INDEX and
  // ADB_QUERY_BULK_READ_ENDPOINT_INDEX into actual endpoint indexes and IDs.
  for (UCHAR endpoint = 0; endpoint < usb_interface_descriptor_.bNumEndpoints;
       endpoint++) {
    // Get endpoint information
    WINUSB_PIPE_INFORMATION pipe_info;
    if (!WinUsb_QueryPipe(winusb_handle(), interface_number(), endpoint,
                          &pipe_info)) {
      return false;
    }

    if (UsbdPipeTypeBulk == pipe_info.PipeType) {
      // This is a bulk endpoint. Cache its index and ID.
      if (0 != (pipe_info.PipeId & USB_ENDPOINT_DIRECTION_MASK)) {
        // Use this endpoint as default bulk read endpoint
        ATLASSERT(0xFF == def_read_endpoint_);
        def_read_endpoint_ = endpoint;
        read_endpoint_id_ = pipe_info.PipeId;
      } else {
        // Use this endpoint as default bulk write endpoint
        ATLASSERT(0xFF == def_write_endpoint_);
        def_write_endpoint_ = endpoint;
        write_endpoint_id_ = pipe_info.PipeId;
      }
    }
  }

  return AdbInterfaceObject::CreateHandle();
}