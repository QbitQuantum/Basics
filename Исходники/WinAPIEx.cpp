// 缩放 Region, SIZE 是缩放后的尺寸, 
// TODO: BUG 如果距离边缘少于5个像素才正确,应该智能的判断是靠哪个边
HRGN WINAPI RegulateRegion(HRGN hrgn, const SIZE* pszDest)
{
	ASSERT( hrgn && pszDest );

	RECT rcSrc;
	int nRet = ::GetRgnBox( hrgn, &rcSrc );
	ASSERT( nRet );

	const SIZE szSrc = {rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top};

	// 快速返回, 要返回复制的 Region, 不能直接返回，BugFix
	if( szSrc.cx == pszDest->cx && szSrc.cy == pszDest->cy )
	{
		HRGN hrgnDiff = CreateRectRgn(0, 0, 0, 0);
		ASSERT( hrgnDiff );
		nRet = ::CombineRgn(hrgnDiff, hrgn, NULL, RGN_COPY);
		ASSERT( ERROR != nRet );
		return hrgnDiff;
	}

	// 1 对 hrgn 取反 hrgnDiff = box - hrgn
	HRGN hrgnBox = CreateRectRgn(0, 0, szSrc.cx, szSrc.cy);
	ASSERT( hrgnBox );

	HRGN hrgnDiff = CreateRectRgn(0, 0, 0, 0);
	ASSERT( hrgnDiff );

	nRet = CombineRgn(hrgnDiff, hrgnBox, hrgn, RGN_DIFF);
	ASSERT( ERROR != nRet );
	
	// 2 对 hrgnDiff 进行缩放
	DWORD dwCount = GetRegionData(hrgnDiff, 0, 0);
	LPRGNDATA prd = (LPRGNDATA)new BYTE[dwCount];
	GetRegionData(hrgnDiff, dwCount, prd);
	RECT* prc = (RECT*)prd->Buffer;

	int y = pszDest->cy - szSrc.cy;
	int x = pszDest->cx - szSrc.cx;

#if 0
	for(int j=0; j<prd->rdh.nCount; j++)
	{
		if( szSrc.cx == prc[j].right && 0 == prc[j].top )
		{
			TRACERECT( "right, top", &prc[j] );
		}
	}
#endif
	for(unsigned int i=0; i<prd->rdh.nCount; i++)
	{
		// 所有右边的
		if( prc[i].right == szSrc.cx )
		{
			prc[i].left += x;
			prc[i].right += x;

			// 右下角
			if( szSrc.cy - prc[i].bottom < 10 )
			{
				prc[i].top += y;
				prc[i].bottom += y;
			}
		}
		// 左下角, BUGFIX: prc[i].top > 5 这个条件
		else if( prc[i].left == 0 && prc[i].top > 10  ) //szSrc.cy - prc[i].bottom < 5 && prc[i].top > 5 )
		{
			prc[i].top += y;
			prc[i].bottom += y;
		}
	}
#if 0
	for(i=0; i<prd->rdh.nCount; i++)
	{
		if( 0 == prc[i].left && 0 == prc[i].top )
		{
			// TRACERECT( "after: left, top", &prc[i] );
		}
		else if( pszDest->cx == prc[i].right && 0 == prc[i].top )
		{
			TRACERECT( "after: right, top", &prc[i] );
		}
	}
#endif

	// TODO: hrgn 是否产生泄露呢？

	// 3 生成放大后的 Region (排除的部分)
	hrgn = ExtCreateRegion(NULL, dwCount, prd);
	ASSERT( hrgn );

	delete [] prd;

	// 4 再排除 hrgnDiff = box - hrgn
	SetRectRgn(hrgnBox, 0, 0, pszDest->cx, pszDest->cy);
	SetRectRgn(hrgnDiff, 0, 0, 0, 0);
	nRet = CombineRgn(hrgnDiff, hrgnBox, hrgn, RGN_DIFF);
	ASSERT( ERROR != nRet );

	nRet = DeleteObject( hrgnBox );
	ASSERT( nRet );

	// 不应该释放哟
	// nRet = DeleteObject( hrgn );
	// ASSERT( nRet );

	return hrgnDiff;
}