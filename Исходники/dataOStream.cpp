void DataOStream::disable()
{
    if( !_disable( ))
        return;
    _connections.clear();
}