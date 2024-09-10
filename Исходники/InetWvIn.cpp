void InetWvIn :: listen( int port, unsigned int nChannels,
                         Stk::StkFormat format, Socket::ProtocolType protocol )
{
    mutex_.lock();

    if ( connected_ ) delete soket_;

    if ( nChannels < 1 ) {
        oStream_ << "InetWvIn()::listen(): the channel argument must be greater than zero.";
        handleError( StkError::FUNCTION_ARGUMENT );
    }

    if ( format == STK_SINT16 ) dataBytes_ = 2;
    else if ( format == STK_SINT32 || format == STK_FLOAT32 ) dataBytes_ = 4;
    else if ( format == STK_FLOAT64 ) dataBytes_ = 8;
    else if ( format == STK_SINT8 ) dataBytes_ = 1;
    else {
        oStream_ << "InetWvIn(): unknown data type specified!";
        handleError( StkError::FUNCTION_ARGUMENT );
    }
    dataType_ = format;

    unsigned long bufferBytes = bufferFrames_ * nBuffers_ * nChannels * dataBytes_;
    if ( bufferBytes > bufferBytes_ ) {
        if ( buffer_) delete [] buffer_;
        buffer_ = (char *) new char[ bufferBytes ];
        bufferBytes_ = bufferBytes;
    }

    data_.resize( bufferFrames_, nChannels );
    lastFrame_.resize( 1, nChannels, 0.0 );

    bufferCounter_ = 0;
    writePoint_ = 0;
    readPoint_ = 0;
    bytesFilled_ = 0;

    if ( protocol == Socket::PROTO_TCP ) {
        TcpServer *socket = new TcpServer( port );
        oStream_ << "InetWvIn:listen(): waiting for TCP connection on port " << socket->port() << " ... ";
        handleError( StkError::STATUS );
        fd_ = socket->accept();
        if ( fd_ < 0) {
            oStream_ << "InetWvIn::listen(): Error accepting TCP connection request!";
            handleError( StkError::PROCESS_SOCKET );
        }
        oStream_ << "InetWvIn::listen(): TCP socket connection made!";
        handleError( StkError::STATUS );
        soket_ = (Socket *) socket;
    }
    else {
        soket_ = new UdpSocket( port );
        fd_ = soket_->id();
    }

    connected_ = true;

    mutex_.unlock();
}