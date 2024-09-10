int DzSetSockOpt( int fd, int level, int name, const void* option, socklen_t len )
{
    DzHost* host = GetHost();
    assert( host );
    assert( fd >= 0 );
    assert( ( fd & HANDLE_HOST_ID_MASK ) == host->hostId );
    assert( !( level == SOL_SOCKET && name == SO_LINGER ) );

    return SetSockOpt( host, fd, level, name, option, len );
}