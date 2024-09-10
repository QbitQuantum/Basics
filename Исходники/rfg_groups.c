int RFG_Groups_readDefFile( RFG_Groups* groups )
{
    FILE*    f;
    char*    line;
    uint32_t lineno = 0;
    uint8_t  parse_err = 0;

    if( !groups )
        return 0;

    if( !groups->file_name )
        return 1;

    /* open group definition file */

    f = fopen( groups->file_name, "r" );
    if( !f )
    {
        fprintf( stderr,
                 "RFG_Groups_readDefFile(): Error: Could not open file '%s'\n",
                 groups->file_name );
        return 0;
    }

    line = ( char* )malloc( MAX_LINE_LEN * sizeof( char ) );
    if( !line )
    {
        fclose( f );
        return 0;
    }

    /* read lines */

    while( !parse_err && fgets( line, MAX_LINE_LEN, f ) )
    {
        char* group;
        char* p;

        /* increment line number */
        lineno++;

        /* remove newline */
        if( strlen( line ) > 0 && line[strlen(line)-1] == '\n' )
            line[strlen(line)-1] = '\0';

        /* remove leading and trailing spaces from line */
        vt_strtrim( line );

        /* cut possible comment from line */

        p = strchr( line, '#' );
        if( p )
            *p = '\0';

        /* continue if line is empty */
        if( strlen( line ) == 0 )
            continue;

        /* search for '='
           e.g. "GROUP=func1;func2;func3"
                      p
        */

        p = strchr( line, '=' );
        if( !p )
        {
            parse_err = 1;
            break;
        }

        /* cut group name from line
           e.g.   "GROUP=func1;func2;func3"
               => "GROUP"
        */

        *p = '\0';

        group = strdup( line );
        vt_strtrim( group );

        /* split remaining line at ';' to get pattern */

        p = strtok( p+1, ";" );
        do
        {
            char* pattern;

            if( !p )
            {
                parse_err = 1;
                break;
            }

            pattern = strdup( p );
            vt_strtrim( pattern );

            /* add group assignment */

            if( strlen( pattern ) > 0 )
                RFG_Groups_addAssign( groups, group, pattern );

            free( pattern );

        } while( ( p = strtok( 0, ";" ) ) );

        free( group );
    }

    if( parse_err )
    {
        fprintf( stderr, "%s:%u: Could not be parsed\n",
                 groups->file_name, lineno );
    }

    free( line );

    fclose( f );

    return parse_err ? 0 : 1;
}