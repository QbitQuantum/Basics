void CoptimizerDlg::OnBnClickedRadioPreset()
{	
	CComboBox *CBox = (CComboBox *)GetDlgItem(IDC_COMBO_PRESET);
	CSliderCtrl *Slider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_CUSTOM);
	int Sel;

	Sel = CBox->GetCurSel();
	CBox->EnableWindow(TRUE);
	
	SetSlider(Slider, Sel);
	Slider->EnableWindow(FALSE);
}