//---------------------------------------------------------------------------
void __fastcall TFileEdit::FindDialogFind(TObject *Sender)
{
    int FoundAt, StartPos, ToEnd;
    // 検索は現在選択されている場所から開始される
    // 何も選択されていない場合は，
    // テキストの最初から開始される
    if(REdit->SelLength) {
        StartPos = REdit->SelStart + REdit->SelLength;
    }
    else {
        StartPos = 0;
    }
    // ToEnd は検索範囲の文字数を示す
    ToEnd = REdit->Text.Length() - StartPos;


    TSearchTypes stype;
    if( FindDialog->Options.Contains(frMatchCase) ) stype << stMatchCase;
    if( FindDialog->Options.Contains(frWholeWord) ) stype << stWholeWord;
    FoundAt = REdit->FindText(FindDialog->FindText, StartPos, ToEnd, stype);
    if( FoundAt != -1 ) {
        REdit->SetFocus();
        REdit->SelStart = FoundAt;
        REdit->SelLength = FindDialog->FindText.Length();
        keybd_event(VK_RIGHT, 0, 0, 0);
        keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
        Application->ProcessMessages();
        REdit->SelStart = FoundAt;
        REdit->SelLength = FindDialog->FindText.Length();
    }
}