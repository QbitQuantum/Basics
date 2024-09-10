void CDisplayProperty::OnChangeSumcolinch() 
{
	// TODO: Add your control notification handler code here

//	UpdateData();
	CWnd *pWnd = GetDlgItem( IDC_SUMCOLINCH );
	CString strVal;
	pWnd->GetWindowText( strVal );
	int SumColInch = atoi ( (const char *)strVal );
	if ( SumColInch == 0 ) return;

	CDC *cDC = GetDC();
	int PixInch = cDC->GetDeviceCaps( LOGPIXELSX );		// Pixels Per Inch

	int SumWidth = PixInch / SumColInch;
	if ( SumWidth == 0 ) SumWidth = 1;
	PixInch = PixInch / SumWidth;

	char str[20];
	_itoa( PixInch, str, 10 );

	pWnd = GetDlgItem( IDC_SUMCOLINCHDIS );
	pWnd->SetWindowText( str );
	pWnd->Invalidate();
	ReleaseDC(cDC);
//	UpdateData(FALSE);
	
}