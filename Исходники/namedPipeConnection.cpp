void NamedPipeConnection::_close()
{
    if( isClosed( ))
        return;

    LBASSERT( _fd > 0 );

    if( isListening( ))
    {
        _exitAIOAccept();

        if( _fd != INVALID_HANDLE_VALUE && !DisconnectNamedPipe( _fd ))
            LBERROR << "Could not disconnect named pipe: " << lunchbox::sysError
                    << std::endl;
    }
    else
    {
        _exitAIORead();
        if( _fd != INVALID_HANDLE_VALUE && !CloseHandle( _fd ))
            LBERROR << "Could not close named pipe: " << lunchbox::sysError
                    << std::endl;
    }

    _fd = INVALID_HANDLE_VALUE;
    _setState( STATE_CLOSED );
}