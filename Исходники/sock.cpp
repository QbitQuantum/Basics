    void Socket::_handleSendError(int ret, const char* context) {
#ifdef MONGO_SSL
        if (_ssl) {
            LOG(_logLevel) << "SSL Error ret: " << ret
                           << " err: " << _sslManager->SSL_get_error(_ssl , ret)
                           << " "
                           << _sslManager->ERR_error_string(_sslManager->ERR_get_error(), NULL)
                           << endl;
            throw SocketException(SocketException::SEND_ERROR , remoteString());
        }
#endif

#if defined(_WIN32)
        const int mongo_errno = WSAGetLastError();
        if ( mongo_errno == WSAETIMEDOUT && _timeout != 0 ) {
#else
        const int mongo_errno = errno;
        if ( ( mongo_errno == EAGAIN || mongo_errno == EWOULDBLOCK ) && _timeout != 0 ) {
#endif
            LOG(_logLevel) << "Socket " << context << 
                " send() timed out " << remoteString() << endl;
            throw SocketException(SocketException::SEND_TIMEOUT , remoteString());
        }
        else {
            LOG(_logLevel) << "Socket " << context << " send() "
                           << errnoWithDescription(mongo_errno) << ' ' << remoteString() << endl;
            throw SocketException(SocketException::SEND_ERROR , remoteString());            
        }
    }

    void Socket::_handleRecvError(int ret, int len, int* retries) {
        if (ret == 0) {
            LOG(3) << "Socket recv() conn closed? " << remoteString() << endl;
            throw SocketException(SocketException::CLOSED , remoteString());
        }
     
        // ret < 0
#ifdef MONGO_SSL
        if (_ssl) {
            LOG(_logLevel) << "SSL Error ret: " << ret
                           << " err: " << _sslManager->SSL_get_error(_ssl , ret)
                           << " "
                           << _sslManager->ERR_error_string(_sslManager->ERR_get_error(), NULL)
                           << endl;
            throw SocketException(SocketException::RECV_ERROR, remoteString());
        }
#endif

#if defined(_WIN32)
        int e = WSAGetLastError();
#else
        int e = errno;
# if defined(EINTR)
        if (e == EINTR) {
            LOG(_logLevel) << "EINTR retry " << ++*retries << endl;
            return;
        }
# endif
#endif

#if defined(_WIN32)
        // Windows
        if ((e == EAGAIN || e == WSAETIMEDOUT) && _timeout > 0) { 
#else
        if (e == EAGAIN && _timeout > 0) { 
#endif
            // this is a timeout
            LOG(_logLevel) << "Socket recv() timeout  " << remoteString() <<endl;
            throw SocketException(SocketException::RECV_TIMEOUT, remoteString());
        }

        LOG(_logLevel) << "Socket recv() " << 
            errnoWithDescription(e) << " " << remoteString() <<endl;
        throw SocketException(SocketException::RECV_ERROR , remoteString());
    }

    void Socket::setTimeout( double secs ) {
        setSockTimeouts( _fd, secs );
    }

    // TODO: allow modification?
    //
    // <positive value> : secs to wait between stillConnected checks
    // 0 : always check
    // -1 : never check
    const int Socket::errorPollIntervalSecs( 5 );

#if defined(NTDDI_VERSION) && ( !defined(NTDDI_VISTA) || ( NTDDI_VERSION < NTDDI_VISTA ) )
    // Windows XP

    // pre-Vista windows doesn't have WSAPoll, so don't test connections
    bool Socket::isStillConnected() {
        return true;
    }

#else // Not Windows XP

    // Patch to allow better tolerance of flaky network connections that get broken
    // while we aren't looking.
    // TODO: Remove when better async changes come.
    //
    // isStillConnected() polls the socket at max every Socket::errorPollIntervalSecs to determine
    // if any disconnection-type events have happened on the socket.
    bool Socket::isStillConnected() {

        if ( errorPollIntervalSecs < 0 ) return true;

        time_t now = time( 0 );
        time_t idleTimeSecs = now - _lastValidityCheckAtSecs;

        // Only check once every 5 secs
        if ( idleTimeSecs < errorPollIntervalSecs ) return true;
        // Reset our timer, we're checking the connection
        _lastValidityCheckAtSecs = now;

        // It's been long enough, poll to see if our socket is still connected

        pollfd pollInfo;
        pollInfo.fd = _fd;
        // We only care about reading the EOF message on clean close (and errors)
        pollInfo.events = POLLIN;

        // Poll( info[], size, timeout ) - timeout == 0 => nonblocking
#if defined(_WIN32)
        int nEvents = WSAPoll( &pollInfo, 1, 0 );
#else
        int nEvents = ::poll( &pollInfo, 1, 0 );
#endif

        LOG( 2 ) << "polling for status of connection to " << remoteString()
                 << ", " << ( nEvents == 0 ? "no events" :
                              nEvents == -1 ? "error detected" :
                                               "event detected" ) << endl;

        if ( nEvents == 0 ) {
            // No events incoming, return still connected AFAWK
            return true;
        }
        else if ( nEvents < 0 ) {
            // Poll itself failed, this is weird, warn and log errno
            warning() << "Socket poll() failed during connectivity check"
                      << " (idle " << idleTimeSecs << " secs,"
                      << " remote host " << remoteString() << ")"
                      << causedBy(errnoWithDescription()) << endl;

            // Return true since it's not clear that we're disconnected.
            return true;
        }

        dassert( nEvents == 1 );
        dassert( pollInfo.revents > 0 );

        // Return false at this point, some event happened on the socket, but log what the
        // actual event was.

        if ( pollInfo.revents & POLLIN ) {

            // There shouldn't really be any data to recv here, so make sure this
            // is a clean hangup.

            // Used concurrently, but we never actually read this data
            static char testBuf[1];

            int recvd = ::recv( _fd, testBuf, 1, portRecvFlags );

            if ( recvd < 0 ) {
                // An error occurred during recv, warn and log errno
                warning() << "Socket recv() failed during connectivity check"
                          << " (idle " << idleTimeSecs << " secs,"
                          << " remote host " << remoteString() << ")"
                          << causedBy(errnoWithDescription()) << endl;
            }
            else if ( recvd > 0 ) {
                // We got nonzero data from this socket, very weird?
                // Log and warn at runtime, log and abort at devtime
                // TODO: Dump the data to the log somehow?
                error() << "Socket found pending data during connectivity check"
                        << " (idle " << idleTimeSecs << " secs,"
                        << " remote host " << remoteString() << ")" << endl;
                dassert( false );
            }
            else {
                // recvd == 0, socket closed remotely, just return false
                LOG( 0 ) << "Socket closed remotely, no longer connected"
                         << " (idle " << idleTimeSecs << " secs,"
                         << " remote host " << remoteString() << ")" << endl;
            }
        }
        else if ( pollInfo.revents & POLLHUP ) {
            // A hangup has occurred on this socket
            LOG( 0 ) << "Socket hangup detected, no longer connected" << " (idle "
                         << idleTimeSecs << " secs," << " remote host " << remoteString() << ")"
                         << endl;
        }
        else if ( pollInfo.revents & POLLERR ) {
            // An error has occurred on this socket
            LOG( 0 ) << "Socket error detected, no longer connected" << " (idle "
                         << idleTimeSecs << " secs," << " remote host " << remoteString() << ")"
                         << endl;
        }
        else if ( pollInfo.revents & POLLNVAL ) {
            // Socket descriptor itself is weird
            // Log and warn at runtime, log and abort at devtime
            error() << "Socket descriptor detected as invalid"
                    << " (idle " << idleTimeSecs << " secs,"
                    << " remote host " << remoteString() << ")" << endl;
            dassert( false );
        }
        else {
            // Don't know what poll is saying here
            // Log and warn at runtime, log and abort at devtime
            error() << "Socket had unknown event (" << static_cast<int>(pollInfo.revents) << ")"
                    << " (idle " << idleTimeSecs << " secs,"
                    << " remote host " << remoteString() << ")" << endl;
            dassert( false );
        }

        return false;
    }

#endif // End Not Windows XP

#if defined(_WIN32)
    struct WinsockInit {
        WinsockInit() {
            WSADATA d;
            if ( WSAStartup(MAKEWORD(2,2), &d) != 0 ) {
                out() << "ERROR: wsastartup failed " << errnoWithDescription() << endl;
                problem() << "ERROR: wsastartup failed " << errnoWithDescription() << endl;
                _exit(EXIT_NTSERVICE_ERROR);
            }
        }
    } winsock_init;
#endif

} // namespace mongo