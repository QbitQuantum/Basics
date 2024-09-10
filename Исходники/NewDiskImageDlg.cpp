/* #FN#
   Receives the edit controls content again. The user could press
   'Enter' or 'Alt-O' and then all changes he's made in the last
   edited control would be lost. */
void
/* #AS#
   Nothing */
CNewDiskImageDlg::
ReceiveFocused()
{
	CWnd *pWnd    = GetFocus();
	UINT  nCtrlID = pWnd ? pWnd->GetDlgCtrlID() : 0;

	if( IDC_NEWDISKIMAGE_SECTORS == nCtrlID )
	{
		OnKillfocusSectors();
	}
} /* #OF# CNewDiskImageDlg::ReceiveFocused */