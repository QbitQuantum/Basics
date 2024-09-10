void CConstraintEditDialog::insertFuncString()
{
	if(!m_editExpression) {
		return;
	}

	CPoint caret = GetCaretPos();
	int curpos = c_expredit.CharFromPos(caret);

	CString selfun;
	int cursel = m_funclist.GetCurSel();
	int len = m_funclist.GetTextLen(cursel);
    m_funclist.GetText(cursel, selfun.GetBuffer(len+2) );
	c_expredit.ReplaceSel(selfun);
	if(selfun!=_T("self") && selfun!=_T("children"))
		c_expredit.ReplaceSel(_T("()"));
	if(selfun==_T("children") || selfun==_T("project().Materials"))
	{
		c_expredit.ReplaceSel(_T("(\"\")"));
	}
	c_expredit.SetFocus();
}