void DisplaySpaceyMsg(void)
{

	UINT fMode;
	HDC dc;
    
	dc = Screen->GetBack()->GetDC();
    
	fMode = GetTextAlign(dc);
	SetTextAlign(dc, TA_CENTER | VTA_CENTER);
    
    Screen->GetBack()->TextXY(320, 2, GreenTxt, "SPACEY VADERS");
    Screen->GetBack()->TextXY(320, 20, GreenTxt, "by Paul Lord '97");

	SetTextAlign(dc, fMode);
	Screen->GetBack()->ReleaseDC();

}