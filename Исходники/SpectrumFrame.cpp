void CSpectrumFrame::OnDefokus() {
	char str[300];
	if(m_type_spectr == SPECTR) {
		if(this->m_type_plant == PAM) {
			CDialogDefokus dialog;
			dialog.m_apertura = m_apertura;
			dialog.m_length_wave = m_length_wave;
			dialog.m_iDem = this->m_iDem;
			dialog.m_k_ap_diaf = pow((6.0 / (dialog.m_Ccf * pow(10.0,7.0) * pow(dialog.m_length_wave, 3.0))), 0.25);
			dialog.UpdateD();

			if(dialog.DoModal() == IDOK) {
				LLayer = m_length_wave;
				DLayer = dialog.m_apertura;
				CObjectFrameDefokus *m_object;
				
				CDialogInfo* DialogInfo = new CDialogInfo(NULL);
				DialogInfo->Create(IDD_INFO,NULL);
				DialogInfo->ShowWindow(SW_SHOW);
				DialogInfo->m_str.Format("Идет расчет дефокусировки...");
				DialogInfo->UpdateData(FALSE);
				
				m_object = new CObjectFrameDefokus(m_fArroy, m_iDem, dialog.m_D, dialog.m_Ccf, dialog.m_Cxp, dialog.m_k_ap_diaf);
				m_object->Kvadrant = 0;
				m_object->GetOptimumCoefficient();
				m_object->m_fPos_Const *= 0.8;
				m_object->ScaleView();
				sprintf(str, "Визуализация Дефокусировка [%dx%d]", m_iDem, m_iDem);
				if (!m_object->Create(NULL,_TEXT(str),0, rectDefault, NULL))
					return;	
				m_object->MoveWindow(80,80,10000,10000);
				
				DialogInfo->CloseWindow();
				delete DialogInfo;
			}
		}
	} else {
		AfxMessageBox("Визуализация находится только со спектра!!!",MB_OK);
	}	
}