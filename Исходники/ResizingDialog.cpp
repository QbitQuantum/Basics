//
// OnNcHitTest
// Handle mouse over the gripper
//
// Credit: Tommy Svensson
//
LRESULT CResizingDialog::OnNcHitTest(CPoint point)
{
	UINT ht = CDialog::OnNcHitTest(point);

	if(ht==HTCLIENT && m_bDrawGripper)
	{
		CRect rc;
		GetWindowRect( rc );
		rc.left = rc.right-GetSystemMetrics(SM_CXHSCROLL);
		rc.top = rc.bottom-GetSystemMetrics(SM_CYVSCROLL);
		if(rc.PtInRect(point))
		{
			ht = HTBOTTOMRIGHT;
		}
	}
	return ht;
}