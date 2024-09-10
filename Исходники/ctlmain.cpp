//---------------------------------------------------------------------------
__fastcall TRigCtlMain::TRigCtlMain( TComponent* Owner )
      : TForm( Owner ), my_rig( 0 )
{
   enableTrace( ".\\TraceLog\\MinosRigCtl_" );
}