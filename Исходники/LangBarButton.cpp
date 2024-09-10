STDMETHODIMP LangBarButton::GetIcon(HICON *phIcon) {
	// https://msdn.microsoft.com/zh-tw/library/windows/desktop/ms628718%28v=vs.85%29.aspx
	// The caller will delete the icon when it's no longer needed.
	// However, we might still need it. So let's return a copy here.
	*phIcon = (HICON)CopyImage(icon_, IMAGE_ICON, 0, 0, 0);
	return S_OK;
}