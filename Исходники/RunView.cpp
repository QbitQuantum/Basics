CRunView::~CRunView()
{
	if (m_hAccelTable != NULL)
	{
		DestroyAcceleratorTable(m_hAccelTable);
		m_hAccelTable = NULL;
	}
	
//	if (m_pBrowserApp != NULL)
//		m_pBrowserApp->Release();
}