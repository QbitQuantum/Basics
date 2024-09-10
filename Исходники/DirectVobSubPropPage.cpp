void CDVSMainPPage::AllocLangs(int nLangs)
{
	m_ppLangs = (WCHAR**)CoTaskMemRealloc(m_ppLangs, sizeof(WCHAR*)*nLangs);
	m_nLangs = nLangs;
}