void CpduBroadTableReply::grok(SOCKET sd, CTable* table)
{
    // Forward the reply to the player (note:
    // the socket goes as well but it's only 2 bytes!)
    u_int16_t playerSocket = getPlayerSocket();
    sendTo(playerSocket);

    // this pdu is done
    delete this;
}