void CtestDlg::Decrypt()
{
	CString temp,Alph;
	alphabet.GetWindowTextW(Alph);
	offset.GetWindowTextW(temp);
	int NewState=(int)_wcstoi64(temp.GetBuffer(),NULL,10);
	text.GetWindowTextW(temp);
	for(int i=0;i<temp.GetLength();i++)
	{
		int c=Alph.Find(temp[i]);
		if(c!=-1)
		{
			c+=NewState-state;
			if(c<0)
				c+=Alph.GetLength();
			temp.SetAt(i,Alph[c%Alph.GetLength()]);
		}
	}
	state=NewState;
	text.SetWindowTextW(temp);
}