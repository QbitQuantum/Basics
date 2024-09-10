static int GetNextInputChar( prompt_slot slot )
/*********************************************/
{
    int     c;

    c = ReadNextChar( slot );
    /* Redirect input to a response file; cannot be nested. */
    if( c == '@' && !is_quoting ) {
        if( CmdFile->how == COMMANDLINE || CmdFile->how == INTERACTIVE ) {
            char    fname[LINE_BUF_SIZE];
            int     oi;

            for( oi = 0; oi < sizeof( fname ) - 1; ) {
                c = ReadNextChar( slot );
                if( c == '"' )
                    is_quoting ^= true;
                /* Quit loop if not a valid filename character. */
                if( (!is_quoting && (c == ',' || c == '+' || c == ';' || c == ' ')) ||
                    c == '/' || c < ' ' )
                    break;
                if( c != '"' ) {
                    fname[oi++] = c;
                }
            }
            fname[oi] = '\0';
            if( c > ' ' )
                --CmdFile->current;

            /* Open the response file and read next character. */
            StartNewFile( StrDup( fname ) );
            c = ReadNextChar( slot );
        }
    }
    return( c );
}