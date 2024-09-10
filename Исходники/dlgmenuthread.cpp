CMenu* CDlgMenuThread::CreateMenu()
{
		CMenu* menu = new CMenu();
		menu->CreatePopupMenu();
		m_arrayMenuData.Add(menu);
		return menu;
}