bool SessionManager::rotateTo( std::string addr, bool audio )
{
    lockSessions();

    int numSessions = availableVideoSessions->numObjects();
    int lastRotatePos = rotatePos;
    if ( lastRotatePos != -1 )
        lastRotateSession =
            dynamic_cast<SessionEntry*>( (*availableVideoSessions)[ rotatePos ] );
    if ( numSessions == 0 )
    {
        unlockSessions();
        return false;
    }

    SessionEntry* current;

    // if arg is an empty string, just rotate to next. otherwise, figure out
    // rotate pos of string arg
    if ( addr.compare( "" ) == 0 )
    {
        if ( ++rotatePos >= numSessions )
        {
            rotatePos = 0;
        }
        current =
            dynamic_cast<SessionEntry*>( (*availableVideoSessions)[ rotatePos ] );
    }
    else
    {
        current = findSessionByAddress( addr, AVAILABLEVIDEOSESSION );

        if ( current != NULL )
        {
            rotatePos = indexOf( current );
        }
    }

    if ( current == NULL )
    {
        gravUtil::logWarning( "SessionManager::rotateTo: session %s"
                              " not found\n", addr.c_str() );
        unlockSessions();
        return false;
    }

    // only rotate if there is a valid old one & it isn't the same as
    // current
    if ( lastRotateSession != NULL && current != NULL &&
            lastRotateSession != current )
    {
        disableSession( lastRotateSession );
        initSession( current );
    }
    // case for first rotate
    else if ( lastRotatePos == -1 )
    {
        initSession( current );
    }

    unlockSessions();

    return true;
}