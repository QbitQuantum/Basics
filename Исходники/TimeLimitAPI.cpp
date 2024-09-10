//-------------------------------------------------------------------------------------
// Name: TimeLimitGetTimeRemaining()
//-------------------------------------------------------------------------------------
HRESULT TimeLimitGetTimeRemaining( TimeRemaining* pTime )
{
    if( 0 == pTime )
        return E_INVALIDARG;

    // zero out the structure
    ZeroMemory( pTime, sizeof( TimeRemaining ) );

    // Initialize the com subsystem
    HRESULT hr = Init();
    if( SUCCEEDED( hr ) )
    {
        tm tmStruct = { 0 };
        time_t ltTime;
        time( &ltTime );

#ifdef __STDC_SECURE_LIB__
        // Make use of the secure CRT functions
#if defined(_AMD64_)
        if( 0 != _localtime64_s( &tmStruct, &ltTime ) )
#else
		__time32_t t32;
		if( 0 != _localtime32_s( &tmStruct, &t32 ) )
#endif
        {
            hr = E_FAIL;
        }
#else
        // Secure CRT functions are not available.
        const tm* pTM = localtime( &ltTime );
        if( 0 == pTM )
        {
            tmStruct = *pTM;
        }
        else
        {
            hr = E_FAIL;
        }
#endif
        if( SUCCEEDED( hr ) )
        {
            HourlyRestrictions restrictions;
            hr = TimeLimitGetHourlyRestrictions( &restrictions );
            if( SUCCEEDED( hr ) )
            {
                BOOL logout = FALSE;
                int hours = 0;
                int d = tmStruct.tm_wday;
                int h = tmStruct.tm_hour;
                while( FALSE == logout && hours < ( 7 * 24 ) )
                {
                    if( restrictions.days[d] & ( 1 << h ) )
                    {
                        // this hour is allowed
                        ++hours;
                        ++h;
                        if( h == 24 )   // next day, reset hour index and increment day index
                        {
                            h = 0;
                            ++d;
                            if( d == 7 )    // end of week, reset day index to Sunday
                            {
                                d = 0;
                            }
                        }
                    }
                    else
                    {
                        // this hour is not allowed, we're done
                        logout = TRUE;
                    }
                }

                // assuming we didn't scan the whole week (if we did, there are no
                // blocked hours), calculate the exact hours, minutes, and seconds
                // left before logout.
                if( hours < ( 7 * 24 ) )
                {
                    int minutes = tmStruct.tm_min;
                    int seconds = tmStruct.tm_sec;
                    if( seconds > 0 )
                    {
                        // if seconds are greater than zero, then we need to account
                        // the partial minute represented by the seconds component
                        ++minutes;
                    }
                    if( minutes > 0 )
                    {
                        // if minutes are greater than zero, then we need to account
                        // for the partial hour represented by the minutes, since
                        // we've counted the hours (rather than subtracting the
                        // current hour from some fixed amount) we subtract rather
                        // than add, as we did for minutes.
                        --hours;
                    }
                    // we're subtracting the current minutes and seconds from 60 to
                    // get the time left until the beginning of the next whole hour
                    // if minutes or seconds are zero, we make them 60 so that
                    // subtraction turns up 00, as it should.
                    if( 0 == minutes )
                    {
                        minutes = 60;
                    }
                    if( 0 == seconds )
                    {
                        seconds = 60;
                    }
                    if( hours >= 0 )
                    {
                        pTime->days = static_cast<unsigned char>( hours / 24 );
                        pTime->hours = static_cast<unsigned char>( hours % 24 );
                        pTime->minutes = static_cast<unsigned char>( 60 - minutes );
                        pTime->seconds = static_cast<unsigned char>( 60 - seconds );
                    }
                    else
                    {
                        // at this point, if the hour count is negative, then
                        // the user has no time remaining.
                        pTime->days = 0;
                        pTime->hours = 0;
                        pTime->minutes = 0;
                        pTime->seconds = 0;
                    }
                }
                else
                {
                    // scanned the whole week and no blocked hours wer found
                    hr = S_FALSE;
                }
            }
        }
    }
    return hr;
}