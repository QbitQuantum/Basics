static void  Usage( void )
/************************/
{
    char const  **list;
    char const  *p;
    int         lines_printed;
    unsigned int i, n;
    auto        char buf[82];
#ifndef __UNIX__
    int const   paging = isatty( fileno( stdout ) );
    int const   height = 24; /* Number of lines assumed on screen */
#endif

    print_banner();
    lines_printed = 4;
    list = EnglishHelp;
    while( *list ) {
        memset( buf, ' ', 80 );
        if( **list == '[' ) {                   /* title to be centered */
            i = strlen( *list );
            strcpy( &buf[38 - i / 2], *list );
            ++list;
            for( n = 0; list[n]; ++n ) {        /* count number in list */
                if( *list[n] == '[' ) {
                    break;
                }
            }
            n = (n + 1) / 2;                    /* half way through list */
#ifndef __UNIX__
            if( paging && lines_printed != 0 && lines_printed >= height ) {
                fputs( WclMsgs[PRESS_ANY_KEY_TO_CONTINUE], stdout );
                fflush( stdout );
                getch();
                puts( "" );
                lines_printed = 0;
            }
#endif
            puts( buf );
            lines_printed++;
            for( ;; ) {
                memset( buf, ' ', 80 );
                p = *list;
                if( p == NULL )
                    break;
                for( i = 0; *p; )
                    buf[i++] = *p++;
                p = list[n];
                if( p != NULL  &&  *p != '[' ) {
                    for( i = 38; *p; ) {
                        buf[i++] = *p++;
                    }
                }
                buf[i] = '\0';
                puts( buf );
                lines_printed++;
#ifndef __UNIX__
                if( paging && lines_printed != 0 && lines_printed >= height ) {
                    fputs( WclMsgs[PRESS_ANY_KEY_TO_CONTINUE], stdout );
                    fflush( stdout );
                    getch();
                    puts( "" );
                    lines_printed = 0;
                }
#endif
                p = list[n];
                if( p == NULL )
                    break;
                if( *p == '[' )
                    break;
                list[n] = NULL; /* indicate already printed */
                ++list;
            }
            list = &list[n];
        } else {
            puts( *list );
            lines_printed++;
            ++list;
        }
    }
}