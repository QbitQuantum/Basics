// caller: application
bool UDTConnection::connect( )
{
    struct sockaddr address;
    CCC *cc = NULL;
    int len;

    ConstConnectionDescriptionPtr description = getDescription();
    LBASSERT( CONNECTIONTYPE_UDT == description->type );
    if( !isClosed( ))
        return false;

    _setState( STATE_CONNECTING );

    if( !_parseAddress( description, address, false ))
        goto err;

    LBASSERT( UDT::INVALID_SOCK == _udt );
    _udt = UDT::socket( AF_INET, SOCK_STREAM, 0 );
    if( UDT::INVALID_SOCK == _udt )
    {
        LBERROR << UDTLASTERROR( "UDT::socket" ) << std::endl;
        goto err;
    }

    if( !tuneSocket( ))
        goto err;

    if( UDT::ERROR == UDT::connect( _udt, &address, sizeof( address )))
    {
        LBERROR << UDTLASTERROR( "UDT::connect" ) << std::endl;
        goto err;
    }

    // Do this after connect, otherwise connect itself becomes non-blocking
    static const bool OFF = false;
    if( !setSockOpt( UDT_RCVSYN,
        static_cast<const void *>( &OFF ), sizeof(OFF) ))
        goto err;

    if( UDT::ERROR != UDT::getsockopt( _udt, 0, UDT_CC, &cc, &len ))
    {
        if( NULL != cc )
        {
            CUDPBlast *ccblast = dynamic_cast<CUDPBlast *>( cc );
            if( NULL != ccblast )
                ccblast->setRate( description->bandwidth / 1000. );
        }
    }

    if( initialize( ))
    {
        _setState( STATE_CONNECTED );
        return true;
    }
err:
    return false;
}