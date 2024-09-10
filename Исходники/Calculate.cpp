void CCalculate::VBCal(long zdjh, long nth) 
{
	// TODO: Add your dispatch handler code here
	/*	if( !PhsDrawUser::InitDB() )
		return;

	_RecordsetPtr rsZ1(__uuidof(Recordset));
	CRString strSQL;

	try 
	{
		strSQL.Format("SELECT nth FROM Z1 WHERE [VolumeID]=%d AND [ZDJH]=%d",
			PhsDrawUser::m_iVlmID,PhsDrawUser::m_iZdjh);
		rsZ1->CursorLocation = adUseClient;
		rsZ1->Open(_variant_t(strSQL),(IDispatch*)PhsDrawUser::m_pConnPRJDB,adOpenStatic,adLockOptimistic,adCmdText);
		if( rsZ1->adoEOF && rsZ1->BOF )
			return;

		if( (long)rsZ1->RecordCount > 1 )//根据路数确定使用标准支吊架选型还是非标支吊架选型
		{
			rsZ1->Close();
			PhsNonStandardAutoCalc();
		}
		else
		{
			long lnth = vtoi(rsZ1->GetCollect("nth"));
			rsZ1->Close();
			PhsStandardAutoCalc( lnth );
		}
	}
	catch(_com_error& e)
	{
		ReportError(e.Description(), __FILE__, __LINE__);
	}

	PhsDrawUser::UnInitDB();
*/

/*
	VARIANT var1,var2;
	VariantInit(&var1);
	VariantInit(&var2);
	_RecordsetPtr rs;
	rs.CreateInstance(__uuidof(Recordset));

	CFrmStatus *frm;
	var1 = varRs;
//	VariantCopy(&var1,&varRs);

	HRESULT hr = VariantChangeType(&var2,&var1,0,VT_UNKNOWN);
	if(FAILED(hr))
		return ;
	rs = (_RecordsetPtr) var1.punkVal;
//	if(rs->adoEOF && rs->BOF)
//	{
		AfxMessageBox("rs");
//	}
	
//	hr = VariantChangeType(&var2,&varFrm,0,VT_UNKNOWN);
//	frm = (CFrmStatus*)var2.punkVal;
*/


	CFrmStatus FrmProgress;
	if(!IsWindow(FrmProgress.m_hWnd))
    	FrmProgress.Create(IDD_STATUS,NULL);
	FrmProgress.CenterWindow();  
	FrmProgress.ShowWindow(SW_SHOW);
	
    CString sTmp;
	sTmp.Format("%d",zdjh);

	FrmProgress.m_Label1.Format(GetResStr(IDS_CalculatingNoXphs),sTmp);// "正在计算" & zdjh & "号支吊架"
	FrmProgress.SetWindowText(GetResStr(IDS_PhsCalculation));// "计算支吊架"
	FrmProgress.UpdateData(false);
	FrmProgress.UpdateStatus(0.02f,true);
	FrmProgress.UpdateWindow();


	_RecordsetPtr rs;
	rs.CreateInstance(__uuidof(Recordset));
	 

	CString strSQL; 

	strSQL.Format("SELECT * FROM [ZA] WHERE [VolumeID]=%d AND [ZDJH]=%d",EDIBgbl::SelVlmID,zdjh);
	rs->Open(_variant_t(strSQL),(IDispatch*)conPRJDB,adOpenStatic,adLockOptimistic,adCmdText);
	if( rs->adoEOF && rs->BOF )
		AfxMessageBox("recordset empty");

	modPHScal::VB_Cal (rs,zdjh,FrmProgress,nth);

	FrmProgress.UpdateWindow();
	FrmProgress.ShowWindow(SW_HIDE);
	FrmProgress.DestroyWindow();

}