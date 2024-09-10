CAdInventoryBox::CAdInventoryBox(CBGame* inGame):CBObject(inGame)
{
	SetRectEmpty(&m_ItemsArea);
	m_ScrollOffset = 0;
	m_Spacing = 0;
	m_ItemWidth = m_ItemHeight = 50;
	m_ScrollBy = 1;

	m_Window = NULL;
	m_CloseButton = NULL;

	m_HideSelected = false;

	m_Visible = false;
	m_Exclusive = false;
}