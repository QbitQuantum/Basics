static void SendControlTransfer(WINUSB_SETUP_PACKET& Packet, BYTE* pBuf)
{
	assert(s_hWinUSB);
	DWORD dwBytesTransferred;
	if(!WinUsb_ControlTransfer(s_hWinUSB, Packet, pBuf, Packet.Length, &dwBytesTransferred, nullptr))
	{
		wprintf_s(L"WinUsb_ControlTransfer: %s\n", _com_error(GetLastError()).ErrorMessage());		
		return;
	}
}