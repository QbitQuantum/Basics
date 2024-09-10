CSSD::CSSD(SSD ssd, CRYPTTYPE crypt, BOOL inSysInfo) : m_Crypt(crypt), m_ssd(ssd)
{ 
	m_ssd.m_szProduct = GetProductInfo(); 
	m_inSysInfo = inSysInfo;
	if (m_inSysInfo) {
		CSysInfo si;
		m_ssd.m_szSysInfo = si.GetSysInfo();
	}
}