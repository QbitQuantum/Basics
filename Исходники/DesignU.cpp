//---------------------------------------------------------------------------
void __fastcall TDesign::Button1Click(TObject *Sender)
{
	EventColor = ColorBox1->Selected;
	SelectColor = ColorBox2->Selected;
    if(FileExists(ExtractFilePath(Application->ExeName) + "\\settings.ini"))
	{
		TIniFile *inifile;
		inifile = new TIniFile(ExtractFilePath(Application->ExeName) + "\\settings.ini");
		inifile->WriteInteger("Color", "EventColor", EventColor);
		inifile->WriteInteger("Color", "SelectColor", SelectColor);
        inifile->UpdateFile();
		inifile->Free();
	}
	Close();
	MainForm->Draw();
}