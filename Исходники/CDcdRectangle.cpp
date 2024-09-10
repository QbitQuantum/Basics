// ********************************
//	IfDcDraw
// ********************************
bool CDcdRectangle::DcDraw( IfDcdTarget* pIfDcdTarget ) 
{
	int		iRv = 0 ;
	bool	bRv = false ;
	

	// --------------------------------
	//	ペン・ブラシの生成
	// --------------------------------
	HPEN	hPen = NULL ;
	if ( iRv >= 0 ){
		hPen = pIfDcdTarget->CreatePen( m_CdPenProp ) ;
		if ( hPen == NULL ){
			iRv = -1 ;	//	ペンの作成に失敗しました。	\n
		}
	}
	HBRUSH	hBrush = NULL ;
	if ( iRv >= 0 ){
		hBrush = pIfDcdTarget->CreateBrush( m_CdBrushProp ) ;
		if ( hBrush == NULL ){
			iRv = -2 ;	//	ブラシの作成に失敗しました。	\n
		}
	}
	HBRUSH		hBrushSid = NULL ;
	if ( iRv >= 0 ){
		hBrushSid = (HBRUSH)SelectObject( pIfDcdTarget->getHdc() , hBrush ) ;
	}
	HPEN		hPenSid = NULL ;
	if ( iRv >= 0 ){
		hPenSid = (HPEN)SelectObject( pIfDcdTarget->getHdc() , hPen ) ;
	}
	int iBkModeSid = -1 ;
	if ( iRv >= 0 ){
		 iBkModeSid = SetBkMode( pIfDcdTarget->getHdc() , TRANSPARENT ) ;
	}
	// --------------------------------
	if ( iRv >= 0 ){
		CdDcdZoneXy	aCdDcdZoneXy = pIfDcdTarget->getZone() ;
		RECT	LRect ;
		LRect.left   = aCdDcdZoneXy.getX().getPos() + 
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		LRect.top    = aCdDcdZoneXy.getY().getPos() +
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		LRect.right  = aCdDcdZoneXy.getX().getEndPos() -
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		LRect.bottom = aCdDcdZoneXy.getY().getEndPos() -
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		
		Rectangle( pIfDcdTarget->getHdc() , 
			LRect.left , LRect.top , LRect.right , LRect.bottom ) ;
		
	}
	if ( iRv >= 0 ){
		bRv = true ;
	}
	// --------------------------------
	if ( iBkModeSid != -1 ) {
		SetBkMode( pIfDcdTarget->getHdc() , iBkModeSid ) ;
	}
	if ( hBrushSid != NULL ){
		SelectObject( pIfDcdTarget->getHdc() , hBrushSid ) ;
		hBrushSid = NULL ;
	}
	if ( hPenSid != NULL ){
		SelectObject( pIfDcdTarget->getHdc() , hPenSid ) ;
		hPenSid = NULL ;
	}
	return ( bRv ) ;
}