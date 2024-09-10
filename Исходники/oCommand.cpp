void OCommand::sendData( const void* buffer, const uint64_t size,
                         const bool last )
{
    LBASSERT( !_impl->dispatcher );
    LBASSERT( last );
    LBASSERTINFO( size >= 16, size );
    LBASSERT( getBuffer().getData() == buffer );
    LBASSERT( getBuffer().getSize() == size );
    LBASSERT( getBuffer().getMaxSize() >= COMMAND_MINSIZE );

    // Update size field
    uint8_t* bytes = getBuffer().getData();
    reinterpret_cast< uint64_t* >( bytes )[ 0 ] = _impl->size + size;
    const uint64_t sendSize = _impl->isLocked ? size : LB_MAX( size,
                                                               COMMAND_MINSIZE);
    const Connections& connections = getConnections();
    for( ConnectionsCIter i = connections.begin(); i != connections.end(); ++i )
    {
        ConnectionPtr connection = *i;
        connection->send( bytes, sendSize, _impl->isLocked );
    }
}