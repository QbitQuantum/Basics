//设置焦点于聊天输入框
void CRightFrame::SetFocusToTalkInput()
{
	CEditUI* pEditCtrl = static_cast<CEditUI*>(m_pm.FindControl("Talk_Edt_Inp"));
	if (pEditCtrl)
	{
		pEditCtrl->SetFocus();
	}
}