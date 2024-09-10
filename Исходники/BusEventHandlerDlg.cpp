void CBusEventHandlerDlg::OnBnClickedOk()
{
    CButton* pomButton       = NULL;
    CString omStrHandlerName = STR_EMPTY ;
    CString omStrControl     = STR_EMPTY ;
    INT nCheck               = 0;
    BOOL bIsEnable           = TRUE;
    // Get the selected handlers either for deleteting or adding and
    // add the name in the array
    for(int j=0; j<defBUSEV_HANDLER_NUMBER; j++)
    {
        pomButton = (CButton*)GetDlgItem(IDC_CHKB_BUSEV_CONNECT_HANDLER + j);
        if(pomButton != NULL )
        {
            nCheck      = pomButton->GetCheck();
            bIsEnable   = pomButton->IsWindowEnabled();
            pomButton->GetWindowText(omStrControl);
            omStrControl.TrimLeft();
            omStrControl.TrimRight();
            omStrControl.Replace(' ','_');
            omStrControl.Replace('-','_');
            omStrHandlerName = omStrControl;
            if(nCheck == 1 && bIsEnable != 0 )
            {
                m_omStrArrayBusEventHandler.Add(omStrHandlerName);
            }
        }
    }
    OnOK();
}