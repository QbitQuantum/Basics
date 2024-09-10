void WFXEdit::RefreshDialog()
{
  CEdit *chkctrl;

  SetWindowText("Edit wave effect: "+itemname);
  chkctrl = (CEdit *) GetDlgItem(IDC_VOLUME);  
  chkctrl->EnableWindow(!!(the_wfx.header.flags&WFX_VOLUME));
  chkctrl = (CEdit *) GetDlgItem(IDC_FREQUENCY);  
  chkctrl->EnableWindow(!!(the_wfx.header.flags&WFX_FREQUENCY));
  chkctrl = (CEdit *) GetDlgItem(IDC_RADIUS);  
  chkctrl->EnableWindow(!!(the_wfx.header.flags&WFX_SRCURVE));
}