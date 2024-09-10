/*
 * Error Messages.
 */
void fgError( const char *fmt, ... )
{
    va_list ap;

    if (fgState.ErrorFunc) {

        va_start( ap, fmt );

        /* call user set error handler here */
        fgState.ErrorFunc(fmt, ap);

        va_end( ap );

    } else {
#ifdef FREEGLUT_PRINT_ERRORS
        va_start( ap, fmt );

        fprintf( stderr, "freeglut ");
        if( fgState.ProgramName )
            fprintf( stderr, "(%s): ", fgState.ProgramName );
        VFPRINTF( stderr, fmt, ap );
        fprintf( stderr, "\n" );

        va_end( ap );
#endif

        if ( fgState.Initialised )
            fgDeinitialize ();

        exit( 1 );
    }
}