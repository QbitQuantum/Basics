/**
* @brief 
*
* @param writeable
* @param frame
*
* @return 
*/
bool HttpDataStream::sendFrame( Select::CommsList &writeable, FramePtr frame )
{
    const ByteBuffer &packet = frame->buffer();

    for ( Select::CommsList::iterator iter = writeable.begin(); iter != writeable.end(); iter++ )
    {
        if ( TcpInetSocket *socket = dynamic_cast<TcpInetSocket *>(*iter) )
        {
            if ( socket == mConnection->socket() )
            {
                int nBytes = socket->write( packet.data(), packet.size() );
                const FeedFrame *sourceFrame = frame->sourceFrame();
                Debug( 4, "Wrote %d bytes on sd %d, frame %ju<-%ju", nBytes, socket->getWriteDesc(), frame->id(), sourceFrame->id() );
                if ( nBytes != packet.size() )
                {
                    Error( "Incomplete write, %d bytes instead of %zd", nBytes, packet.size() );
                    mStop = true;
                    return( false );
                }
            }
        }
    }
    return( true );
}