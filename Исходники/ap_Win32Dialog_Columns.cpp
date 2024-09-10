BOOL AP_Win32Dialog_Columns::_onDeltaPos(NM_UPDOWN * pnmud)
{
	wchar_t buf[BUFSIZE];
	UT_Win32LocaleString str;
    
	switch( pnmud->hdr.idFrom )
	{
	case AP_RID_DIALOG_COLUMN_SPIN_NUMCOLUMNS:
		if( pnmud->iDelta < 0 )
		{
			setColumns( getColumns() + 1 );
		}
		else
		{
			if( getColumns() > 1 )
			{
				setColumns( getColumns() - 1 );
			}
		}
		SetDlgItemTextW(m_hDlg, AP_RID_DIALOG_COLUMN_EDIT_NUMCOLUMNS, _itow(getColumns(),buf,10));
		checkButton(AP_RID_DIALOG_COLUMN_RADIO_ONE, (getColumns()==1));
		checkButton(AP_RID_DIALOG_COLUMN_RADIO_TWO, (getColumns()==2));
		checkButton(AP_RID_DIALOG_COLUMN_RADIO_THREE, (getColumns()==3));
		return 1;

	case AP_RID_DIALOG_COLUMN_SPIN_SPACEAFTER:
		if( pnmud->iDelta < 0 )
		{
			incrementSpaceAfter( true );
		}
		else
		{
			incrementSpaceAfter( false );
		}
        str.fromUTF8 (getSpaceAfterString());
        SetDlgItemTextW(m_hDlg, AP_RID_DIALOG_COLUMN_EDIT_SPACEAFTER, str.c_str ());
		return 1;

	case AP_RID_DIALOG_COLUMN_SPIN_MAXSIZE:
		if( pnmud->iDelta < 0 )
		{
			incrementMaxHeight( true );
		}
		else
		{
			incrementMaxHeight( false );
		}
        str.fromUTF8 (getHeightString());
        SetDlgItemTextW(m_hDlg, AP_RID_DIALOG_COLUMN_EDIT_MAXSIZE, str.c_str ());
		return 1;

	default:
		return 0;
	}
}