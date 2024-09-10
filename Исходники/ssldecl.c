static void ProcTokens( class typ, unsigned *next )
{
    symbol      *sym;
    unsigned    value;

    WantColon();
    do {
        if( CurrToken != T_NAME )
            Error( "expecting name" );
        sym = NewSym( typ );
        Scan();
        switch( typ ) {
        case CLASS_INPUT:
        case CLASS_OUTPUT:
        case CLASS_INOUT:
            if( CurrToken == T_LITERAL ) {
                NewAlias( sym );
                Scan();
            }
        }
        if( CurrToken == T_EQUALS ) {
            Scan();
            value = GetNum();
            Scan();
        } else {
            value = *next;
        }
        sym->v.token = value;
        if( value >= *next ) {
            *next = value + 1;
        }
    } while( CurrToken != T_SEMI );
    Scan();
}