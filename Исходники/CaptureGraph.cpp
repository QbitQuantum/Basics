void CaptureGraph::OnSize()
{
	HWND hwnd;
    CWnd *pcwnd;
    CRect rect;
    mVideoWindow->get_Owner((OAHWND*)&hwnd);
    pcwnd=CWnd::FromHandle(hwnd);
    pcwnd->GetClientRect(&rect);
    mVideoWindow->SetWindowPosition(rect.left ,rect.top ,
                  rect.right ,rect.bottom );
}