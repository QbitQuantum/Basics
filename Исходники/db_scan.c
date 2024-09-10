/* NextToken - read the next token */
static int NextToken(ParseContext *c)
{
    int ch, tkn;

    /* skip leading blanks */
    ch = SkipSpaces(c);

    /* remember the start of the current token */
    c->tokenOffset = (int)(c->sys->linePtr - c->sys->lineBuf);

    /* check the next character */
    switch (ch) {
    case EOF:
        tkn = T_EOL;
        break;
    case '"':
        tkn = StringToken(c);
        break;
    case '\'':
        tkn = CharToken(c);
        break;
    case '<':
        if ((ch = GetChar(c)) == '=')
            tkn = T_LE;
        else if (ch == '>')
            tkn = T_NE;
        else if (ch == '<')
            tkn = T_SHL;
        else {
            UngetC(c);
            tkn = '<';
        }
        break;
    case '>':
        if ((ch = GetChar(c)) == '=')
            tkn = T_GE;
        else if (ch == '>')
            tkn = T_SHR;
        else {
            UngetC(c);
            tkn = '>';
        }
        break;
    case '0':
        switch (GetChar(c)) {
        case 'x':
        case 'X':
            tkn = HexNumberToken(c);
            break;
        case 'b':
        case 'B':
            tkn = BinaryNumberToken(c);
            break;
        default:
            UngetC(c);
            tkn = NumberToken(c, '0');
            break;
        }
        break;
    default:
        if (isdigit(ch))
            tkn = NumberToken(c, ch);
        else if (IdentifierCharP(ch)) {
            char *savePtr;
            switch (tkn = IdentifierToken(c,ch)) {
            case T_ELSE:
                savePtr = c->sys->linePtr;
                if ((ch = SkipSpaces(c)) != EOF && IdentifierCharP(ch)) {
                    switch (IdentifierToken(c, ch)) {
                    case T_IF:
                        tkn = T_ELSE_IF;
                        break;
                    default:
                        c->sys->linePtr = savePtr;
                        break;
                    }
                }
                else
                    c->sys->linePtr = savePtr;
                break;
            case T_END:
                savePtr = c->sys->linePtr;
                if ((ch = SkipSpaces(c)) != EOF && IdentifierCharP(ch)) {
                    switch (IdentifierToken(c, ch)) {
                    case T_DEF:
                        tkn = T_END_DEF;
                        break;
                    case T_IF:
                        tkn = T_END_IF;
                        break;
                    default:
                        c->sys->linePtr = savePtr;
                        break;
                    }
                }
                else
                    c->sys->linePtr = savePtr;
                break;
            case T_DO:
                savePtr = c->sys->linePtr;
                if ((ch = SkipSpaces(c)) != EOF && IdentifierCharP(ch)) {
                    switch (IdentifierToken(c, ch)) {
                    case T_WHILE:
                        tkn = T_DO_WHILE;
                        break;
                    case T_UNTIL:
                        tkn = T_DO_UNTIL;
                        break;
                    default:
                        c->sys->linePtr = savePtr;
                        break;
                    }
                }
                else
                    c->sys->linePtr = savePtr;
                break;
            case T_LOOP:
                savePtr = c->sys->linePtr;
                if ((ch = SkipSpaces(c)) != EOF && IdentifierCharP(ch)) {
                    switch (IdentifierToken(c, ch)) {
                    case T_WHILE:
                        tkn = T_LOOP_WHILE;
                        break;
                    case T_UNTIL:
                        tkn = T_LOOP_UNTIL;
                        break;
                    default:
                        c->sys->linePtr = savePtr;
                        break;
                    }
                }
                else
                    c->sys->linePtr = savePtr;
                break;
            }
        }
        else
            tkn = ch;
    }

    /* return the token */
    return tkn;
}