String			TSearchFilesFrm::GetSearchData()
{
	AnsiString data;
	AnsiString content_text = edtSearchContent->Text;

	if(cbSearchMode->ItemIndex == 0)
	{
		data = content_text;
	}
	else if(cbSearchMode->ItemIndex == 1)
	{
		data = BinToStr(content_text.c_str(), content_text.Length());
	}
	else if(cbSearchMode->ItemIndex == 2)
	{
		DWORD num = content_text.ToInt();
		data.SetLength(4);
		int pos = 0;
		WriteDWORD(data.c_str(), pos, num);
		data = BinToStr(data.c_str(), data.Length());
	}
	else if(cbSearchMode->ItemIndex == 3)
	{
		WORD num = content_text.ToInt();
		data.SetLength(2);
		int pos = 0;
		WriteWORD(data.c_str(), pos, num);
		data = BinToStr(data.c_str(), data.Length());
	}
	else if(cbSearchMode->ItemIndex == 4)
	{
		BYTE num = content_text.ToInt();
		data.SetLength(1);
		int pos = 0;
		WriteBYTE(data.c_str(), pos, num);
		data = BinToStr(data.c_str(), data.Length());
	}
	return	data;
}