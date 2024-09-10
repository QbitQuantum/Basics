void CCFader::Destroy()
{
    DeleteObject(this->hBackground);
    DeleteObject(this->hCenterLine);
    DeleteObject(this->hFader);
    DeleteObject(this->hSlit);
    DeleteObject(this->hTickMarks);

	DestroyWindow(this->hWnd);
	UnregisterClassW(this->sClass, this->hInstance);
    this->hWnd = 0;
}