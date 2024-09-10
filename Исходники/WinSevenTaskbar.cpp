void WinSevenTaskbar::init(void)
{
	m_winMsg = RegisterWindowMessageW(L"TaskbarButtonCreated");
	m_ptbl = NULL;
}