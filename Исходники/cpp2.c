ReturnCode control( struct Global *global,
    int *counter )  /* Pending newline counter */
{
    /*
     * Process #control lines.  Simple commands are processed inline,
     * while complex commands have their own subroutines.
     *
     * The counter is used to force out a newline before #line, and
     * #pragma commands.  This prevents these commands from ending up at
     * the end of the previous line if cpp is invoked with the -C option.
     */

    int c;
    char *tp;
    int hash;
    char *ep;
    ReturnCode ret;

    c = skipws( global );

    if( c == '\n' || c == EOF_CHAR )
        {
        (*counter)++;

        return(FPP_OK);
        }

    if( !isdigit(c) )
        scanid( global, c );                  /* Get #word to tokenbuf        */
    else
        {
        unget( global );                    /* Hack -- allow #123 as a      */

        strcpy( global->tokenbuf, "line" );   /* synonym for #line 123        */
        }

    hash = (global->tokenbuf[1] == EOS) ? L_nogood : (global->tokenbuf[0] + (global->tokenbuf[2] << 1));

    switch( hash )
        {
        case L_assert:
            tp = "assert";
            break;
        case L_define:
            tp = "define";
            break;
        case L_elif:
            tp = "elif";
            break;
        case L_else:
            tp = "else";
            break;
        case L_endif:
            tp = "endif";
            break;
        case L_error:
            tp = "error";
            break;
        case L_if:
            tp = "if";
            break;
        case L_ifdef:
            tp = "ifdef";
            break;
        case L_ifndef:
            tp = "ifndef";
            break;
        case L_include:
            tp = "include";
            break;
        case L_line:
            tp = "line";
            break;
        case L_pragma:
            tp = "pragma";
            break;
        case L_undef:
            tp = "undef";
            break;
        default:
            hash = L_nogood;
        case L_nogood:
            tp = "";
            break;
        }

    if( !streq( tp, global->tokenbuf ) )
        hash = L_nogood;

    /*
     * hash is set to a unique value corresponding to the
     * control keyword (or L_nogood if we think it's nonsense).
     */
    if( global->infile->fp == NULL )
        cwarn( global, WARN_CONTROL_LINE_IN_MACRO, global->tokenbuf );

    if( !compiling )
        {                       /* Not compiling now    */
        switch( hash )
            {
            case L_if:              /* These can't turn     */
            case L_ifdef:           /*  compilation on, but */
            case L_ifndef:          /*   we must nest #if's */
                if( ++global->ifptr >= &global->ifstack[BLK_NEST] )
                    {
                    cfatal( global, FATAL_TOO_MANY_NESTINGS, global->tokenbuf );

                    return( FPP_TOO_MANY_NESTED_STATEMENTS );
                    }

                *global->ifptr = 0;       /* !WAS_COMPILING   */

            case L_line:            /* Many         */
                /*
                 * Are pragma's always processed?
                 */
            case L_pragma:          /*  options     */
            case L_include:         /*   are uninteresting  */
            case L_define:          /*    if we     */
            case L_undef:           /*     aren't           */
            case L_assert:          /*  compiling.  */
            case L_error:
                dump_line( global, counter );       /* Ignore rest of line  */
                return(FPP_OK);
            }
        }
    /*
     * Make sure that #line and #pragma are output on a fresh line.
     */
    if( *counter > 0 && (hash == L_line || hash == L_pragma) )
        {
        Putchar( global, '\n' );

        (*counter)--;
        }

    switch( hash )
        {
        case L_line:
            /*
             * Parse the line to update the line number and "progname"
             * field and line number for the next input line.
             * Set wrongline to force it out later.
             */
            c = skipws( global );

            global->workp = global->work;       /* Save name in work    */

            while( c != '\n' && c != EOF_CHAR )
                {
                if( (ret = save( global, c )) )
                    return(ret);

                c = get( global );
                }

            unget( global );

            if( (ret = save( global, EOS )) )
                return(ret);

            /*
             * Split #line argument into <line-number> and <name>
             * We subtract 1 as we want the number of the next line.
             */
            global->line = atoi(global->work) - 1;     /* Reset line number    */

            for( tp = global->work; isdigit(*tp) || type[(unsigned)*tp] == SPA; tp++)
                ;             /* Skip over digits */

            if( *tp != EOS )
                {
                /* Got a filename, so:  */

                if( *tp == '"' && (ep = strrchr(tp + 1, '"')) != NULL )
                    {
                    tp++;           /* Skip over left quote */

                    *ep = EOS;      /* And ignore right one */
                    }

                if( global->infile->progname != NULL )
                    /* Give up the old name if it's allocated.   */
                    free( global->infile->progname );

                global->infile->progname = savestring( global, tp );
                }

            global->wrongline = TRUE;           /* Force output later   */
            break;

        case L_include:
            ret = doinclude( global );
            if( ret )
                return(ret);
            break;

        case L_define:
            ret = dodefine( global );
            if( ret )
                return(ret);
            break;

        case L_undef:
            doundef( global );
            break;

        case L_else:
            if( global->ifptr == &global->ifstack[0] )
                {
                cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }
            else if( (*global->ifptr & ELSE_SEEN) != 0 )
                {
                cerror( global, ERROR_STRING_MAY_NOT_FOLLOW_ELSE, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }

            *global->ifptr |= ELSE_SEEN;

            if( (*global->ifptr & WAS_COMPILING) != 0 )
                {
                if( compiling || (*global->ifptr & TRUE_SEEN) != 0 )
                    compiling = FALSE;
                else
                    {
                    compiling = TRUE;
                    }
                }
            break;

        case L_elif:
            if( global->ifptr == &global->ifstack[0] )
                {
                cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }
            else if( (*global->ifptr & ELSE_SEEN) != 0 )
                {
                cerror( global, ERROR_STRING_MAY_NOT_FOLLOW_ELSE, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }

            if( (*global->ifptr & (WAS_COMPILING | TRUE_SEEN)) != WAS_COMPILING )
                {
                compiling = FALSE;        /* Done compiling stuff */

                dump_line( global, counter );   /* Skip this clause */

                return( FPP_OK );
                }

            ret = doif( global, L_if );

            if( ret )
                return(ret);

            break;

        case L_error:
            cerror(global, ERROR_ERROR);
            break;

        case L_if:
        case L_ifdef:
        case L_ifndef:
            if( ++global->ifptr < &global->ifstack[BLK_NEST] )
                {
                *global->ifptr = WAS_COMPILING;

                ret = doif( global, hash );

                if( ret )
                    return(ret);

                break;
                }

            cfatal( global, FATAL_TOO_MANY_NESTINGS, global->tokenbuf );

            return( FPP_TOO_MANY_NESTED_STATEMENTS );

        case L_endif:
            if( global->ifptr == &global->ifstack[0] )
                {
                cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                dump_line( global, counter );

                return(FPP_OK);
                }

            if( !compiling && (*global->ifptr & WAS_COMPILING) != 0 )
                global->wrongline = TRUE;

            compiling = ((*global->ifptr & WAS_COMPILING) != 0);

            --global->ifptr;

            break;

        case L_assert:
            {
            int result;

            ret = eval( global, &result );

            if(ret)
                return(ret);

            if( result == 0 )
                cerror( global, ERROR_PREPROC_FAILURE );
            }
            break;

        case L_pragma:
            /*
             * #pragma is provided to pass "options" to later
             * passes of the compiler.  cpp doesn't have any yet.
             */
            Putstring( global, "#pragma " );

            while( (c = get( global ) ) != '\n' && c != EOF_CHAR )
                Putchar( global, c );

            unget( global );

            Putchar( global, '\n' );

            break;

        default:
            /*
             * Undefined #control keyword.
             * Note: the correct behavior may be to warn and
             * pass the line to a subsequent compiler pass.
             * This would allow #asm or similar extensions.
             */
            if( global->warnillegalcpp )
                cwarn( global, WARN_ILLEGAL_COMMAND, global->tokenbuf );

            Putchar( global, '#' );
            Putstring( global, global->tokenbuf );
            Putchar( global, ' ' );

            while( (c = get( global ) ) != '\n' && c != EOF_CHAR )
                Putchar( global, c );

            unget( global );

            Putchar( global, '\n' );

            break;
        }

    if( hash != L_include )
        {
        #if OLD_PREPROCESSOR
        /*
         * Ignore the rest of the #control line so you can write
         *      #if foo
         *      #endif  foo
         */
        dump_line( global, counter );         /* Take common exit */

        return( FPP_OK );
        #else
          if (skipws(global) != '\n')
            {
            cwarn( global, WARN_UNEXPECTED_TEXT_IGNORED );

            skipnl( global );
            }
        #endif
        }

    (*counter)++;

    return( FPP_OK );
}