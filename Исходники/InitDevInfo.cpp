void CInitDevInfo::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	char cur_temp[500]={0x00};
	GetCurrentDirectory(500,cur_temp);
	CString CurrentPath;
	CurrentPath.Format("%s",cur_temp);

	this->OnOK();

	int state = 0;
	

	CDevKeyFirResume devKeyFirResumeDlg1(1,phSHandle);
	if(IDOK!=devKeyFirResumeDlg1.DoModal())
		return;
	devKeyFirResumeDlg1.GetRecoverState(&state);
	if(2 != state)
		return;

	//恢复管理员
	CDevKeyFirResume devKeyFirResumeDlg2(2,phSHandle);
	if(IDOK!=devKeyFirResumeDlg2.DoModal())
		return;
	devKeyFirResumeDlg2.GetRecoverState(&state);
	if(2 != state)
		return;


	SetCurrentDirectory(CurrentPath);

	int numclosed = _fcloseall( );
   
	Cph_PWMngrDlg phDlg(NULL,1,NULL,NULL,NULL/*phContainer*/,PWMMNGR_CAPTION);
	phDlg.DoModal();
}