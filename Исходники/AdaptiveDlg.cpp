BOOL CAdaptiveDlg::UpdateDataPlus(BOOL bSaveAndValidate)
{
	char buffer[128];
	CString s, se("Existing value will be used.");
	double out[2], xf[2];
	int i, m[4], x[2], right;
	CButton *hRadio;

	UpdateData(bSaveAndValidate);

	if (!bSaveAndValidate)
	{
		sprintfFloat(adap.stepsize[0], 4, buffer, sizeof(buffer));
		s = buffer;
		SetDlgItemText (IDC_STEP1, s);
		sprintfFloat(adap.stepsize[1], 4, buffer, sizeof(buffer));
		s = buffer;
		SetDlgItemText (IDC_STEP2, s);
		SetDlgItemInt(IDC_REVERSALS1, adap.reversal[0]);
		SetDlgItemInt(IDC_REVERSALS2, adap.reversal[1]);
		SetDlgItemInt(IDC_DOWN, adap.down);
		SetDlgItemInt(IDC_UP, adap.up);
		sprintfFloat(adap.initialPt, 3, buffer, sizeof(buffer));
		s = buffer;
		SetDlgItemText (IDC_INIT_VAL, s);
		SetDlgItemInt(IDC_FINAL_REV_4AVG, adap.finalRev4Avg);
		if (adap.descending)
		{
			hRadio = (CButton *)GetDlgItem(IDC_ASCENDING);
			hRadio->SetCheck(0);
			hRadio = (CButton *)GetDlgItem(IDC_DESCENDING);
			hRadio->SetCheck(1);
		}
		else
		{
			hRadio = (CButton *)GetDlgItem(IDC_ASCENDING);
			hRadio->SetCheck(1);
			hRadio = (CButton *)GetDlgItem(IDC_DESCENDING);
			hRadio->SetCheck(0);
		}
		hRadio = (CButton *)GetDlgItem(IDC_FACTOR);
		if (adap.factor)		hRadio->SetCheck(1);
		else			hRadio->SetCheck(0);
		OnUpdateInitVal();
	}
	else
	{
		hRadio = (CButton*)GetDlgItem(IDC_DESCENDING);
		adap.descending = (hRadio->GetCheck()) ? 1:0;

		//Validation
		s = "Stepsize Validation failed.";
		CECD(xf[0],IDC_STEP1, s)
		CECD(xf[1],IDC_STEP2, s)
		s = "reversal Validation failed.";
		CECI(x[0],IDC_REVERSALS1, s)
		CECI(x[1],IDC_REVERSALS2, s)
		s = "Down invalid."; CECI(m[0],IDC_DOWN,s)
		s = "Up invalid."; CECI(m[1],IDC_UP,s)
		s = "Number of final reversals invalid.";
		CECI(m[2],IDC_FINAL_REV_4AVG,s)
		GetDlgItemText (IDC_INIT_VAL, buffer, sizeof(buffer));
		i=str2array(out, 2, buffer, " ,");
		if (i==0) 	{	MessageBox ("Invalid initial value","Existing value will be used."); return FALSE;}
		if (i==2) 
		{
			adap.dualSeries=1;
			adap2.initialPt = out[1];
		}
		adap.initialPt = out[0];
		hRadio = (CButton *)GetDlgItem(IDC_FACTOR);
		adap.factor = (hRadio->GetCheck()==BST_CHECKED); 

		//Update
		adap.down = m[0];
		adap.up = m[1];
		adap.finalRev4Avg = m[2];
		memcpy((void*)adap.stepsize, (void*)xf, sizeof(xf));
		memcpy((void*)adap.reversal, (void*)x, sizeof(x));
		SyncAdap();
	}
	return TRUE;
}