// -------------------
// MCIErrorMessageBox
// Retrieve error message corresponding to return value from
//  mciSendCommand() or mciSenString()
// -------------------
static VOID MCIErrorMessageBox (MCIERROR iErrorCode)
{
	char szErrorText[128];
	if (!mciGetErrorStringA (iErrorCode, szErrorText, sizeof (szErrorText)))
		wsprintfA(szErrorText,"MCI CD Audio Unknow Error #%d\n", iErrorCode);
	CONS_Printf (szErrorText);
	/*MessageBox (GetActiveWindow(), szTemp+1, "LEGACY",
				MB_OK | MB_ICONSTOP);*/
}