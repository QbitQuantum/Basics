void Msg2Msg::OnPipeListenEvent(ProtoSocket&       theSocket, 
                                ProtoSocket::Event theEvent)
{
    ProtoPipe *thePipePtr = (ProtoPipe*)&theSocket;
    switch (theEvent)
    {
        case ProtoSocket::RECV:
        {
            TRACE("msg2Msg: listen RECV event ..\n");
            unsigned int len = 8191;
            if(thePipePtr->Recv(msg_buffer, len))
            {
                if(len)
                {
                    SendMessage();
                }
            }
            else
            {
                DMSG(0,"Msg2Msg::OnPipeListenEvent() Error getting message\n");
            }
            break;
        }
        case ProtoSocket::SEND:
            TRACE("msg2Msg: listen SEND event ..\n");
            break;
        case ProtoSocket::ACCEPT:
            TRACE("msg2Msg: listen ACCEPT event ..\n");
            if(!thePipePtr->Accept())
            {
                DMSG(0,"Msg2Msg::OnPipeListenEvent() Error on calling Accept()\n");
            }
            break;
        case ProtoSocket::DISCONNECT:
            TRACE("msg2Msg: listen DISCONNECT event ..\n");
            char pipeName[PATH_MAX];
            strncpy(pipeName,thePipePtr->GetName(),PATH_MAX);
            thePipePtr->Close();
            if(!thePipePtr->Listen(pipeName))
            {
                DMSG(0,"Msg2Msg::OnPipeListenEvent() Error restarting listen pipe...\n");
            }
            break;
        default:
            TRACE("Msg2Msg::OnPipeListenEvent(%d) unhandled event type\n", theEvent);
            break;
        
    }  // end switch(theEvent)
}  // end Msg2Msg::OnPipeListenEvent()