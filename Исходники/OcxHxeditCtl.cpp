void COcxHxeditCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	COleControl::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	ShowCaret();
	//获得焦点是装载钩子
	if (m_pwdStatue)
		SetHook(true);
	
}