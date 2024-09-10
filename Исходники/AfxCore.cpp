UINT AfxRecalculateYield( int nDays, BOOL bReport )
{
	// 计算市场年平均收益率
	double	market_yield_average = 0.0, market_yield_d = 0.0;
	double	market_dayyield_average = 0.0, market_dayyield_d = 0.0;
	CKData	& kdayMain	=	AfxGetStockMain().GetKDataDay();

	if( kdayMain.GetSize() <= nDays )
	{
		if( bReport )
			AfxMessageBox( IDS_RECALYIELD_NOSZZS, MB_OK | MB_ICONINFORMATION );
		return 0;
	}
	BOOL bmarket_yield_ok = CalculateYieldYear( kdayMain, &market_yield_average, &market_yield_d, nDays );
	BOOL bmarket_dayyield_ok = CalculateYieldDay( kdayMain, &market_dayyield_average, &market_dayyield_d, nDays );

	if( !bmarket_yield_ok && !bmarket_dayyield_ok )
	{
		if( bReport )
			AfxMessageBox( IDS_RECALYIELD_NOSZZS, MB_OK | MB_ICONINFORMATION );
	}
	
	// 开始生成结果数据
	CStockContainer & container = AfxGetStockContainer();
	int	nCount	=	0;
	// 等待对话框
	CWaitDlg	*	pWait	=	NULL;
	if( bReport )
	{
		pWait	=	new CWaitDlg( AfxGetMainWnd() );
		pWait->SetProgressRange( 0, container.GetSize()-1 );
	}
	for( int i=0; i<container.GetSize(); i++ )
	{
		if( pWait )
		{
			pWait->SetProgress( i );
			if( pWait->WaitForCancel( ) )
				break;
		}

		CStockInfo	& info	=	container.ElementAt(i);

		LONG	stocktype	=	info.GetType();
		if( CStock::typeshIndex != stocktype && CStock::typeshA != stocktype && CStock::typeshB != stocktype
			&& CStock::typeszIndex != stocktype && CStock::typeszA != stocktype && CStock::typeszB != stocktype )
			continue;

		CStock	stock;
		stock.SetStockInfo( &info );
		AfxPrepareStockData(&AfxGetDB(),stock,CKData::ktypeDay,CKData::formatXDRup,CKData::mdtypeClose,TRUE,TRUE);
		CKData	& kday	=	stock.GetKDataDay();

		info.m_fYield_average		=	(float)STKLIB_DATA_INVALID;
		info.m_fYield_stddev		=	(float)STKLIB_DATA_INVALID;
		info.m_fBeite				=	(float)STKLIB_DATA_INVALID;

		double	yield_average = 0., yield_d = 0., beite = 0. ;
		if( CalculateYieldYear( kday, &yield_average, &yield_d, nDays ) )
		{
			info.m_fYield_average	=	(float)( 100. * yield_average );
			info.m_fYield_stddev	=	(float)( 100. * yield_d );
			if( bmarket_yield_ok && CalculateBeiteYear( kday, kdayMain, market_yield_average, market_yield_d, &beite, nDays ) )
				info.m_fBeite		=	(float)( beite );
			else if( bmarket_dayyield_ok && CalculateBeiteDay( kday, kdayMain, market_dayyield_average, market_dayyield_d, &beite, nDays ) )
				info.m_fBeite		=	(float)( beite );
		}
		else if( CalculateYieldDay( kday, &yield_average, &yield_d, nDays ) )
		{
			info.m_fYield_average	=	(float)( 100. * (pow(1+yield_average,STKLIB_DAYS_INONEYEAR)-1) );
			info.m_fYield_stddev	=	(float)( 100. * sqrt((double)STKLIB_DAYS_INONEYEAR) * yield_d );
			if( bmarket_dayyield_ok && CalculateBeiteDay( kday, kdayMain, market_dayyield_average, market_dayyield_d, &beite, nDays ) )
				info.m_fBeite		=	(float)( beite );
		}

		nCount	++;
	}

	// 保存到硬盘文件
	AfxGetDB().StoreBasetable( container );

	// 关闭等待对话框和目标文件
	if( pWait )
	{
		pWait->DestroyWindow();
		delete	pWait;
	}

	return nCount;
}