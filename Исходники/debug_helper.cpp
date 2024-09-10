//-------------------------------------------------------------------------------------
void DebugHelper::sync()
{
    if(bufferedLogPackets_.size() == 0)
        return;

    if(messagelogAddr_.isNone())
    {
        if(bufferedLogPackets_.size() > 128)
        {
            ERROR_MSG("DebugHelper::sync: can't found messagelog. packet size=%u.\n", bufferedLogPackets_.size());
            clearBufferedLog();
        }
        return;
    }

    int8 v = Mercury::g_trace_packet;
    Mercury::g_trace_packet = 0;

    Mercury::Channel* pChannel = pNetworkInterface_->findChannel(messagelogAddr_);
    if(pChannel == NULL)
    {
        if(bufferedLogPackets_.size() > 1024)
        {
            messagelogAddr_.ip = 0;
            messagelogAddr_.port = 0;

            WARNING_MSG("DebugHelper::sync: is no use the messagelog, packet size=%u.\n",
                        bufferedLogPackets_.size());
            clearBufferedLog();
        }

        Mercury::g_trace_packet = v;
        return;
    }

    if(bufferedLogPackets_.size() > 0)
    {
        if(bufferedLogPackets_.size() > 32)
        {
            WARNING_MSG("DebugHelper::sync: packet size=%u.\n", bufferedLogPackets_.size());
        }

        int i = 0;

        size_t totalLen = 0;

        std::list< Mercury::Bundle* >::iterator iter = bufferedLogPackets_.begin();
        for(; iter != bufferedLogPackets_.end();)
        {
            if(i++ >= 32 || totalLen > (PACKET_MAX_SIZE_TCP * 10))
                break;

            totalLen += (*iter)->currMsgLength();
            pChannel->send((*iter));

            Mercury::Bundle::ObjPool().reclaimObject((*iter));
            bufferedLogPackets_.erase(iter++);
        }
    }

    Mercury::g_trace_packet = v;
}