void Pipe2Sock::OnListenEvent(ProtoSocket&       /*theSocket*/, 
                                ProtoSocket::Event theEvent)
{
    switch (theEvent)
    {
        case ProtoSocket::RECV:
        {
            TRACE("pipe2Sock: listen RECV event ..\n");
            unsigned int len = 8191;
            if (listen_pipe.Recv(msg_buffer, len))
            {
                if (len){
                    SendMessage();
                    TRACE("pipe2Sock: recvd \"%s\"\n", msg_buffer);
                }
            }
            else
            {
                PLOG(PL_ERROR, "Pipe2Sock::OnListenEvent() listen_pipe.Recv() error\n");
            }            
            break;
        }
        case ProtoSocket::SEND:
            TRACE("pipe2Sock: listen SEND event ..\n");
            break;
        case ProtoSocket::ACCEPT:
            TRACE("pipe2Sock: listen ACCEPT event ..\n");
            if (!listen_pipe.Accept())
                PLOG(PL_ERROR, "Pipe2Sock::OnListenEvent() listen_pipe.Accept() error\n");
            break;
        case ProtoSocket::DISCONNECT:
            TRACE("pipe2Sock: listen DISCONNECT event ..\n");
            char pipeName[PATH_MAX];
            strncpy(pipeName, listen_pipe.GetName(), PATH_MAX);
            listen_pipe.Close();
            if (!listen_pipe.Listen(pipeName))
                PLOG(PL_ERROR, "pipe2Sock: error restarting listen pipe ...\n");
            break;
        default:
            TRACE("Pipe2Sock::OnListenEvent(%d) unhandled event type\n", theEvent);
            break;
        
    }  // end switch(theEvent)
}  // end Pipe2Sock::OnListenEvent()