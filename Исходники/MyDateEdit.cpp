BOOL CMyDateEdit::CheckDate(char nchar,int StartPos,int EndPos)
{	
	CString strText;
	BOOL Leap;	
	int Year,Month,Day;
	strText=GetText();
	Year=atoi(strText);
	Month=atoi(strText.Mid(5,2));
	Day=atoi(strText.Mid(8,2));
	if((Year%4)==0)
	{
		if(((Year%100)==0)&&((Year%400)!=0))
			Leap=FALSE;
		else
			Leap=TRUE;
	}
	else
		Leap=FALSE;
	if(StartPos==4||StartPos==5)
	{
			if(nchar>'1')
			{
				MessageBeep((UINT)-1);
				return FALSE;
			}
			else if(nchar=='1')
			{
				strText=GetText();
				if(strText.GetAt(6)>'2')
				{
					strText.SetAt(6,'2');
					SetText(strText);
					SetSel(StartPos,StartPos);
					return TRUE;
				}
			}
			return TRUE;
	}
	if(StartPos==6)
	{
		strText=GetText();
		if(strText.GetAt(5)=='1')
		{
			if(nchar>'2')
			{
				MessageBeep((UINT)-1);
				return FALSE;
			}
		}
			return TRUE;
	}
	strText=GetText();
	if(StartPos==7||StartPos==8)
	{
		if(Month!=2)
		{
			if(nchar>'3')
				{
					MessageBeep((UINT)-1);
					return FALSE;
				}
				else if(nchar=='3')
				{
					strText=GetText();
					if(strText.GetAt(9)>'0')
					{
						if(Month==4||Month==6||Month==9||Month==11)
						{
							strText.SetAt(9,'0');
						}
						else
							strText.SetAt(9,'1');
						SetText(strText);
						SetSel(StartPos,StartPos);
						return TRUE;
					}			
				}
		}
		else
		{
			if(nchar>'2')
			{
				MessageBeep((UINT)-1);
				return FALSE;
			}
			else if(nchar=='2')
			{			
				strText=GetText();
				if(strText.GetAt(9)>'8')
				{
					if(Leap)
					{
						strText.SetAt(9,'9');
					}
					else
						strText.SetAt(9,'8');
					SetText(strText);
					SetSel(StartPos,StartPos);
					return TRUE;
				}
			}
		}
		return TRUE;				
	}
	if(StartPos==9)
	{
		strText=GetText();
		if(strText.GetAt(8)=='3')
		{
			if(Month==4||Month==6||Month==9||Month==11)
			{
				if(nchar>'0')
				{
					MessageBeep((UINT)-1);
					return FALSE;
				}	
			}
			else if(Month!=2)
			{
				if(nchar>'1')
				{
					MessageBeep((UINT)-1);
					return FALSE;
				}
			}
		}
		else if(strText.GetAt(8)=='2')
		{
			if(Month==2)
			{
				if(Leap)
				{
					if(nchar>'9')
					{
						MessageBeep((UINT)-1);
						return FALSE;
					}
				}
				else
				{
					if(nchar>'8')
					{
						MessageBeep((UINT)-1);
						return FALSE;
					}					
				}
			}
		}
		return TRUE;
	}
	return TRUE;
}