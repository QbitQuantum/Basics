bool silvia_pcsc_card::transmit(bytestring APDU, bytestring& data_sw)
{
	if (!connected) return false;
	
	data_sw.resize(65536);
	DWORD out_len = 65536;
	SCARD_IO_REQUEST recv_req;
		
	LONG rv = SCardTransmit(
		card_handle, 
		protocol == SCARD_PROTOCOL_T0 ? SCARD_PCI_T0 : SCARD_PCI_T1, 
		APDU.byte_str(), 
		APDU.size(), 
		&recv_req,
		data_sw.byte_str(),
		&out_len);
		
	if (rv != SCARD_S_SUCCESS)
	{
		return false;
	}
	
	data_sw.resize(out_len);
	
	if (data_sw.size() < 2)
	{
		return false;
	}
	
	return true;
}