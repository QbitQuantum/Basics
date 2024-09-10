void __fastcall TfrmMain::GetMinMaxInfo(TWMGetMinMaxInfo &Msg) {
	Msg.MinMaxInfo->ptMaxTrackSize.x = GetDeviceCaps(Canvas->Handle, HORZRES) +
		(Width - ClientWidth);
	Msg.MinMaxInfo->ptMaxTrackSize.y = GetDeviceCaps(Canvas->Handle, VERTRES) +
		(Height - ClientHeight);
}