void CMyGroupBox::AdjustRadio()
{
	CRect rcTmp;
	GetClientRect(rcTmp);
	int nWith = rcTmp.Width(); 
	for (int i = 0; i < GetRadioCount(); i++)
	{
		CButton* pBtn = m_RadioList.GetAt(i);
		pBtn->MoveWindow(10, 20 + i * m_nRadioHeight, nWith - 10 * 2, m_nRadioHeight);
	}
}