IPCCommandResult CWII_IPC_HLE_Device_usb_oh0_46d_a03::Open(u32 CommandAddress, u32 Mode)
{
	Memory::Write_U32(GetDeviceID(), CommandAddress + 4);
	m_Active = true;
	return GetDefaultReply();
}