/*!
	Targetアイテムを使う・クルップボードへ・他に使いたいときは？
	@param[in]	hWnd	ウインドウハンドル
	@param[in]	id		動作モードＩＤ
	@return		HRESULT	終了状態コード
*/
HRESULT DraughtItemUse( HWND hWnd, INT id )
{
	LPSTR		pcAaItem;
	INT_PTR		iItems, i, iOffset, iTarget;
	UINT_PTR	cbSize;
	UINT		dMode;
	MAAM_ITR	itItem;

	if( gbThumb )	//	サムネモード
	{
		iOffset = gdVwTop * TPNL_HORIZ;
		iTarget = iOffset + giTarget;

		pcAaItem = AacAsciiArtGet( iTarget );
		if( !(pcAaItem) )	return E_OUTOFMEMORY;

		switch( id )
		{
			case IDM_DRAUGHT_INSERTEDIT:	dMode = MAA_INSERT;		break;
			case IDM_DRAUGHT_INTERRUPTEDIT:	dMode = MAA_INTERRUPT;	break;
			case IDM_DRAUGHT_LAYERBOX:		dMode = MAA_LAYERED;	break;
			default:
			case IDM_DRAUGHT_UNICLIP:		dMode = MAA_UNICLIP;	break;
			case IDM_DRAUGHT_SJISCLIP:		dMode = MAA_SJISCLIP;	break;

			case IDM_THUMB_DRAUGHT_ADD:		dMode = MAA_DRAUGHT;	break;
		}
		StringCchLengthA( pcAaItem, STRSAFE_MAX_CCH, &cbSize );

		ViewMaaMaterialise( hWnd, pcAaItem, cbSize, dMode );

		if( id != IDM_THUMB_DRAUGHT_ADD )
		{
			//	ここでお気に入りに入れる・大丈夫か？
			if( SUCCEEDED( AaItemsFavUpload( pcAaItem, cbSize ) ) )
			{
				FavContsRedrawRequest( hWnd );
			}
		}

		FREE(pcAaItem);
	}
	else
	{
		iItems = gvcDrtItems.size( );	//	現在個数
		if( 0 >= iItems )	return E_OUTOFMEMORY;

		for( i = 0, itItem = gvcDrtItems.begin(); gvcDrtItems.end() != itItem; i++, itItem++ )
		{
			if( giTarget == i )	//	ヒット
			{
				switch( id )
				{
					case IDM_DRAUGHT_INSERTEDIT:	dMode = MAA_INSERT;		break;
					case IDM_DRAUGHT_INTERRUPTEDIT:	dMode = MAA_INTERRUPT;	break;
					case IDM_DRAUGHT_LAYERBOX:		dMode = MAA_LAYERED;	break;
					default:
					case IDM_DRAUGHT_UNICLIP:		dMode = MAA_UNICLIP;	break;
					case IDM_DRAUGHT_SJISCLIP:		dMode = MAA_SJISCLIP;	break;
				}
				StringCchLengthA( itItem->pcItem, STRSAFE_MAX_CCH, &cbSize );

				ViewMaaMaterialise( hWnd, itItem->pcItem, cbSize, dMode );
			}
		}
	}

	return E_INVALIDARG;
}