//---------------------------------------------------------------------------
void __fastcall TTVPMainForm::WMRearrangeModalWindows(TMessage &Msg)
{
	if(TVPFullScreenedWindow != NULL && TVPGetModalWindowRearrangeInFullScreen())
	{
		HDWP hdwp = BeginDeferWindowPos(1);
		hdwp = TVPShowModalAtTimer(hdwp);
		hdwp = TVPShowFontSelectFormTop(hdwp);
		hdwp = TVPShowHintWindowTop(hdwp);
		EndDeferWindowPos(hdwp);
	}
}