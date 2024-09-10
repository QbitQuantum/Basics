//---------------------------------------------------------------------------
void __fastcall TProgressForm::TimerTimer(TObject *Sender)
{
	Timer->Enabled = false;
	Process();
}