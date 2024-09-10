void BufferConnection::sendBuffer( ConnectionPtr connection )
{
    if( _buffer.isEmpty( ))
        return;

    if( !connection )
    {
        EQWARN << "NULL connection during buffer write" << std::endl;
        return;
    }

    EQCHECK( connection->send( _buffer.getData(), _buffer.getSize() ));
    _buffer.setSize( 0 );
}