static void parse( Translator *tor )
{
    QString text;
    QString com;
    QString extracomment;

    yyCh = getChar();

    yyTok = getToken();
    while ( yyTok != Tok_Eof ) {
        switch ( yyTok ) {
        case Tok_class:
            yyTok = getToken();
            if(yyTok == Tok_Ident) {
                yyScope.push(new Scope(yyIdent, Scope::Clazz, yyLineNo));
            }
            else {
                yyMsg() << qPrintable(LU::tr("'class' must be followed by a class name.\n"));
                break;
            }
            while (!match(Tok_LeftBrace)) {
                yyTok = getToken();
            }
            break;

        case Tok_tr:
            yyTok = getToken();
            if ( match(Tok_LeftParen) && matchString(text) ) {
                com.clear();
                bool plural = false;

                if ( match(Tok_RightParen) ) {
                    // no comment
                } else if (match(Tok_Comma) && matchStringOrNull(com)) {   //comment
                    if ( match(Tok_RightParen)) {
                        // ok,
                    } else if (match(Tok_Comma)) {
                        plural = true;
                    }
                }
                if (!text.isEmpty())
                    recordMessage(tor, context(), text, com, extracomment, plural);
            }
            break;
        case Tok_translate:
            {
                QString contextOverride;
                yyTok = getToken();
                if ( match(Tok_LeftParen) &&
                     matchString(contextOverride) &&
                     match(Tok_Comma) &&
                     matchString(text) ) {

                    com.clear();
                    bool plural = false;
                    if (!match(Tok_RightParen)) {
                        // look for comment
                        if ( match(Tok_Comma) && matchStringOrNull(com)) {
                            if (!match(Tok_RightParen)) {
                                if (match(Tok_Comma) && matchExpression() && match(Tok_RightParen)) {
                                    plural = true;
                                } else {
                                    break;
                                }
                            }
                        } else {
                            break;
                        }
                    }
                    if (!text.isEmpty())
                        recordMessage(tor, contextOverride, text, com, extracomment, plural);
                }
            }
            break;

        case Tok_Ident:
            yyTok = getToken();
            break;

        case Tok_Comment:
            if (yyComment.startsWith(QLatin1Char(':'))) {
                yyComment.remove(0, 1);
                extracomment.append(yyComment);
            }
            yyTok = getToken();
            break;

        case Tok_RightBrace:
            if ( yyScope.isEmpty() ) {
                yyMsg() << qPrintable(LU::tr("Excess closing brace.\n"));
            }
            else
                delete (yyScope.pop());
            extracomment.clear();
            yyTok = getToken();
            break;

         case Tok_LeftBrace:
            yyScope.push(new Scope(QString(), Scope::Other, yyLineNo));
            yyTok = getToken();
            break;

        case Tok_Semicolon:
            extracomment.clear();
            yyTok = getToken();
            break;

        case Tok_Package:
            yyTok = getToken();
            while(!match(Tok_Semicolon)) {
                switch(yyTok) {
                    case Tok_Ident:
                        yyPackage.append(yyIdent);
                        break;
                    case Tok_Dot:
                        yyPackage.append(QLatin1String("."));
                        break;
                    default:
                         yyMsg() << qPrintable(LU::tr("'package' must be followed by package name.\n"));
                         break;
                }
                yyTok = getToken();
            }
            break;

        default:
            yyTok = getToken();
        }
    }

    if ( !yyScope.isEmpty() )
        yyMsg(yyScope.top()->line) << qPrintable(LU::tr("Unbalanced opening brace.\n"));
    else if ( yyParenDepth != 0 )
        yyMsg(yyParenLineNo) << qPrintable(LU::tr("Unbalanced opening parenthesis.\n"));
}