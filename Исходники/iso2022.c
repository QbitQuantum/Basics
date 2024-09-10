public void DecodeISO2022( state_t *state, byte codingSystem )
{
  int region;
  byte charset, ch, rch;
  byte c[ ICHAR_WIDTH ];

  for( ; ; ){
    GetChar( ch );
    if( ch < SP ){
      if( ESC == ch ){
	if( FALSE == DecodeEscape( state ) )
	  break;
      } else if( HT == ch )
	DecodeAddTab( state->attr );
      else if( SO == ch )	/* LS1 for 8bit */
	state->gset[ GL ] = G1;
      else if( SI == ch )	/* LS0 for 8bit */
	state->gset[ GL ] = G0;
      else if( BS == ch )
	DecodeAddBs();
      else if( EM == ch )
	state->sset = G2;
      else
	DecodeAddControl( ch );
    } else {
      if( '~' == ch && TRUE == hz_detection ){
	switch( STR[ SIDX ] ){
	case '~':
	  if( ASCII == state->cset[ G0 ] )
	    IncStringIndex();
	  break;	/* break for '~' itself.*/
	case '{':
	  if( ASCII == state->cset[ G0 ] ){
	    IncStringIndex();
	    state->cset[ G0 ] = GB2312;
	    continue;
	  }
	  break;
	case '}':
	  if( GB2312 == state->cset[ G0 ] ){
	    IncStringIndex();
	    state->cset[ G0 ] = ASCII;
	    continue;
	  }
	  break;
	}
      }
      rch = ch;
      if( 0 != state->sset ){
	/*
	 * single shifted character
	 */
	if( EUC_TAIWAN == codingSystem && G2 == state->sset ){
	  charset = CNS_1 + ( ch - 0xa1 );
	  if( charset < CNS_1 || charset > CNS_7 ){
	    state->sset = 0;
	    continue;
	  }
	  GetChar( ch );
	} else {
	  charset = SSET;
	}
	state->sset = 0;
	ch &= 0x7f;	/* for EUC */
	if( !IsGraphicChar( charset, ch ) ){
	  if( SP == ch ){
	    DecodeAddSpace( state->attr );
	  } else {
	    DecodeAddControl( rch );
	  }
	  continue;
	}
	c[ 0 ] = ch;
	if( TRUE == iTable[ (int)charset ].multi ){
	  GetChar( ch );
	  if( !IsGraphicChar( charset, ch & 0x7f ) ){
	    DecodeAddControl( rch );
	    DecodeAddControl( ch );
	    continue;
	  }
	  c[ 1 ] = ch & 0x7f;	/* for EUC */
	}
      } else {
	if( 0x80 & ch ){
	  if( SS2 == ch ){
	    state->sset = G2;
	    continue;
	  } else if( SS3 == ch ){
	    state->sset = G3;
	    continue;
	  }
	  region = GR;
	  ch &= 0x7f;
	} else {
	  region = GL;
	}
	charset = CSET( region );
	if( !IsGraphicChar( charset, ch ) ){
	  if( SP == ch ){
	    DecodeAddSpace( state->attr );
	  } else {
	    DecodeAddControl( rch );
	  }
	  continue;
	}
	c[ 0 ] = ch;
	if( TRUE == iTable[ (int)charset ].multi ){
	  GetChar( ch );
	  ch &= 0x7f;
	  if( !IsGraphicChar( charset, ch ) )
	    continue;
	  c[ 1 ] = ch;
	}
      }
      DecodeAddChar( charset, c, state->attr );
    }
  }
}