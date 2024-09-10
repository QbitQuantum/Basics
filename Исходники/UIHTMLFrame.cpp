void __fastcall THTMLFrame::HtmlHotSpotClick(TObject *Sender,
	  const AnsiString SRC, bool &Handled)
{
	TSysCharSet Delims;
	Delims << ':';
	String Proto = ExtractWord(1,SRC,Delims);
	Handled=false;

	if(SameText(Proto,"dcm"))
	{
		 String Script = SRC.c_str()+4;
		 Evalate(Script);
		 Handled = true;
	}
	else if(SameText(Proto,"http") || SameText(Proto,"mailto"))
	{
		ShellExecuteA(Handle, NULL, SRC.c_str(), NULL, NULL, SW_SHOWNORMAL);
		Handled = true;
	}
}