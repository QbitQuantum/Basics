    int ConnectorInterface::GetBufferIndex(bool bReserve)
    {
#if BEHAVIAC_COMPILER_MSVC
        BEHAVIAC_ASSERT(t_packetBufferIndex != TLS_OUT_OF_INDEXES);
        int bufferIndex = (int)TlsGetValue(t_packetBufferIndex);
#else
        BEHAVIAC_ASSERT(t_packetBufferIndex != (unsigned int) - 1);
        int bufferIndex = (int)t_packetBufferIndex;
#endif
        //WHEN bReserve is false, it is unsafe to allocate memory as other threads might be allocating
        //you can avoid the following assert to malloc a block of memory in your thread at the very beginning
        BEHAVIAC_ASSERT(bufferIndex > 0 || bReserve);

        //bufferIndex initially is 0
        if (bufferIndex <= 0 && bReserve)
        {
            bufferIndex = ReserveThreadPacketBuffer();
        }

        return bufferIndex;
    }