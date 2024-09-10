static int getToken()
{
    const char tab[] = "abfnrtv";
    const char backTab[] = "\a\b\f\n\r\t\v";
    uint n;

    yyIdentLen = 0;
    yyCommentLen = 0;
    yyStringLen = 0;

    while ( yyCh != EOF ) {
	yyLineNo = yyCurLineNo;

	if ( isalpha(yyCh) || yyCh == '_' ) {
	    do {
		if ( yyIdentLen < sizeof(yyIdent) - 1 )
		    yyIdent[yyIdentLen++] = (char) yyCh;
		yyCh = getChar();
	    } while ( isalnum(yyCh) || yyCh == '_' );
	    yyIdent[yyIdentLen] = '\0';

	    switch ( yyIdent[0] ) {
	    case 'Q':
		if ( strcmp(yyIdent + 1, "_OBJECT") == 0 ) {
		    return Tok_Q_OBJECT;
		} else if ( strcmp(yyIdent + 1, "T_TR_NOOP") == 0 ) {
		    return Tok_tr;
		} else if ( strcmp(yyIdent + 1, "T_TRANSLATE_NOOP") == 0 ) {
		    return Tok_translate;
		}
		break;
	    case 'T':
		// TR() for when all else fails
		if ( qstricmp(yyIdent + 1, "R") == 0 )
		    return Tok_tr;
		break;
	    case 'c':
		if ( strcmp(yyIdent + 1, "lass") == 0 )
		    return Tok_class;
		break;
	    case 'f':
		/*
		  QTranslator::findMessage() has the same parameters as
		  QApplication::translate().
		*/
		if ( strcmp(yyIdent + 1, "indMessage") == 0 )
		    return Tok_translate;
		break;
	    case 'n':
		if ( strcmp(yyIdent + 1, "amespace") == 0 )
		    return Tok_namespace;
		break;
	    case 'r':
		if ( strcmp(yyIdent + 1, "eturn") == 0 )
		    return Tok_return;
		break;
	    case 's':
		if ( strcmp(yyIdent + 1, "truct") == 0 )
		    return Tok_class;
		break;
	    case 't':
		if ( strcmp(yyIdent + 1, "r") == 0 ) {
		    return Tok_tr;
		} else if ( qstrcmp(yyIdent + 1, "rUtf8") == 0 ) {
		    return Tok_trUtf8;
		} else if ( qstrcmp(yyIdent + 1, "ranslate") == 0 ) {
		    return Tok_translate;
		}
	    }
	    return Tok_Ident;
	} else {
	    switch ( yyCh ) {
	    case '#':
		/*
		  Early versions of lupdate complained about
		  unbalanced braces in the following code:

		      #ifdef ALPHA
			  while ( beta ) {
		      #else
			  while ( gamma ) {
		      #endif
			      delta;
			  }

		  The code contains, indeed, two opening braces for
		  one closing brace; yet there's no reason to panic.

		  The solution is to remember yyBraceDepth as it was
		  when #if, #ifdef or #ifndef was met, and to set
		  yyBraceDepth to that value when meeting #elif or
		  #else.
		*/
		do {
		    yyCh = getChar();
		} while ( isspace(yyCh) && yyCh != '\n' );

		switch ( yyCh ) {
		case 'i':
		    yyCh = getChar();
		    if ( yyCh == 'f' ) {
			// if, ifdef, ifndef
			yySavedBraceDepth.push( yyBraceDepth );
                        yySavedParenDepth.push( yyParenDepth );
		    }
		    break;
		case 'e':
		    yyCh = getChar();
		    if ( yyCh == 'l' ) {
			// elif, else
			if ( !yySavedBraceDepth.isEmpty() ) {
			    yyBraceDepth = yySavedBraceDepth.top();
                            yyParenDepth = yySavedParenDepth.top();
			}
		    } else if ( yyCh == 'n' ) {
			// endif
			if ( !yySavedBraceDepth.isEmpty() ) {
			    yySavedBraceDepth.pop();
                            yySavedParenDepth.pop();
			}
		    }
		}
		while ( isalnum(yyCh) || yyCh == '_' )
		    yyCh = getChar();
		break;
	    case '/':
		yyCh = getChar();
		if ( yyCh == '/' ) {
		    do {
			yyCh = getChar();
		    } while ( yyCh != EOF && yyCh != '\n' );
		} else if ( yyCh == '*' ) {
		    bool metAster = FALSE;
		    bool metAsterSlash = FALSE;

		    while ( !metAsterSlash ) {
			yyCh = getChar();
			if ( yyCh == EOF ) {
			    fprintf( stderr,
				     "%s: Unterminated C++ comment starting at"
				     " line %d\n",
				     (const char *) yyFileName, yyLineNo );
			    yyComment[yyCommentLen] = '\0';
			    return Tok_Comment;
			}
			if ( yyCommentLen < sizeof(yyComment) - 1 )
			    yyComment[yyCommentLen++] = (char) yyCh;

			if ( yyCh == '*' )
			    metAster = TRUE;
			else if ( metAster && yyCh == '/' )
			    metAsterSlash = TRUE;
			else
			    metAster = FALSE;
		    }
		    yyCh = getChar();
		    yyCommentLen -= 2;
		    yyComment[yyCommentLen] = '\0';
		    return Tok_Comment;
		}
		break;
	    case '"':
		yyCh = getChar();

		while ( yyCh != EOF && yyCh != '\n' && yyCh != '"' ) {
		    if ( yyCh == '\\' ) {
			yyCh = getChar();

			if ( yyCh == '\n' ) {
			    yyCh = getChar();
			} else if ( yyCh == 'x' ) {
			    QCString hex = "0";

			    yyCh = getChar();
			    while ( isxdigit(yyCh) ) {
				hex += (char) yyCh;
				yyCh = getChar();
			    }
			    sscanf( hex, "%x", &n );
			    if ( yyStringLen < sizeof(yyString) - 1 )
				yyString[yyStringLen++] = (char) n;
			} else if ( yyCh >= '0' && yyCh < '8' ) {
			    QCString oct = "";

			    do {
				oct += (char) yyCh;
				yyCh = getChar();
			    } while ( yyCh >= '0' && yyCh < '8' );
			    sscanf( oct, "%o", &n );
			    if ( yyStringLen < sizeof(yyString) - 1 )
				yyString[yyStringLen++] = (char) n;
			} else {
			    const char *p = strchr( tab, yyCh );
			    if ( yyStringLen < sizeof(yyString) - 1 )
				yyString[yyStringLen++] = ( p == 0 ) ?
					(char) yyCh : backTab[p - tab];
			    yyCh = getChar();
			}
		    } else {
			if ( yyStringLen < sizeof(yyString) - 1 )
			    yyString[yyStringLen++] = (char) yyCh;
			yyCh = getChar();
		    }
		}
		yyString[yyStringLen] = '\0';

		if ( yyCh != '"' )
		    qWarning( "%s:%d: Unterminated C++ string",
			      (const char *) yyFileName, yyLineNo );

		if ( yyCh == EOF ) {
		    return Tok_Eof;
		} else {
		    yyCh = getChar();
		    return Tok_String;
		}
		break;
	    case '-':
		yyCh = getChar();
		if ( yyCh == '>' ) {
		    yyCh = getChar();
		    return Tok_Arrow;
		}
		break;
	    case ':':
		yyCh = getChar();
		if ( yyCh == ':' ) {
		    yyCh = getChar();
		    return Tok_Gulbrandsen;
		}
		return Tok_Colon;
	    case '\'':
		yyCh = getChar();
		if ( yyCh == '\\' )
		    yyCh = getChar();

		do {
		    yyCh = getChar();
		} while ( yyCh != EOF && yyCh != '\'' );
		yyCh = getChar();
		break;
	    case '{':
                if (yyBraceDepth == 0)
		    yyBraceLineNo = yyCurLineNo;
		yyBraceDepth++;
		yyCh = getChar();
		return Tok_LeftBrace;
	    case '}':
                if (yyBraceDepth == 0)
		    yyBraceLineNo = yyCurLineNo;
		yyBraceDepth--;
		yyCh = getChar();
		return Tok_RightBrace;
	    case '(':
                if (yyParenDepth == 0)
		    yyParenLineNo = yyCurLineNo;
		yyParenDepth++;
		yyCh = getChar();
		return Tok_LeftParen;
	    case ')':
		if (yyParenDepth == 0)
		    yyParenLineNo = yyCurLineNo;
		yyParenDepth--;
		yyCh = getChar();
		return Tok_RightParen;
	    case ',':
		yyCh = getChar();
		return Tok_Comma;
	    case ';':
		yyCh = getChar();
		return Tok_Semicolon;
	    default:
		yyCh = getChar();
	    }
	}
    }
    return Tok_Eof;
}