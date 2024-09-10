void __fastcall TMainForm::FormDestroy(TObject *Sender) {
    if( !isCorrect ) // если выбраные файлы не открылись, не нужно их сохранять в .ini
        return;

    TIniFile *ini = new TIniFile(iniFile);
    try {
        ini->WriteString( "FileName", "file-copy", fcPanel->Caption );
        ini->WriteString( "FileName", "cyclogram", cPanel->Caption );
    }
    __finally {
        ini->Free();
        clearAll();
    }
}