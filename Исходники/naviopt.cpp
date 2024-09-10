//---------------------------------------------------------------------------
void __fastcall TOptDialog::BtnFontClick(TObject *Sender)
{
	AnsiString s;
	FontDialog->Font=FontLabel->Font;
	if (!FontDialog->Execute()) return;
	FontLabel->Font=FontDialog->Font;
	FontLabel->Caption=FontLabel->Font->Name+s.sprintf(" %dpt",FontLabel->Font->Size);
}