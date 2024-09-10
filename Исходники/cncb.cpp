UCHAR CNCB::SendNoAck(UCHAR wSessionNumber,LPSTR lpPacket, UINT wLength)
{ 
	ClearNCB();
	if (wLength > 0xffff) RaiseException(EXCEPTION_ACCESS_VIOLATION,0,0,NULL);
	m_NCB.ncb_lana_num = m_iLanaNum;
	m_NCB.ncb_command = NCBSENDNA;
	m_NCB.ncb_lsn = wSessionNumber;
	m_NCB.ncb_length = wLength;
	m_NCB.ncb_buffer = (unsigned char *)lpPacket;
	return (fp?((*fp)(&m_NCB)):(0x3f));
	return 0;
};