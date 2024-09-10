uint128_t MasterCM::sync( const uint128_t& version )
{
    EQASSERTINFO( version.high() != 0 || version == VERSION_NEXT ||
                  version == VERSION_HEAD, version );
#if 0
    EQLOG( LOG_OBJECTS ) << "sync to v" << version << ", id " 
                         << _object->getID() << "." << _object->getInstanceID()
                         << std::endl;
#endif

    if( version == VERSION_NEXT )
    {
        ObjectDataIStream* is = _queuedDeltas.pop();
        _apply( is );
        return _version;
    }
    // else
    if( version == VERSION_HEAD )
    {
        ObjectDataIStream* is = 0;
        while( _queuedDeltas.tryPop( is ))
            _apply( is );
        return _version;
    }
    // else apply only concrete slave commit

    ObjectDataIStream* is = 0;
    ObjectDataIStreams unusedStreams;
    while( !is )
    {
        ObjectDataIStream* candidate = _queuedDeltas.pop();
        if( candidate->getVersion() == version )
            is = candidate;
        else
            unusedStreams.push_back( candidate );
    }

    _apply( is );
    _queuedDeltas.pushFront( unusedStreams );
    return version;
}