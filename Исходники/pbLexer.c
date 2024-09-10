// state machine based lexer
// tokens are recorded in 'tokens', ended by a NONE token
bool lex( char * line, const bool mode ) {
	char * start = NULL, *end = NULL, *s = line ;
	char term[ 256 ], *pterm = NULL ;
	LexState state = lsInit ;

	// state machine
	for ( ptok = tokens ; ptok < &tokens[ 256 ] ; ) {
		switch ( state ) {
		case lsInit :
			ptok->type = tNONE ;
			ptok->subtype = stNONE ;
			ptok->value = 0 ;
			ptok->text = NULL ;

			pterm = term ;
			*pterm = '\0' ;
			state = lsIdle ;
			break ;

		case lsIdle :
			// starting characters of tokens to be
			if ( *s == '\0' || *s == '\r' || *s == '\n' ) {
				// end of line
				return true ;
			} else if ( *s == ' ' || iscntrl( *s ) ) {
				// white space, 'space' and all control characters, except \0, \r and \n
				s++ ;
			} else if ( mode && ( isalnum( *s ) || *s == '_'  ) ) {
				// KCPSM mode, all alphanum is accepted for idents, could be hex values
				// ident
				start = s++ ;
				state = lsIdent ;
			} else if ( !mode && ( isalpha( *s ) || *s == '_' ) ) {
				// ident
				start = s++ ;
				state = lsIdent ;
			} else if ( *s == ';' ) {
				// comment
				start = s++ ;
				state = lsComment ;
			} else if ( *s == '0' ) {
				// maybe hex or bin
				start = s++ ;
				state = lsHexBin ;
			} else if ( isdigit( *s ) ) {
				// decimal number
				start = s++ ;
				state = lsDec ;
			} else if ( *s == '$' ) {
				// hexadecimal number
				start = ++s ;
				state = lsHex ;
			} else if ( *s == '%' ) {
				// binary number
				start = ++s ;
				state = lsBin ;
			} else if ( *s == '.' ) {
				// directives, indexing, local labels, etc
				start = s++ ;
				state = lsIndex ;
			} else if ( *s == ':' || *s == ',' || *s == '(' || *s == ')' ) {
				// punctuation ',', ':', '(', ')', '~'
				start = s++ ;
				state = lsPunct ;
			} else if ( *s == '*' || *s == '/' || *s == '#' || *s == '+' || *s == '-' ||
					*s == '|' || *s == '&' || *s == '^' || *s == '~' ) {
				// operators
				start = s++ ;
				state = lsOperator ;
			} else if ( *s == '<' || *s == '>' ) {
				// double char operators
				start = s++ ;
				state = lsDoubleOp ;
			} else if ( *s == '\'' ) {
				// 'c'
				start = ++s ;
				state = lsChar ;
			} else if ( *s == '"' ) {
				// "string"
				start = ++s ;
				state = lsString ;
			} else
				state = lsError ;
			break ;

		case lsComment :
			if ( *s != '\0' && *s != '\r' && *s != '\n' )
				// anything till end of line
				s++ ;
			else {
				end = s ;
				ptok->type = tNONE ;
				ptok->subtype = stCOMMENT ;
				state = lsCopy ;
			}
			break ;

		case lsChar :
			if ( *s == '\'' ) {
				ptok->type = tCHAR ;
				end = s++ ;
				state = lsCopy ;
			} else if ( *s == '\\' ) {
				s += 1 ;
				if ( *s != '\0' )
					s += 1 ;
			} else if ( isgraph( *s ) || *s == ' ' ) {
				s++ ;
			} else
				state = lsError ;
			break ;

		case lsString :
			if ( *s == '"' ) {
				ptok->type = tSTRING ;
				end = s++ ;
				state = lsCopy ;
			} else if ( *s == '\\' ) {
				s += 1 ;
				if ( *s != '\0' )
					s += 1 ;
			} else if ( isgraph( *s ) || *s == ' ' )
				s++ ;
			else
				state = lsError ;
			break ;

		case lsIdent :
			if ( isalnum( *s ) || *s == '_' )
				s++ ;
			else {
				end = s ;
				ptok->type = tIDENT ;
				ptok->subtype = stNONE ;
				state = lsCopy ;
			}
			break ;

		case lsHexBin :
			if ( *s == 'x' ) {
				start = ++s ;
				state = lsHex ;
			} else if ( *s == 'b' ) {
				start = ++s ;
				state = lsBin ;
			} else
				// missing the first '0' doesn't hurt here
				state = lsDec ;
			break ;

		case lsHex :
			if ( isxdigit( *s ) )
				s++ ;
			else {
				end = s ;
				ptok->type = tHEX ;
				state = lsCopy ;
			}
			break ;

		case lsBin :
			if ( *s == '0' || *s == '1' )
				s++ ;
			else {
				end = s ;
				ptok->type = tBIN ;
				state = lsCopy ;
			}
			break ;

		case lsDec :
			if ( isdigit( *s ) )
				s++ ;
			else {
				end = s ;
				ptok->type = tDEC ;
				state = lsCopy ;
			}
			break ;

		case lsOperator :
			ptok->type = tOPERATOR ;
			switch ( *start ) {
			case '*' :
				ptok->subtype = stMUL ;
				break ;
			case '/' :
				ptok->subtype = stDIV ;
				break ;
			case '#' :
				ptok->subtype = stMOD ;
				break ;
			case '+' :
				ptok->subtype = stADD ;
				break ;
			case '-' :
				ptok->subtype = stSUB ;
				break ;
			case '|' :
				ptok->subtype = stIOR ;
				break ;
			case '&' :
				ptok->subtype = stAND ;
				break ;
			case '^' :
				ptok->subtype = stXOR ;
				break ;
			case '~' :
				ptok->subtype = stTILDA ;
				break ;
			}
			end = s ;
			state = lsCopy ;
			break ;

		case lsDoubleOp :
			if ( *start == *s ) { // << or >>
				ptok->type = tOPERATOR ;
				switch ( *start ) {
				case '<' :
					ptok->subtype = stSHL ;
					break ;
				case '>' :
					ptok->subtype = stSHR ;
					break ;
				}
				end = ++s ;
				state = lsCopy ;
			} else
				state = lsError ;
			break ;

		case lsPunct :
			end = s ;
			state = lsCopy ;
			switch ( *start ) {
			case ':' :
				ptok->type = tCOLON ;
				break ;
			case '(' :
				ptok->type = tLPAREN ;
				break ;
			case ')' :
				ptok->type = tRPAREN ;
				break ;
			case ',' :
				ptok->type = tCOMMA ;
				break ;
			default :
				state = lsError ;
			}
			break ;

		case lsIndex :
			// any of .IX, .IX++, .--IX, .-IX+
			if ( isalnum( *s ) || *s == '-' || *s == '+' )
				s++ ;
			else {
				end = s ;
				ptok->type = tIDENT ;
				ptok->subtype = stDOT ;
				state = lsCopy ;
			}
			break ;

			// final token collector
		case lsCopy :
			while ( start < end )
				*pterm++ = *start++ ;
			*pterm = '\0' ;
			ptok->text = strdup( term ) ;
			ptok++ ;
			state = lsInit ;
			break ;

			// any errors
		case lsError :
			*pterm = '\0' ;
			ptok->type = tERROR ;
			return false ;
		}
	}
	return false ;
}