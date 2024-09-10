bool ReenumerateDeviceNode(PSP_DEVINFO_DATA pDevInfoData)
{
  return CM_Reenumerate_DevNode(pDevInfoData->DevInst, 0) == CR_SUCCESS;
}