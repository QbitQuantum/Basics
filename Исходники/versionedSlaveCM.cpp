void VersionedSlaveCM::addInstanceDatas( const ObjectDataIStreamDeque& cache,
                                         const uint128_t& startVersion )
{
    LB_TS_THREAD( _rcvThread );
#if 0
    LBLOG( LOG_OBJECTS ) << lunchbox::disableFlush << "Adding data front ";
#endif

    uint128_t oldest = VERSION_NONE;
    uint128_t newest = VERSION_NONE;
    if( !_queuedVersions.isEmpty( ))
    {
        ObjectDataIStream* is = 0;

        LBCHECK( _queuedVersions.getFront( is ));
        oldest = is->getVersion();

        LBCHECK( _queuedVersions.getBack( is ));
        newest = is->getVersion();
    }

    ObjectDataIStreamDeque head;
    ObjectDataIStreams tail;

    for( ObjectDataIStreamDeque::const_iterator i = cache.begin();
         i != cache.end(); ++i )
    {
        ObjectDataIStream* stream = *i;
        const uint128_t& version = stream->getVersion();
        if( version < startVersion )
            continue;
        
        LBASSERT( stream->isReady( ));
        LBASSERT( stream->hasInstanceData( ));
        if( !stream->isReady( ))
            break;

        if( version < oldest )
            head.push_front( stream );
        else if( version > newest )
            tail.push_back( stream );
    }

    for( ObjectDataIStreamDeque::const_iterator i = head.begin();
         i != head.end(); ++i )
    {
        const ObjectDataIStream* stream = *i;
#ifndef NDEBUG
        ObjectDataIStream* debugStream = 0;
        _queuedVersions.getFront( debugStream );
        if( debugStream )
            LBASSERT( debugStream->getVersion() == stream->getVersion() + 1);
#endif
        _queuedVersions.pushFront( new ObjectDataIStream( *stream ));
#if 0
        LBLOG( LOG_OBJECTS ) << stream->getVersion() << ' ';
#endif
    }

#if 0
    LBLOG( LOG_OBJECTS ) << " back ";
#endif
    for( ObjectDataIStreams::const_iterator i = tail.begin();
         i != tail.end(); ++i )
    {
        const ObjectDataIStream* stream = *i;
#ifndef NDEBUG
        ObjectDataIStream* debugStream = 0;
        _queuedVersions.getBack( debugStream );
        if( debugStream )
        {
            LBASSERT( debugStream->getVersion() + 1 == stream->getVersion( ));
        } 
#endif
        _queuedVersions.push( new ObjectDataIStream( *stream ));
#if 0
        LBLOG( LOG_OBJECTS ) << stream->getVersion() << ' ';
#endif
    }
#if 0
    LBLOG( LOG_OBJECTS ) << std::endl << lunchbox::enableFlush;
#endif
}