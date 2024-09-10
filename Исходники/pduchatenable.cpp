int CpduChatEnable::sendChatEnable(SOCKET sd,
                                   u_int16_t flags,
                                   const char* message)
{
    char* buf = value_ + PDU_HEADER_SIZE;
    flags = htons(flags);
    memcpy(buf, &flags , sizeof(flags));
    return sendTo(sd);
}