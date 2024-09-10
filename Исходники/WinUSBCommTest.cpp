BOOL SendDatatoDefaultEndpoint(WINUSB_INTERFACE_HANDLE hDeviceHandle, BYTE byWinUSBCommControl, BYTE *pbyData = NULL, WORD wNumBytesCount = 0)
{
  if (hDeviceHandle==INVALID_HANDLE_VALUE)
  {
    return FALSE;
  }

  BOOL bResult = TRUE;
  WINUSB_SETUP_PACKET SetupPacket;
  ZeroMemory(&SetupPacket, sizeof(WINUSB_SETUP_PACKET));
  ULONG cbSent = 0;

  //Create the setup packet
  SetupPacket.RequestType = (BMREQUEST_HOST_TO_DEVICE << 7) | (BMREQUEST_VENDOR << 5) | BMREQUEST_TO_INTERFACE;
  SetupPacket.Request = byWinUSBCommControl;
  SetupPacket.Value = 0;
  SetupPacket.Index = 0; // specify WinUSBComm interface
  SetupPacket.Length = wNumBytesCount;

  bResult = WinUsb_ControlTransfer(hDeviceHandle, SetupPacket, pbyData, wNumBytesCount, &cbSent, 0);
  if(!bResult)
  {
    goto done;
  }

  PTRACE("Data sent: %d \nActual data transferred: %d.\n", wNumBytesCount, cbSent);


done:
  return bResult;

}