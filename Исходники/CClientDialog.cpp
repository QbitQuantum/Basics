bool CDialogDef::r_Verb( CScript & s, CTextConsole * pSrc )	// some command on this object as a target
{
	ADDTOCALLSTACK("CDialogDef::r_Verb");
	EXC_TRY("Verb");
	// The first part of the key is GUMPCTL_TYPE
	LPCTSTR pszKey = s.GetKey();

	int index = FindTableSorted( pszKey, sm_szLoadKeys, COUNTOF(sm_szLoadKeys)-1 );
	if ( index < 0 )
	{
		CGString sVal;
		CScriptTriggerArgs Args(s.GetArgRaw());
		if ( r_Call(s.GetKey(), pSrc, &Args, &sVal) )
			return true;
		if (!m_pObj)
			return CResourceLink::r_Verb(s, pSrc);
		return m_pObj->r_Verb(s, pSrc);
	}
	
	LPCTSTR pszArgs	= s.GetArgStr();

	switch( index )
	{
		case GUMPCTL_PAGE:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;

			GET_ABSOLUTE( page );

			if ( page <= 0 )		return true;

			int	iNewPage;
			if ( m_iPage == 0 || page > m_iPage || page == 0 )
				iNewPage	= page;
			else if ( page == m_iPage  )
				iNewPage	= 1;
			else
				iNewPage	= page + 1;	

			m_sControls[m_iControls].Format( "page %d", iNewPage );
			m_iControls++;
			return true;
		}
		case GUMPCTL_BUTTON:			// 7 = X,Y,Down gump,Up gump,pressable(1/0),page,id
		case GUMPCTL_BUTTONTILEART:		// 11 = X,Y,Down gump,Up gump,pressable(1/0),page,id,tileart,hue,X,Y
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( down );
			GET_ABSOLUTE( up );
			GET_ABSOLUTE( press );
			GET_ABSOLUTE( page );
			GET_ABSOLUTE( id );

			int	iNewPage;
			if ( m_iPage == 0 || page > m_iPage || page == 0 )
				iNewPage	= page;
			else if ( page == m_iPage  )
				iNewPage	= 1;
			else
				iNewPage	= page + 1;	

			if (index == GUMPCTL_BUTTON)
				m_sControls[m_iControls].Format( "button %d %d %d %d %d %d %d", x, y, down, up, press, iNewPage, id );
			else
			{
				GET_ABSOLUTE( tileId );
				GET_ABSOLUTE( tileHue );
				GET_ABSOLUTE( tileX );
				GET_ABSOLUTE( tileY );				
				
				m_sControls[m_iControls].Format( "buttontileart %d %d %d %d %d %d %d %d %d %d %d", x, y, down, up, press, iNewPage, id, tileId, tileHue, tileX, tileY );
			}

			m_iControls++;
			return true;
		}
		case GUMPCTL_GUMPPIC:
		{
			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( id );
			SKIP_ALL( pszArgs );

			m_sControls[m_iControls].Format( "gumppic %d %d %d%s%s", x, y, id, *pszArgs ? " hue=" : "", *pszArgs ? pszArgs : "" );
			m_iControls++;
			return true;
		}
		case GUMPCTL_GUMPPICTILED:
		{
			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( sX );
			GET_ABSOLUTE( sY );
			GET_ABSOLUTE( id );

			m_sControls[m_iControls].Format( "gumppictiled %d %d %d %d %d", x, y, sX, sY, id );
			m_iControls++;
			return true;
		}
		case GUMPCTL_RESIZEPIC:
		{
			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( id );
			GET_ABSOLUTE( sX );
			GET_ABSOLUTE( sY );

			m_sControls[m_iControls].Format( "resizepic %d %d %d %d %d", x, y, id, sX, sY );
			m_iControls++;
			return true;
		}
		case GUMPCTL_TILEPIC:
		case GUMPCTL_TILEPICHUE:
		{
			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( id );
			SKIP_ALL( pszArgs );

			// TilePic don't use args, TilePicHue yes :)
			if ( index == GUMPCTL_TILEPIC )
				m_sControls[m_iControls].Format( "tilepic %d %d %d", x, y, id );
			else
				m_sControls[m_iControls].Format( "tilepichue %d %d %d%s%s", x, y, id, *pszArgs ? " " : "", *pszArgs ? pszArgs : "" );

			m_iControls++;
			return true;
		}
		case GUMPCTL_DTEXT:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;
			if ( m_iTexts >= (COUNTOF(m_sText) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( hue );
			SKIP_ALL( pszArgs )
			if ( *pszArgs == '.' )			pszArgs++;

			size_t iText = GumpAddText( *pszArgs ? pszArgs : "" );
			m_sControls[m_iControls].Format( "text %d %d %d %" FMTSIZE_T, x, y, hue, iText );
			m_iControls++;
			return true;
		}
		case GUMPCTL_DCROPPEDTEXT:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;
			if ( m_iTexts >= (COUNTOF(m_sText) - 1) )
				return false;
			
			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( w );
			GET_ABSOLUTE( h );
			GET_ABSOLUTE( hue );
			SKIP_ALL( pszArgs )
			if ( *pszArgs == '.' )			pszArgs++;

			size_t iText = GumpAddText( *pszArgs ? pszArgs : "" );
			m_sControls[m_iControls].Format( "croppedtext %d %d %d %d %d %" FMTSIZE_T, x, y, w, h, hue, iText );
			m_iControls++;
			return true;
		}
		case GUMPCTL_DHTMLGUMP:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;
			if ( m_iTexts >= (COUNTOF(m_sText) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( w );
			GET_ABSOLUTE( h );
			GET_ABSOLUTE( bck );
			GET_ABSOLUTE( options );
			SKIP_ALL( pszArgs )

			size_t iText = GumpAddText( *pszArgs ? pszArgs : "" );
			m_sControls[m_iControls].Format( "htmlgump %d %d %d %d %" FMTSIZE_T " %d %d", x, y, w, h, iText, bck, options );
			m_iControls++;
			return true;
		}
		case GUMPCTL_DTEXTENTRY:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;
			if ( m_iTexts >= (COUNTOF(m_sText) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( w );
			GET_ABSOLUTE( h );
			GET_ABSOLUTE( hue );
			GET_ABSOLUTE( id );
			SKIP_ALL( pszArgs )

			size_t iText = GumpAddText( *pszArgs ? pszArgs : "" );
			m_sControls[m_iControls].Format( "textentry %d %d %d %d %d %d %" FMTSIZE_T, x, y, w, h, hue, id, iText );
			m_iControls++;
			return true;
		}
		case GUMPCTL_DTEXTENTRYLIMITED:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;
			if ( m_iTexts >= (COUNTOF(m_sText) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( w );
			GET_ABSOLUTE( h );
			GET_ABSOLUTE( hue );
			GET_ABSOLUTE( id );
			GET_ABSOLUTE( charLimit );
			SKIP_ALL( pszArgs )

			size_t iText = GumpAddText( *pszArgs ? pszArgs : "" );
			m_sControls[m_iControls].Format( "textentrylimited %d %d %d %d %d %d %" FMTSIZE_T " %d", x, y, w, h, hue, id, iText, charLimit );
			m_iControls++;
			return true;
		}
		case GUMPCTL_CHECKBOX:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( down );
			GET_ABSOLUTE( up );
			GET_ABSOLUTE( state );
			GET_ABSOLUTE( id );

			m_sControls[m_iControls].Format( "checkbox %d %d %d %d %d %d", x, y, down, up, state, id );

			m_iControls++;
			return true;
		}
		case GUMPCTL_RADIO:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( down );
			GET_ABSOLUTE( up );
			GET_ABSOLUTE( state );
			GET_ABSOLUTE( id );

			m_sControls[m_iControls].Format( "radio %d %d %d %d %d %d", x, y, down, up, state, id );

			m_iControls++;
			return true;
		}
		case GUMPCTL_CHECKERTRANS:
		{
			if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
				return false;

			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( width );
			GET_ABSOLUTE( height );

			m_sControls[m_iControls].Format( "checkertrans %d %d %d %d", x, y, width, height );
			m_iControls++;
			return true;
		}
		case GUMPCTL_DORIGIN:
		{
			// GET_RELATIVE( x, m_iOriginX );
			// GET_RELATIVE( y, m_iOriginY );
			// m_iOriginX	= x;
			// m_iOriginY	= y;
			
			SKIP_ALL( pszArgs );
			if ( *pszArgs == '-' && (IsSpace( pszArgs[1] ) || !pszArgs[1]) )		pszArgs++;
			else  if ( *pszArgs == '*' )	m_iOriginX	+= Exp_GetSingle( ++pszArgs );
			else							m_iOriginX	 = Exp_GetSingle( pszArgs );

			SKIP_ALL( pszArgs );
			if ( *pszArgs == '-' && (IsSpace( pszArgs[1] ) || !pszArgs[1]) )		pszArgs++;
			else  if ( *pszArgs == '*' )	m_iOriginY	+= Exp_GetSingle( ++pszArgs );
			else							m_iOriginY	= Exp_GetSingle( pszArgs );
			
			return true;
		}
		case GUMPCTL_NODISPOSE:
			m_bNoDispose = true;
			break;
		case GUMPCTL_CROPPEDTEXT:
		case GUMPCTL_TEXT:
		case GUMPCTL_TEXTENTRY:
		case GUMPCTL_TEXTENTRYLIMITED:
			break;

		case GUMPCTL_XMFHTMLGUMP:		// 7 = x,y,sx,sy, cliloc(1003000) hasBack canScroll
		case GUMPCTL_XMFHTMLGUMPCOLOR: // 7 + color. 
		{
			GET_RELATIVE( x, m_iOriginX );
			GET_RELATIVE( y, m_iOriginY );
			GET_ABSOLUTE( sX );
			GET_ABSOLUTE( sY );
			GET_ABSOLUTE( cliloc );
			GET_ABSOLUTE( hasBack );
			GET_ABSOLUTE( canScroll );
			//SKIP_ALL( pszArgs )

			if ( index == GUMPCTL_XMFHTMLGUMP ) // xmfhtmlgump doesn't use color
				m_sControls[m_iControls].Format( "xmfhtmlgump %d %d %d %d %d %d %d" , x, y, sX, sY, cliloc, hasBack, canScroll );
			else
				m_sControls[m_iControls].Format( "xmfhtmlgumpcolor %d %d %d %d %d %d %d%s%s", x, y, sX, sY, cliloc, hasBack, canScroll, *pszArgs ? " " : "", *pszArgs ? pszArgs : "" );

			m_iControls++;
			return true;
		}
		case GUMPCTL_XMFHTMLTOK: // 9 = x y width height has_background has_scrollbar color cliloc_id @args
		{
			GET_RELATIVE(x, m_iOriginX);
			GET_RELATIVE(y, m_iOriginY);
			GET_ABSOLUTE(sX);
			GET_ABSOLUTE(sY);
			GET_ABSOLUTE(hasBack);
			GET_ABSOLUTE(canScroll);
			GET_ABSOLUTE(color);
			GET_ABSOLUTE(cliloc);
			SKIP_ALL(pszArgs);

			m_sControls[m_iControls].Format("xmfhtmltok %d %d %d %d %d %d %d %d %s", x, y, sX, sY, hasBack, canScroll, color, cliloc, *pszArgs ? pszArgs : "");

			m_iControls++;
			return true;
		}
		default:
			break;
	}

	if ( m_iControls >= (COUNTOF(m_sControls) - 1) )
		return false;

	m_sControls[m_iControls].Format("%s %s", pszKey, pszArgs);
	m_iControls++;
	return true;
	EXC_CATCH;

	EXC_DEBUG_START;
	EXC_ADD_SCRIPTSRC;
	EXC_DEBUG_END;
	return false;
}