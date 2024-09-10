HANDLE
OpenUsbDevice( 
    _In_ LPGUID  pGuid, 
    _In_ PSTR    outNameBuf
    )
/*++
Routine Description:

   Do the required PnP things in order to find
   the next available proper device in the system at this time.

Arguments:

    pGuid:      ptr to GUID registered by the driver itself
    outNameBuf: the generated name for this device

Return Value:

    return HANDLE if the open and initialization was successful,
        else INVLAID_HANDLE_VALUE.
--*/
{
   ULONG NumberDevices;
   HANDLE hOut = INVALID_HANDLE_VALUE;
   HDEVINFO                 hardwareDeviceInfo;
   SP_DEVICE_INTERFACE_DATA deviceInfoData;
   ULONG                    i;
   BOOLEAN                  done;
   PUSB_DEVICE_DESCRIPTOR   usbDeviceInst;
   PUSB_DEVICE_DESCRIPTOR  *UsbDevices = &usbDeviceInst;
   PUSB_DEVICE_DESCRIPTOR   tempDevDesc;

   *UsbDevices = NULL;
   tempDevDesc = NULL;
   NumberDevices = 0;

   //
   // Open a handle to the plug and play dev node.
   // SetupDiGetClassDevs() returns a device information set that contains 
   // info on all installed devices of a specified class.
   //
   hardwareDeviceInfo = 
       SetupDiGetClassDevs ( pGuid,
                             NULL, // Define no enumerator (global)
                             NULL, // Define no
                             (DIGCF_PRESENT |           // Only Devices present
                               DIGCF_DEVICEINTERFACE)); // Function class devices.

   if (hardwareDeviceInfo == INVALID_HANDLE_VALUE) {
       return INVALID_HANDLE_VALUE ;
   }
   //
   // Take a wild guess at the number of devices we have;
   // Be prepared to realloc and retry if there are more than we guessed
   //
   NumberDevices = 4;
   done = FALSE;
   deviceInfoData.cbSize = sizeof (SP_DEVICE_INTERFACE_DATA);

   i=0;
   while (!done) {
      NumberDevices *= 2;

      if (*UsbDevices) {
          tempDevDesc = (PUSB_DEVICE_DESCRIPTOR)
             realloc (*UsbDevices, (NumberDevices * sizeof (USB_DEVICE_DESCRIPTOR)));
          if(tempDevDesc) {
              *UsbDevices = tempDevDesc;
              tempDevDesc = NULL;
          }
          else {
              free(*UsbDevices);
              *UsbDevices = NULL;
          }
      } else {
         *UsbDevices = (PUSB_DEVICE_DESCRIPTOR)calloc (NumberDevices, sizeof (USB_DEVICE_DESCRIPTOR));
      }

      if (NULL == *UsbDevices) {

         // SetupDiDestroyDeviceInfoList destroys a device information set
         // and frees all associated memory.

         SetupDiDestroyDeviceInfoList (hardwareDeviceInfo);
         return INVALID_HANDLE_VALUE;
      }

      for (; i < NumberDevices; i++) {
          // SetupDiEnumDeviceInterfaces() returns information about device 
          // interfaces exposed by one or more devices. Each call returns 
          // information about one interface; the routine can be called 
          // repeatedly to get information about several interfaces exposed 
          // by one or more devices.

         if (SetupDiEnumDeviceInterfaces (hardwareDeviceInfo,
                                         0, // We don't care about specific PDOs
                                         pGuid,
                                         i,
                                         &deviceInfoData)) {

            hOut = OpenOneDevice (hardwareDeviceInfo, &deviceInfoData, outNameBuf);
                        if ( hOut != INVALID_HANDLE_VALUE ) {
               done = TRUE;
               break;
                        }
         } else {
            if (ERROR_NO_MORE_ITEMS == GetLastError()) {
               done = TRUE;
               break;
            }
         }
      }
   }

   // SetupDiDestroyDeviceInfoList() destroys a device information set
   // and frees all associated memory.

   SetupDiDestroyDeviceInfoList (hardwareDeviceInfo);
   free ( *UsbDevices );
   return hOut;
}