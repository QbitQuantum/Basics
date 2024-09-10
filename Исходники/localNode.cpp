bool LocalNode::close() 
{ 
    if( _state != STATE_LISTENING )
        return false;

    NodeStopPacket packet;
    send( packet );

    EQCHECK( _receiverThread->join( ));
    _cleanup();

    EQINFO << _incoming.getSize() << " connections open after close"
           << std::endl;
#ifndef NDEBUG
    const Connections& connections = _incoming.getConnections();
    for( Connections::const_iterator i = connections.begin();
         i != connections.end(); ++i )
    {
        EQINFO << "    " << *i << std::endl;
    }
#endif

    EQASSERTINFO( !hasPendingRequests(),
                  *static_cast< base::RequestHandler* >( this ));
    return true;
}