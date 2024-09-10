CTimeEv::~CTimeEv()
{
	if(m_oAVIR.IsOpen())
		m_oAVIR.Close();
	if(m_hdd)
		DrawDibClose(m_hdd);
	if(m_pDIBFrame)
		delete [] m_pDIBFrame;
}