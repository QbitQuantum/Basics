nsresult
sbWinFindDevicesByStorageDevNum(STORAGE_DEVICE_NUMBER* aStorageDevNum,
                                PRBool                 aMatchPartitionNumber,
                                const GUID*            aGUID,
                                nsTArray<DEVINST>&     aDevInstList)
{
  // Validate arguments.
  NS_ENSURE_ARG_POINTER(aStorageDevNum);
  NS_ENSURE_ARG_POINTER(aGUID);

  // Function variables.
  nsresult rv;

  // Get the interface device class info and set up for auto-disposal.
  HDEVINFO devInfo =
             SetupDiGetClassDevsW(aGUID,
                                  NULL,
                                  NULL,
                                  DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
  NS_ENSURE_TRUE(devInfo != INVALID_HANDLE_VALUE, NS_ERROR_FAILURE);
  sbAutoHDEVINFO autoDevInfo(devInfo);

  // Search for device instances with a matching storage device number.
  aDevInstList.Clear();
  DWORD devIndex = 0;
  while (1) {
    // Get the next device detail data and set it up for auto-disposal.
    PSP_DEVICE_INTERFACE_DETAIL_DATA devIfDetailData;
    SP_DEVINFO_DATA                  devInfoData;
    rv = sbWinGetDevDetail(&devIfDetailData,
                           &devInfoData,
                           devInfo,
                           aGUID,
                           devIndex++);
    if (rv == NS_ERROR_NOT_AVAILABLE)
      break;
    NS_ENSURE_SUCCESS(rv, rv);
    sbAutoMemPtr<SP_DEVICE_INTERFACE_DETAIL_DATA>
      autoDevIfDetailData(devIfDetailData);

    // Get the next storage device number.
    STORAGE_DEVICE_NUMBER storageDevNum;
    rv = sbWinGetStorageDevNum(devIfDetailData->DevicePath, &storageDevNum);
    if (NS_FAILED(rv))
      continue;

    // Skip device instance if it doesn't match the target storage device
    // number.
    if (storageDevNum.DeviceType != aStorageDevNum->DeviceType)
      continue;
    if (storageDevNum.DeviceNumber != aStorageDevNum->DeviceNumber)
      continue;
    if (aMatchPartitionNumber &&
        (storageDevNum.PartitionNumber != aStorageDevNum->PartitionNumber)) {
      continue;
    }

    // Add device instance to list.
    NS_ENSURE_TRUE(aDevInstList.AppendElement(devInfoData.DevInst),
                   NS_ERROR_OUT_OF_MEMORY);
  }

  return NS_OK;
}