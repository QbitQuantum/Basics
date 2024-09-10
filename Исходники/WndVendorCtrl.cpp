void CWndVendorCtrl::OnDrawItemInfo( C2DRender* p2DRender, CItemElem* pItemElem, int nX, int nY )
{
	// 아이템 이름 및 가격
	CString strItem;
	if( pItemElem->GetAbilityOption() )
		strItem.Format( "%s +%d", pItemElem->GetName(), pItemElem->GetAbilityOption());
	else
	{
		strItem.Format( "%s", pItemElem->GetName() );
	}
	
	int nLen	= strItem.GetLength();
	CSize size	= p2DRender->m_pFont->GetTextExtent( strItem );
	
	if( size.cx > MAX_VENDOR_ITEM_TEXT_EXTENT )
	{
		CString str, strOld;
		WORD wCodePage = g_codePage;
		const char* begin = strItem;
		const char* end = begin + strItem.GetLength();
		const char* iter = begin;
		while( *iter && iter < end )
		{
			const char* next	= CharNextEx( iter, wCodePage );
			char temp[16];
			memcpy( temp, iter, next - iter );
			temp[next - iter]	= 0;
			str		+= temp;
			size	= p2DRender->m_pFont->GetTextExtent( str );
			if( size.cx > MAX_VENDOR_ITEM_TEXT_EXTENT )
				break;
			iter	= next;
			strOld	= str;
		}
		strItem		= strOld + "...";
	}
/*
	// 아이템 명이 너무 길 경우 ...으로.
	if( strItem.GetLength() > 18 ) 
	{
		int	nReduceCount = 0;

		for( nReduceCount=0; nReduceCount<18; )
		{
			if( IsDBCSLeadByte( strItem[ nReduceCount ] ) )
				nReduceCount+=2;
			else
				nReduceCount++;
		}
		strItem = strItem.Left( nReduceCount );
		strItem += "...";
	}
*/
	p2DRender->TextOut( nX + 50, nY + 3, strItem, 0xffffffff );//ADEILSON 0xff000000
	
	char szCost[1024] = {0,};
	DWORD dwCostTem = pItemElem->m_nCost;
	_itoa( dwCostTem, szCost, 10 );
	if( ::GetLanguage() == LANG_KOR )
		strItem = GetNumberFormatSelling(szCost);
	else
		strItem = GetNumberFormatEx(szCost);
	
	DWORD dwCostColor = 0xffffffff;//ADEILSON 0xff000000
	if( dwCostTem >= 1000000000 ) // 10억
		dwCostColor = 0xff990099;
	else if( dwCostTem >= 100000000 ) // 1억
		dwCostColor = 0xffCC0303;
	else if( dwCostTem >= 10000000 ) // 1000만
		dwCostColor = 0xffFF6600;
	else if( dwCostTem >= 1000000 ) // 100만
		dwCostColor = 0xff3333FF;
	else if( dwCostTem >= 100000 ) // 10만
		dwCostColor = 0xff009900;
	
	p2DRender->TextOut( nX + 50, nY + 17, strItem, dwCostColor );
}