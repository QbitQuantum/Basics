//初始化函数
BOOL CSetChip::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("压注"));

	//计算押注
	LONG lChipsArray[SET_CHIP_COUNT] ;

	//数据验证
	ASSERT( m_wMaxChip > 0 ) ;
	if ( m_wMaxChip <= 0 ) return TRUE ;

	for ( BYTE cbChipIndex = 0; cbChipIndex < SET_CHIP_COUNT; ++cbChipIndex )
	{
		lChipsArray[cbChipIndex] = LONG ( ( cbChipIndex + 1.0 ) / SET_CHIP_COUNT * m_wMaxChip ) ;

		//整百处理
		if ( lChipsArray[cbChipIndex] > 100 )
		{
			LONG lHundredCount = lChipsArray[cbChipIndex] / 100 ;
			lChipsArray[cbChipIndex] = lHundredCount * 100 ;
		}
	}

	//插入押注
	CComboBox *pChipComBox = ( CComboBox* ) GetDlgItem( IDC_SETCHIP ) ;
	CString strChip ;

	for ( BYTE cbChipIndex = 0; cbChipIndex < SET_CHIP_COUNT; ++cbChipIndex )
	{
		strChip.Format( TEXT( "%ld" ), lChipsArray[cbChipIndex] ) ;
		pChipComBox->InsertString( cbChipIndex, strChip ) ;
	}
	pChipComBox->SetCurSel( 0 ) ;	

	pChipComBox->SetFocus() ;

	m_nChip = lChipsArray[0] ;

	return TRUE;
}