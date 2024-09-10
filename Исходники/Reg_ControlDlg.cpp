CReg_ControlDlg::~CReg_ControlDlg()
{

	if(hFirstThread!=NULL)
		TerminateThread(hFirstThread, 0);
}