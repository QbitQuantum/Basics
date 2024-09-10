void StaticSlaveCM::addInstanceDatas( const ObjectDataIStreamDeque& cache,
                                      const uint128_t& /* start */ )
{
    LB_TS_THREAD( _rcvThread );
    LBASSERT( _currentIStream );
    LBASSERT( _currentIStream->getDataSize() == 0 );
    LBASSERT( cache.size() == 1 );
    if( cache.empty( ))
        return;

    ObjectDataIStream* stream = cache.front();
    LBASSERT( stream );
    LBASSERT( stream->isReady( ));
    LBASSERT( stream->getVersion() == VERSION_FIRST );

    if( !stream->isReady() || stream->getVersion() != VERSION_FIRST )
        return;

    LBLOG( LOG_OBJECTS ) << "Adding cached instance data" << std::endl;
    delete _currentIStream;
    _currentIStream = new ObjectDataIStream( *stream );
}