///////////////////////////////////////////////////////////////////////////
//  <summary>
//  This method writes data from the given buffer to the underlying stream.
//  It can block or not, depending on the value of the blocking parameter.
//  </summary>
//
//  <param name = "buffer">
//  The buffer that contains the data to be written.
//  </param>
//
//  <param name = "size">
//  The size of the buffer in bytes of the buffer.
//  </param>
//
//  <param name = "blocking">
//  True if the write request should block;  false otherwise.
//  </param>
//
//  <param name = "bytesWritten">
//  An out parameter that will contain the number of bytes that have been
//  written to the stream.
//  </param>
//
//  <returns>
//  Returns a MgStreamStatus value indicating the status of the operation.
//  </returns>
MgStreamHelper::MgStreamStatus MgAceStreamHelper::WriteData(void* buffer,
    size_t size, bool blocking, size_t* bytesWritten)
{
    // Do not attempt writing zero byte to the socket as this could be problematic.
    if (0 == size)
    {
        return MgStreamHelper::mssDone;
    }

    ACE_ASSERT( buffer && size > 0 );
    MgStreamHelper::MgStreamStatus stat = MgStreamHelper::mssError;

    //  check parameters
    if ( buffer && size > 0 )
    {
        //  init out parameter
        if ( bytesWritten != NULL )
            *bytesWritten = 0;

        ACE_SOCK_Stream stream;
        stream.set_handle( m_handle );

        ssize_t res = 0;

        // On Linux, use MSG_NOSIGNAL to request not to send SIGPIPE on
        // errors on stream oriented sockets when the other end breaks
        // the connection. The EPIPE error is still returned.
        // Note that neither trapping the SIGPIPE signal via an
        // ACE_Event_Handler nor calling ACE_OS::signal(SIGPIPE, SIG_IGN)
        // seems to work.

        if ( blocking )
        {
            res = stream.send_n(buffer, size, MG_MSG_NOSIGNAL);
        }
        else
        {
            res = stream.send(buffer, size, MG_MSG_NOSIGNAL);
        }

        //  check for failure
        if ( res >= 0 )
        {
            //  update out parameter
            if ( bytesWritten != NULL )
                *bytesWritten = res;

            if ( res == (ssize_t)size )
            {
                stat = MgStreamHelper::mssDone;
            }
            else
            {
                stat = blocking ? MgStreamHelper::mssError : MgStreamHelper::mssNotDone;
            }
        }
    }

    return stat;
}