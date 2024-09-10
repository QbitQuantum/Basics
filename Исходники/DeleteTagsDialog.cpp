void CDeleteTagsDialog::OnSelchangeComboDeleteTaglist() 
{
    int     location = m_tagList.GetCurSel();
    CButton *p = (CButton *)GetDlgItem( IDOK );

    if ( location == LB_ERR ) {
        p->EnableWindow( FALSE );
        return;
    }

	m_tagList.GetLBText( location, m_tag );
    m_tagIndex = location;

    p->EnableWindow( TRUE );
}