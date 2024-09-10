LRESULT CGenericCancelProgressDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CGenericProgressDlg::OnPaint(uMsg, wParam, lParam, bHandled);
    if (GetDlgItem(IDC_STOP).IsWindow())
    {
	    GetDlgItem(IDC_STOP).RedrawWindow();
    }
	ValidateRgn(NULL);
	return 0;
}