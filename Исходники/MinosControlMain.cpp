__fastcall TMinosControlForm::TMinosControlForm( TComponent* Owner )
      : TForm( Owner ), connected( false ), controlLineEventThread( 0 )
{
   disableInterrupts::initialise();
   enableTrace( ".\\TraceLog\\MinosControl_" );
   LineSet *ls = LineSet::GetLineSet();
   ls->lsLog = LineLog;
}