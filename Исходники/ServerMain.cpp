void DeleteSocket(SOCKET *s)
{
    socketlistmtx.lock();
    activeSocket.remove(s);
    socketlistmtx.unlock();
}