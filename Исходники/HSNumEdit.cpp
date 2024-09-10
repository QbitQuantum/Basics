bool CHSNumEdit::CheckInput (UINT nChar)
{
	// checks no digit or dots before a minus sign
	// and no more than m_digits after '.'
	int pos = CharFromPos(GetCaretPos()); 
	CString txt;
	GetWindowText(txt);
	int len = txt.GetLength();
	//////// no digits or dot before a minus sign
	int sign = txt.Find('-');
	if ( pos <= sign )
		return false;
	//// no dot before m_digit from end of string
	int dot = txt.ReverseFind('.');
	if ( dot == -1 )
	{
		// no dot - check position before accepting
		if ( pos >= len -m_digits )
			return true;
		//else
		//	return false;
	}
	/////// limit digits after '.' 
	if ( len - pos < dot) 
	{
		// no insert if 
		// there is more than m_digits digits after zero.
		if ( pos -dot > m_digits )
			return false;
		// the insert will cause the same
		if ( len - dot> m_digits) 
			return false;
	}
	return true;
}