//只允许输入数字 小数点
void CCheckEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//只接受 数字、小数点、退格
	if( (nChar < '0' || nChar > '9') && nChar != '.' && nChar != VK_BACK )
		return ;

	CString strCheck;
	CEdit *pEdit = (CEdit*)GetFocus();
	pEdit->GetWindowTextW(strCheck);
	DWORD dwSel = pEdit->GetSel();

	//光标在最左边  1.不允许输入小数点	2.除了个位为0外，最高位不能为 0
	if(dwSel == 0){
		if(nChar == '.' || (nChar == '0' && !strCheck.IsEmpty()))
			return ;
	}
	//光标不在最左边  1.只允许输入一个小数点	2.只有一个0的情况下，除了小数点外任何数字均覆盖掉0（这里要做的就是清空）
	else{
		if(nChar == '.' && strCheck.Find(_T('.')) != -1)
			return ;
		if(strCheck.Compare(_T("0")) == 0 && (nChar != '.'&& nChar != VK_BACK))
			pEdit->SetWindowTextW(NULL);
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}