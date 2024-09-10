void CPmtGrabber::OnTsPacket(byte* tsPacket)
{
	if (m_pCallback==NULL) return;
  int pid=((tsPacket[1] & 0x1F) <<8)+tsPacket[2];
  if (pid != GetPid()) return;
	CEnterCriticalSection enter(m_section);
  CSectionDecoder::OnTsPacket(tsPacket);
}