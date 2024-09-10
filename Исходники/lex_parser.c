static  Token   *savePreviousToken(Token_state *ts, TokensTable *tt)
{
    // save the previous token
    Token *temp_tk = createTokenByLen(ts->begin, ts->cur - ts->begin);
    if(!temp_tk)
    {
        error_process(ts, Error_type_not_enough_mem);
        return NULL;
    }
    else
    {
        if(!addTokenToTable(tt, temp_tk))
        {
            freeToken(temp_tk);
            return NULL;
        }
        else
        {
            ts->state = Lex_state_begin;
            
            cc_skip_space((const char **)&ts->cur);
            ts->begin = ts->cur;
            return temp_tk;
        }
    }
}