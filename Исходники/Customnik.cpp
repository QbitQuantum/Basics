void __fastcall TForm3::AddItems(const int HowMany)
{
	for(int i = 0; i < HowMany; i++) {
		UnicodeString NextItemText;
		NextItemText.sprintf(L"[%d] [%ls] [%ls%ls]", FTotal, names[FTotal % 9], Host, cats[FTotal % 4]);
		FTotal++;
		FStrings->Add(NextItemText);
	}
	FTotal++;
}