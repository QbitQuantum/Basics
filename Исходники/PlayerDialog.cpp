void CPlayerDialog::OnBnClickedButtonPtz()
{
	// TODO: 在此添加控件通知处理程序代码
    CMenu *pSubM = this->m_menuPtz.GetSubMenu( 0 );



	if ( pSubM && pSubM->m_hMenu )
	{
		CRect rcBtnPtz;
		this->m_btnPtz.GetWindowRect( rcBtnPtz );
		CPoint ptCenterPtn = rcBtnPtz.CenterPoint();

		BOOL bDigitalPtz = m_cVideoWnd.IsDigitalPtz();
		pSubM->CheckMenuItem( ID_MENU_PTZ, MF_BYCOMMAND | ( bDigitalPtz ? MF_UNCHECKED : MF_CHECKED ) );
		pSubM->CheckMenuItem( ID_MENU_DIGITAL_PTZ, MF_BYCOMMAND | ( bDigitalPtz ? MF_CHECKED : MF_UNCHECKED ) );

		pSubM->TrackPopupMenu( TPM_CENTERALIGN, ptCenterPtn.x, ptCenterPtn.y, this );
	}
    else
    {
        Log() << _T( "Ptz Menu is NULL!!" ) << endl;
    }

}