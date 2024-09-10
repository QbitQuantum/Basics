_WCRTLINK int __F_NAME(execvp,_wexecvp)( const CHAR_TYPE *file, const CHAR_TYPE * const *argv )
    {
        #ifdef __WIDECHAR__
            if( _RWD_wenviron == NULL )  __create_wide_environment();
            return( _wexecvpe( file, argv, (const CHAR_TYPE **)_RWD_wenviron ) );
        #else
            #ifdef __RDOS__
                return( execv( file, argv ) );
            #else
                return( execvpe( file, argv, (const CHAR_TYPE **)_RWD_environ ) );
            #endif                
        #endif
    }