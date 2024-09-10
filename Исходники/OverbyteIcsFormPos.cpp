//---------------------------------------------------------------------------
void __fastcall SaveFormPos(TForm *Form,
                            const AnsiString IniFileName,
                            const AnsiString SectionName,
                            const AnsiString KeyName)
{
    TIniFile     *IniFile;
    TWindowState WindowState;
    char         Buffer[256];

    if (IniFileName.Length() == 0)
        return;

    // Create inifile object => Open ini file
    IniFile = new TIniFile(IniFileName);

    WindowState = Form->WindowState;

    // If window minimized or maximized, restore to normal state
    if (Form->WindowState != wsNormal)
        Form->WindowState = wsNormal;

    // Save the window's postion and size to the ini file
    IniFile->WriteString(SectionName,
                         KeyName,
                         WindowPosToStr(Buffer, Form));

    // Destroy inifile object => close ini file
    IniFile->Free();

    Form->WindowState = WindowState;
}