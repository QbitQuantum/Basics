/* See
 * http://blogs.msdn.com/b/larryosterman/archive/2007/10/31/what-happens-when-audio-rendering-fails.aspx
 * for detailed information about each of these entries */
HRESULT STDMETHODCALLTYPE VistaAudioSessionEvents::OnSessionDisconnected(
                                  AudioSessionDisconnectReason disconnectReason)
{

   switch (disconnectReason)  {
   case DisconnectReasonDeviceRemoval:
   case DisconnectReasonFormatChanged:
   case DisconnectReasonSessionDisconnected:
      notifyParent_->ShouldReInit();
      break;
   case DisconnectReasonServerShutdown:
      TaskDialog(nullptr,
                 nullptr,
                 PROGRAM_NAME,
                 _T("The audio service has been shut down. "),
                 _T("WinMute is not able to recover from that condition.\n")
                 _T("Please try restarting the program"),
                 TDCBF_OK_BUTTON,
                 TD_WARNING_ICON,
                 nullptr);
      break;
   case DisconnectReasonSessionLogoff:
      break;
   case DisconnectReasonExclusiveModeOverride:
      break;
   }
   return S_OK;
}