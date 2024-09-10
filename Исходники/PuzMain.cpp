// выбор в меню Справка команды О программе
void __fastcall TForm1::N4Click(TObject *Sender)
{
    WinExec("hh.exe -mapid 3 puzzle.chm", SW_RESTORE);

}