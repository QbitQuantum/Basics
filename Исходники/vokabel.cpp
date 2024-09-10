void TfrmVokabel::setEntry(CEntry *e)
{
    HANDLE hwnd;
    if (e==NULL)
    this->Close();

    this->lblWord->Caption = e->word.c_str();
    this->lblTranslation->Caption = e->translation.c_str();

    this->lblTranslation->Visible = false;

    hwnd=FindWindowExA(NULL,NULL,NULL,"Vokabel");
    SetForegroundWindow((HWND__*)hwnd);
}