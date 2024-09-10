	void SetData(int Type,const wchar_t *Str,const wchar_t *Eol,int StrNum,int StrPos,int Length=-1)
	{
		if (Length == -1 && Str)
			Length=(int)StrLength(Str);

		this->Type=Type;
		this->StrPos=StrPos;
		this->StrNum=StrNum;
		this->Length=Length;
		xwcsncpy(EOL,Eol?Eol:L"",ARRAYSIZE(EOL)-1);

		if (this->Str)
		{
			delete[] this->Str;
		}

		if (Str)
		{
			this->Str=new wchar_t[Length+1];

			if (this->Str)
				wmemmove(this->Str,Str,Length);
		}
		else
			this->Str=nullptr;
	}