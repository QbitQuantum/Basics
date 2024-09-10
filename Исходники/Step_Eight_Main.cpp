void CMainWnd::MenuSwitch()
{
	m_wndMenu.DestroyMenu();
	switch (blMenu)
	{
	case TRUE:
		m_wndMenu.LoadMenuW(IDR_MENU);
		break;
	case FALSE:
		m_wndMenu.LoadMenuW(IDR_MENU_RUS);
		break;
	}

	// Меняем переменную на противоположную, так как мы выбрали другое меню
	blMenu = !blMenu;

	// Устанавливаем меню во фрейм
	SetMenu(&m_wndMenu);
}