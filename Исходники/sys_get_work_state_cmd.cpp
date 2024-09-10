GMI_RESULT  SysGetWorkStateCommandExecutor::Execute()
{
#define           MESSAGE_LENGTH  16384
    int32_t           MessageCode     = RETCODE_OK;
    GMI_RESULT        Result          = GMI_SUCCESS;
    SystemPacket     *CommandPacket   = (SystemPacket*)m_Reply.GetPtr();

    int32_t            GetWorkStateLen = 0;
    SysPkgXml          SysWorkState;
    ReferrencePtr<char_t, DefaultObjectsDeleter> WorkStateMessage(BaseMemoryManager::Instance().News<char_t>(MESSAGE_LENGTH));
    if (NULL == WorkStateMessage.GetPtr())
    {
        return GMI_OUT_OF_MEMORY;
    }

    do
    {
        memset(&SysWorkState, 0, sizeof(SysPkgXml));
        Result = m_SystemServiceManager->GetWorkState(MESSAGE_LENGTH, WorkStateMessage.GetPtr(), &SysWorkState);
        if (FAILED(Result))
        {
            MessageCode = RETCODE_ERROR;
            break;
        }
        GetWorkStateLen                = SysWorkState.s_ContentLength;
        SysWorkState.s_ContentLength   = HOST_TO_NETWORK_UINT(SysWorkState.s_ContentLength);
        SysWorkState.s_Encrypt         = HOST_TO_NETWORK_UINT(SysWorkState.s_Encrypt);
    }
    while (0);

    // Reply
    uint16_t PacketHeaderSize = sizeof(SysPkgHeader);
    uint16_t PacketAttrHdSize1;
    uint16_t PayloadTotalSize;
    uint16_t AppPacketSize;

    if (MessageCode == RETCODE_OK)
    {
        PacketAttrHdSize1 = sizeof(SysPkgAttrHeader) + sizeof(SysPkgXml) + GetWorkStateLen;
    }
    else
    {
        PacketAttrHdSize1 = sizeof(SysPkgAttrHeader) + sizeof(SysPkgMessageCode);
    }
    PayloadTotalSize = PacketAttrHdSize1 + sizeof(SdkPkgTransferProtocolKey);
    AppPacketSize    = PacketHeaderSize  + PacketAttrHdSize1;
    ReferrencePtr<SystemPacket> Reply(BaseMemoryManager::Instance().New<SystemPacket>());
    if (NULL == Reply.GetPtr())
    {
        return GMI_OUT_OF_MEMORY;
    }

    //SYS_ERROR("line = %d\n", __LINE__);
    Result = Reply->AllocatePacketBuffer(0, PayloadTotalSize);
    if (FAILED(Result))
    {
        return Result;
    }
    //SYS_ERROR("line = %d\n", __LINE__);
    //fill packet header
    Result = SystemPacket::FillPacketHeader(
                 Reply->GetPacketHeaderBuffer(),
                 CommandPacket->GetMessageTag(),
                 CommandPacket->GetVersion(),
                 SYSCODE_GET_DEVICE_WORK_STATE_RSP,
                 1,
                 AppPacketSize,
                 CommandPacket->GetSessionId(),
                 CommandPacket->GetSequenceNumber()
             );
    if (FAILED(Result))
    {
        SYS_ERROR("FillPacketHeader fail\n");
        return Result;
    }
    //SYS_ERROR("line = %d\n", __LINE__);
    //fill packet body
    uint8_t *PayloadBuffer = Reply->GetPacketPayloadBuffer();
    uint16_t Offset = 0;
    SysPkgAttrHeader *SysPkgAtrrHdPtr;

    if (MessageCode == RETCODE_OK)
    {
        SysPkgXml *SysCapabilitiesPtr;
        char_t    *MessagePtr;

        SysPkgAtrrHdPtr = (SysPkgAttrHeader*)PayloadBuffer;
        SysPkgAtrrHdPtr->s_Type   = HOST_TO_NETWORK_USHORT(TYPE_XML);
        SysPkgAtrrHdPtr->s_Length = HOST_TO_NETWORK_USHORT(PacketAttrHdSize1);
        Offset                   += sizeof(SysPkgAttrHeader);
        //SYS_ERROR("line = %d\n", __LINE__);
        SysCapabilitiesPtr        = (SysPkgXml*)(PayloadBuffer + Offset);
        //SYS_ERROR("line = %d\n", __LINE__);
        memcpy((void_t*)SysCapabilitiesPtr, (void_t*)&SysWorkState,  sizeof(SysPkgXml));
        //SYS_ERROR("line = %d\n", __LINE__);
        Offset                   += sizeof(SysPkgXml);
        MessagePtr                = (char_t*)(PayloadBuffer + Offset);
        //SYS_ERROR("line = %d, PacketAttrHdSize1 %d, SysCapabilities.s_ContentLength %d\n", __LINE__, PacketAttrHdSize1, GetWorkStateLen);
        memcpy(MessagePtr, WorkStateMessage.GetPtr(), GetWorkStateLen);
        //SYS_ERROR("line = %d\n", __LINE__);
        Offset                   += GetWorkStateLen;
    }
    else
    {
        SysPkgMessageCode *SysPkgMessageCodePtr;

        SysPkgAtrrHdPtr = (SysPkgAttrHeader*)PayloadBuffer;
        SysPkgAtrrHdPtr->s_Type   = HOST_TO_NETWORK_USHORT(TYPE_MESSAGECODE);
        SysPkgAtrrHdPtr->s_Length = HOST_TO_NETWORK_USHORT(PacketAttrHdSize1);
        Offset                   += sizeof(SysPkgAttrHeader);
        SysPkgMessageCodePtr      = (SysPkgMessageCode*)(PayloadBuffer + Offset);
        SysPkgMessageCodePtr->s_MessageCode = HOST_TO_NETWORK_UINT(MessageCode);
        SysPkgMessageCodePtr->s_MessageLen  = 0;
        Offset                   += sizeof(SysPkgMessageCode);
        Offset                   += SysPkgMessageCodePtr->s_MessageLen;
    }
    SYS_ERROR("line = %d\n", __LINE__);
    //fill packet tail
    Result = SystemPacket::FillPacketSdkTransferProtocolKey(
                 (PayloadBuffer + Offset),
                 CommandPacket->GetSdkTransferKeyTag(),
                 CommandPacket->GetSdkTransferProtocolSessionId(),
                 CommandPacket->GetSdkTransferProtocolSequenceNumber(),
                 CommandPacket->GetSdkTransferProtocolAuthValue()
             );
    if (FAILED(Result))
    {
        SYS_ERROR("FillPacketSdkTransferProtocolKey fail\n");
        return Result;
    }
    SYS_ERROR("line = %d\n", __LINE__);
    m_Reply = Reply;

    return GMI_SUCCESS;
}