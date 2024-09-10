CHTMLViewCapView::~CHTMLViewCapView()
{
	::CloseHandle(m_hDocCompleteEvent);
	GdiplusShutdown(m_gdiplusToken);
}