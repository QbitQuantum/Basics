IOKitDevice::IOKitDevice(const IOKitDevice& device)
:
   usBusNumber(device.usBusNumber),
	usAddress(device.usAddress),
   usVid(device.usVid),
   usPid(device.usPid),
	usConfigurationNum(device.usConfigurationNum),
   ulSerialNumber(device.ulSerialNumber),
	ulLocation(device.ulLocation),
   hSavedService(NULL)
{

   if (device.hSavedService)
   {
      IOObjectRetain(device.hSavedService);
      hSavedService = device.hSavedService;
   }

   STRNCPY(szProductDescription, device.szProductDescription, sizeof(szProductDescription));
   memcpy(szSerialString, device.szSerialString, sizeof(szSerialString));
   memcpy(&stDeviceDescriptor, &(device.stDeviceDescriptor), sizeof(device.stDeviceDescriptor));
   memcpy(szSystemPath, device.szSystemPath, sizeof(device.szSystemPath));

   return;
}