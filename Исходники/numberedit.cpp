long CNumberEdit::GetNumber()
{
	CString csText;
	GetWindowText(csText);
	
	return ATOL(csText);
}