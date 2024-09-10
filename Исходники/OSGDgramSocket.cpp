/*! Receive a NetworkMessage. Workes like recv, but buffer and size is
    taken from the NetworkMessage
    \see Socket::recv
 */
int DgramSocket::recvFrom(NetworkMessage &msg,SocketAddress &from)
{
    NetworkMessage::Header hdr;
    peek(&hdr,sizeof(hdr));
    msg.setSize(osgntohl(hdr.size));
    return recvFrom(msg.getBuffer(),msg.getSize(),from);
}