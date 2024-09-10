//---------------------------------------------------------------------------
__fastcall TKeyControlForm::TKeyControlForm( TComponent* Owner )
      : TForm( Owner ), saveResize( false )
{
   enableTrace( ".\\TraceLog\\MinosKeyer" );
   SetPriorityClass( GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS );  // Win2K and Above only!

   std::vector<boost::shared_ptr<VKMixer> > mixers = VKMixer::getMixers( Handle );   // initialisae the VKMixer system

   OutputMixerComboBox->Enabled = !LockMixersCB->Checked;

   populateMixerList();

   loadKeyers();

   setLineCallBack( lcallback );
   setVUCallBack( recvolcallback, outvolcallback );

   TMessage Message;
   MMMixControlChange( Message );
}