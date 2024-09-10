///////////////////////////////////////////
//   Is called when the attack is to begin.
///////////////////////////////////////////
void CRSAFactorHintDlg::OnStart() 
{
	
	UpdateData();
	int m_b=GetDlgItemInt(IDC_EDITB);
	int m_bitsOfP=GetDlgItemInt(IDC_EDITBITSOFP);
	if (m_bitsOfP==0){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_FH_ENTERP);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
	else
		if(m_b>m_bitsOfP){
			CString msg, myTitle;
			msg.Format(IDS_RSA_FH_BITSOFP,
				m_bitsOfP,
				m_b);
			this->GetWindowText(myTitle);
			MessageBox(msg,myTitle);
		}
		else
			if(m_bitsOfN==0){
				CString tmp, myTitle;
				tmp.LoadString(IDS_RSA_FH_CHOOSEN);
				this->GetWindowText(myTitle);
				MessageBox(tmp,myTitle);
			}
			else
				if(GetDlgItemInt(IDC_EDITDIM)==0){
					int needed = (int)((double)(m_bitsOfN+3)/4)+1;
					CString form, myTitle;
					form.Format(IDS_RSA_FH_ATLEASTKNOWN,
						m_b,
						needed);
					this->GetWindowText(myTitle);
					MessageBox(form,myTitle);
				}
				else{
					disableEnable(false); // disable example geneartion
					GetDlgItem(IDCANCELATTACK)->EnableWindow(true);
					GetDlgItem(IDSTART)->EnableWindow(false);
					SetTimer(1, 1000, 0); // this timer updates the GUI
					elapsedTime=0;
					
					int newbase=2; // representation of the Parameters N
					UpdateData();  // and P
					if(m_base==0)
						newbase=10;
					if(m_base==1)
						newbase=16;
					
					fh.setN(m_N);
					ZZ P = m_GuessP;
					if(m_msbLsb==0)
						P*=power(to_ZZ(2),m_bitsOfP-m_b);
					fh.setP(P);
					fh.setBitsOfP(m_bitsOfP);
					fh.setB(GetDlgItemInt(IDC_EDITB));
					
					SetDlgItemText(IDC_EDITFACTORP,"");
					SetDlgItemText(IDC_EDITFACTORQ,"");
					
					UpdateData();
					fh.status=1;
					pThread = AfxBeginThread (thrFunction, this); 
				}
				
}