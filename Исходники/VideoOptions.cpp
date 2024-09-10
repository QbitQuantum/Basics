void CVideoOptions::OnAbout() 
{
	// TODO: Add your control notification handler code here
	int sel = ((CComboBox *) GetDlgItem(IDC_COMPRESSORS))->GetCurSel();
	if (sel != CB_ERR)  {
		
	
		HIC hic = ICOpen(compressor_info[sel].fccType, compressor_info[sel].fccHandler, ICMODE_QUERY);
		if (hic) {			
				
			ICAbout(hic,m_hWnd);			
			ICClose(hic);
		}


	}
	
}