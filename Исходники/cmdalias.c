void ListAliases( void )
/**********************/
{
    int i;
    char far *alias;
    char        prompt[ 80 ];

    SaveLine();
    SavePrompt( prompt );
    PutNL();
    i = 0;
    alias = AliasList;
    while( *alias != '\0' ) {
        if( *alias == '\n' ) {
            if( ++i == 23 ) {
                PutChar( '\n' );
                if( !PutMore() ) break;
                ++alias;
                i = 0;
                continue;
            }
        }
        PutChar( *alias );
        ++alias;
    }
    RestorePrompt( prompt );
    RestoreLine();
    Draw = TRUE;
}