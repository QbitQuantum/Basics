    }
    BLOCK_END("ChatHandler::handleMessage")
}

void ChatHandler::talk(const std::string &restrict text,
                       const std::string &restrict channel A_UNUSED) const
{
    if (!localPlayer)
        return;

    const std::string mes = std::string(localPlayer->getName()).append(
        " : ").append(text);

    createOutPacket(CMSG_CHAT_MESSAGE);
    // Added + 1 in order to let eAthena parse admin commands correctly
    outMsg.writeInt16(static_cast<int16_t>(mes.length() + 4 + 1), "len");
    outMsg.writeString(mes, static_cast<int>(mes.length() + 1), "message");
}

void ChatHandler::talkRaw(const std::string &mes) const
{
    createOutPacket(CMSG_CHAT_MESSAGE);
    outMsg.writeInt16(static_cast<int16_t>(mes.length() + 4), "len");
    outMsg.writeString(mes, static_cast<int>(mes.length()), "message");
}

void ChatHandler::privateMessage(const std::string &restrict recipient,
                                 const std::string &restrict text)
{
    createOutPacket(CMSG_CHAT_WHISPER);
    outMsg.writeInt16(static_cast<int16_t>(text.length() + 28), "len");