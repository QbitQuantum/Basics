//---------------------------------------------------------------------------
__fastcall TMinosChatForm::TMinosChatForm( TComponent* Owner )
      : TForm( Owner ), subscribed( false ), saveResize( false )
{
   enableTrace( ".\\TraceLog\\MinosChat_" );
}