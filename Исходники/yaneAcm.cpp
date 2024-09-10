LRESULT CAcm::Close(void) {
	if (m_bOpen) {
		m_bOpen = false;
		acmStreamUnprepareHeader(m_hAcm,&m_acmheader,NULL);
		return acmStreamClose(m_hAcm,NULL);
	}
	return 0;
}