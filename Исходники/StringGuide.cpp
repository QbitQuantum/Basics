bool StringGuideWindow::CreateThis(HWND hParent)
{
	if ( ClassWindow::RegisterWindowClass(0, NULL, NULL, CreateSolidBrush(RGB(0, 0, 0)), NULL, "StringGuide", NULL, false) &&
		 ClassWindow::CreateClassWindow(0, NULL, WS_OVERLAPPED|WS_CHILD|WS_VISIBLE, 463, 7, 125, 365, hParent, NULL) )
	{
		HWND hStringGuide = getHandle();
		HDC hDC = GetDC(hStringGuide);
		SelectObject(hDC, defaultFont);
		SIZE strSize = { };
		for (size_t i = 0; i < strColors.size(); i++)
		{
			auto Color = strColors.at(i);
			GetTextExtentPoint32A(hDC, std::get<2>(Color).c_str(), std::get<2>(Color).length(), &strSize);
			colorPrefix[i].CreateThis(hStringGuide, 2, i*13, strSize.cx, 13, std::get<2>(Color).c_str(), 0);
			color[i].CreateThis(hStringGuide, strSize.cx+3, i*13, 100, 13, std::get<1>(Color).c_str(), TEXT_COLOR_FIRST+i);
		}
		ReleaseDC(hDC);
		return true;
	}
	else
		return false;
}