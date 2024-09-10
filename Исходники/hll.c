static c_bop GetCOp( int * i )
/****************************/
{
    int size = 0;
    c_bop rc;
    char *p = AsmBuffer[*i]->string_ptr;

    if ( AsmBuffer[*i]->token == T_STRING )
        size = AsmBuffer[*i]->value;

    if ( size == 2 ) {
        if ( *p == '=' && *(p+1) == '=' )
            rc = COP_EQ;
        else if ( *p == '!' && *(p+1) == '=' )
            rc = COP_NE;
        else if ( *p == '>' && *(p+1) == '=' )
            rc = COP_GE;
        else if ( *p == '<' && *(p+1) == '=' )
            rc = COP_LE;
        else if ( *p == '&' && *(p+1) == '&' )
            rc = COP_AND;
        else if ( *p == '|' && *(p+1) == '|' )
            rc = COP_OR;
        else
            return( COP_NONE );
    } else if ( size == 1 ) {
        if ( *p == '>' )
            rc = COP_GT;
        else if ( *p == '<' )
            rc = COP_LT;
        else if ( *p == '&' )
            rc = COP_ANDB;
        else if ( *p == '!' )
            rc = COP_NEG;
        else
            return( COP_NONE );
    } else {
        if ( AsmBuffer[*i]->token != T_ID )
            return( COP_NONE );
        /* a valid "flag" string must end with a question mark */
        size = strlen( AsmBuffer[*i]->string_ptr );
        if ( *(p+size-1) != '?' )
            return( COP_NONE );
        if ( size == 5 && ( 0 == _memicmp( p, "ZERO", 4 ) ) )
            rc = COP_ZERO;
        else if ( size == 6 && ( 0 == _memicmp( p, "CARRY", 5 ) ) )
            rc = COP_CARRY;
        else if ( size == 5 && ( 0 == _memicmp( p, "SIGN", 4 ) ) )
            rc = COP_SIGN;
        else if ( size == 7 && ( 0 == _memicmp( p, "PARITY", 6 ) ) )
            rc = COP_PARITY;
        else if ( size == 9 && ( 0 == _memicmp( p, "OVERFLOW", 8 ) ) )
            rc = COP_OVERFLOW;
        else
            return( COP_NONE );
    }
    *i += 1;
    return( rc );
}