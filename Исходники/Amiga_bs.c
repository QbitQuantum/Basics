int OpenBlockSelectWindow( void )
{
	struct NewGadget	ng;
	struct Gadget	*g;
	UWORD		lc, tc;
	UWORD		offx = Scr->WBorLeft, offy = Scr->WBorTop + Scr->RastPort.TxHeight + 1;

	if ( ! ( g = CreateContext( &BlockSelectGList ))){
		CloseBlockSelectWindow();
		return( 1L );
	}

	for( lc = 0, tc = 0; lc < BlockSelect_CNT; lc++ ) {

		CopyMem((char * )&BlockSelectNGad[ lc ], (char * )&ng, (long)sizeof( struct NewGadget ));

		ng.ng_VisualInfo = VisualInfo;
		ng.ng_TextAttr   = &topaz8;
		ng.ng_LeftEdge  += offx;
		ng.ng_TopEdge   += offy;

		BlockSelectGadgets[ lc ] = g = CreateGadgetA((ULONG)BlockSelectGTypes[ lc ], g, &ng, ( struct TagItem * )&BlockSelectGTags[ tc ] );

		while( BlockSelectGTags[ tc ] ) tc += 2;
		tc++;

		if ( NOT g ){
			CloseBlockSelectWindow();
			return( 2L );
		}
	}

	if ( ! ( BlockSelectWnd = OpenWindowTags( NULL,
				WA_Left,	BlockSelectLeft,
				WA_Top,		BlockSelectTop,
				WA_Width,	BlockSelectWidth,
				WA_Height,	BlockSelectHeight + offy,
				WA_IDCMP,	LISTVIEWIDCMP | BUTTONIDCMP | IDCMP_NEWSIZE | IDCMP_REFRESHWINDOW | IDCMP_RAWKEY,
				WA_Flags,	WFLG_SIZEGADGET|WFLG_DRAGBAR|WFLG_DEPTHGADGET|WFLG_SMART_REFRESH,
				WA_Gadgets,	BlockSelectGList,
				WA_Title,	BlockSelectWdt,
				WA_MinWidth,	160,
				WA_MinHeight,	60,
				WA_MaxWidth,	720,
				WA_MaxHeight,	467,
				WA_AutoAdjust,	TRUE,
				WA_PubScreen,Scr,
				TAG_DONE )))
	{
		CloseBlockSelectWindow();
		return( 4L );
	}

	GT_RefreshWindow( BlockSelectWnd, NULL );

	return( 0L );
}