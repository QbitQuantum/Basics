bool edna_emulator::transceive_control(SCARDHANDLE reader, const bytestring& cmd, bytestring& rdata)
{
	DWORD pcsc_rv;
	DWORD rlen;
	
	rdata.resize(512);
	if ((pcsc_rv = SCardControl(reader, IOCTL_CCID_ESCAPE_DIRECT, cmd.const_byte_str(), cmd.size(), rdata.byte_str(), 512, &rlen)) != SCARD_S_SUCCESS)
	{
		ERROR_MSG("Failed to exchange control command (0x%08X)", pcsc_rv);
		
		SCardDisconnect(reader, SCARD_UNPOWER_CARD);
		SCardReleaseContext(pcsc_context);
		
		return false;
	}
	
	rdata.resize(rlen);
	
	return true;
}