CEdit *CClickList::ShowInPlaceMemory(int Row, int Col)
{    
	CEdit *pMemoryEdit = new CPopupEdit(Row, Col, GetItemText(Row, Col));
	ASSERT_VALID(pMemoryEdit);

	pMemoryEdit->Create(WS_BORDER | WS_CHILD | WS_VISIBLE, GetInPlaceRect(Row, Col), 
		this, IDL_INPLACE_MEMORY);
	pMemoryEdit->SetFocus();

	return pMemoryEdit;
}