/*****************************************************************************

    SetupSession

*****************************************************************************/
APIERR SetupSession( const TCHAR * pszServer )
{
    APIERR           err;
    WKSTA_INFO_100 * pwki100       = NULL;

    //
    //  Connect to the target server.
    //

    err = SetupNullSession( pszServer );

    if( err == NERR_Success ) //  NULL session established.
    {
        BOOL fIsDownlevel = FALSE;

        //
        //  Determine target type.
        //

        err = NetWkstaGetInfo( (LPTSTR)pszServer,
                               100,
                               (LPBYTE *)&pwki100 );

        if( ( err == ERROR_ACCESS_DENIED ) ||
                ( ( err == NERR_Success ) &&
                  ( pwki100->wki100_platform_id == SV_PLATFORM_ID_OS2 ) ) )
        {
            //
            //  The target is downlevel.
            //

            fIsDownlevel = TRUE;
        }

        if( ( err != NERR_Success ) || fIsDownlevel )
        {
            //
            //  Either we cannot talk to the server, or it's
            //  downelevel, so blow away the NULL session.
            //

            DestroySession( pszServer );
        }

        if( fIsDownlevel )
        {
            //
            //  It's a downlevel server.  There aren't many useful
            //  API we can remote to a downlevel server over a NULL
            //  session, (and we just blew away the NULL session
            //  anyway) so try a "normal" session.
            //

            err = SetupNormalSession( pszServer );
        }

        if( pwki100 != NULL )
        {
            NetApiBufferFree( (LPVOID)pwki100 );
        }
    }

    return(err);
}