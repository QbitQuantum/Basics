int OpenBlankerWindow( void )
{
	struct NewGadget	ng;
	struct Gadget	*g;
	UWORD		lc, tc;
	UWORD		wleft = BlankerLeft, wtop = BlankerTop, ww, wh;

	ComputeFont( BlankerWidth, BlankerHeight );

	ww = ComputeX( BlankerWidth );
	wh = ComputeY( BlankerHeight );

	if (( wleft + ww + OffX + Scr->WBorRight ) > Scr->Width ) wleft = Scr->Width - ww;
	if (( wtop + wh + OffY + Scr->WBorBottom ) > Scr->Height ) wtop = Scr->Height - wh;

	if ( ! ( BlankerFont = OpenDiskFont( Font )))
		return( 5L );

	if ( ! ( g = CreateContext( &BlankerGList )))
		return( 1L );

	for( lc = 0, tc = 0; lc < Blanker_CNT; lc++ ) {

		CopyMem((char * )&BlankerNGad[ lc ], (char * )&ng, (long)sizeof( struct NewGadget ));

		ng.ng_VisualInfo = VisualInfo;
		ng.ng_TextAttr   = Font;
		ng.ng_LeftEdge   = OffX + ComputeX( ng.ng_LeftEdge );
		ng.ng_TopEdge    = OffY + ComputeY( ng.ng_TopEdge );
		ng.ng_Width      = ComputeX( ng.ng_Width );
		ng.ng_Height     = ComputeY( ng.ng_Height);

		BlankerGadgets[ lc ] = g = CreateGadgetA((ULONG)BlankerGTypes[ lc ], g, &ng, ( struct TagItem * )&BlankerGTags[ tc ] );

		while( BlankerGTags[ tc ] ) tc += 2;
		tc++;

		if ( NOT g )
			return( 2L );
	}

	if ( ! ( BlankerWnd = OpenWindowTags( NULL,
				WA_Left,	wleft,
				WA_Top,		wtop,
				WA_Width,	ww + OffX + Scr->WBorRight,
				WA_Height,	wh + OffY + Scr->WBorBottom,
				WA_IDCMP,	BUTTONIDCMP|LISTVIEWIDCMP|IDCMP_MENUPICK|IDCMP_CLOSEWINDOW|IDCMP_VANILLAKEY|IDCMP_REFRESHWINDOW,
				WA_Flags,	WFLG_DRAGBAR|WFLG_DEPTHGADGET|WFLG_CLOSEGADGET|WFLG_SIZEBBOTTOM|WFLG_SMART_REFRESH|WFLG_ACTIVATE|WFLG_RMBTRAP,
				WA_Gadgets,	BlankerGList,
				WA_Title,	BlankerWdt,
				WA_ScreenTitle,	"Garshneblanker",
				WA_PubScreen,	Scr,
				TAG_DONE )))
	return( 4L );

	GT_RefreshWindow( BlankerWnd, NULL );

	return( 0L );
}