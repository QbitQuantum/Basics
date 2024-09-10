bool FieldInfoDlg::validMinMaxValue( long id, bool isIntType )
{
    CEdit* pEdit = ( CEdit* )GetDlgItem( id );
    CString str;
    pEdit->GetWindowText( str );
    if( !validDataformat( str, isIntType ) )
    {
        pEdit->SetFocus();
        pEdit->SetSel( 0, -1 );
        return false;
    }
    return true;
}