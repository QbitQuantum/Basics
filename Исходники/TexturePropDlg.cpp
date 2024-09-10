void CTexturePropDlg::EnableCheckBox(UINT id, BOOL bEnable)
{
	CButton *pButton;

	pButton = (CButton*)GetDlgItem(id);
	if( pButton )
		pButton->EnableWindow( bEnable );
}