/* ParseStatement - parse a statement */
void ParseStatement(ParseContext *c, Token tkn)
{
    /* dispatch on the statement keyword */
    switch (tkn) {
    case T_REM:
        /* just a comment so ignore the rest of the line */
        break;
    case T_DEF:
        ParseDef(c);
        break;
    case T_END_DEF:
        ParseEndDef(c);
        break;
    case T_DIM:
        ParseDim(c);
        break;
    case T_LET:
        ParseLet(c);
        break;
    case T_IF:
        ParseIf(c);
        break;
    case T_ELSE:
        ParseElse(c);
        break;
    case T_ELSE_IF:
        ParseElseIf(c);
        break;
    case T_END_IF:
        ParseEndIf(c);
        break;
    case T_END:
        ParseEnd(c);
        break;
    case T_FOR:
        ParseFor(c);
        break;
    case T_NEXT:
        ParseNext(c);
        break;
    case T_DO:
        ParseDo(c);
        break;
    case T_DO_WHILE:
        ParseDoWhile(c);
        break;
    case T_DO_UNTIL:
        ParseDoUntil(c);
        break;
    case T_LOOP:
        ParseLoop(c);
        break;
    case T_LOOP_WHILE:
        ParseLoopWhile(c);
        break;
    case T_LOOP_UNTIL:
        ParseLoopUntil(c);
        break;
    case T_STOP:
        ParseStop(c);
        break;
    case T_GOTO:
        ParseGoto(c);
        break;
    case T_RETURN:
        ParseReturn(c);
        break;
    case T_PRINT:
        ParsePrint(c);
        break;
    case T_IDENTIFIER:
        if (SkipSpaces(c) == ':') {
            DefineLabel(c, c->token, codeaddr(c));
            break;
        }
        UngetC(c);
    default:
        SaveToken(c, tkn);
        ParseImpliedLetOrFunctionCall(c);
        break;
    }
}