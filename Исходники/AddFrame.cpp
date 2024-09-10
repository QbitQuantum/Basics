CDuiAddFrame::CDuiAddFrame()
{
	if(m_pImageList == NULL)
	{
		HRESULT hResult = SHGetImageList(SHIL_JUMBO, IID_IImageList, (void**)&m_pImageList);
		if(hResult != S_OK){
			m_pImageList = NULL;
		}
	}
	m_ImagePath = CPaintManagerUI::GetInstancePath() + L"Icon\\tmp.png";
}