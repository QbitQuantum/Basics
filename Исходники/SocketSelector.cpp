bool SocketSelector::isReady(Socket& socket) const
{
    SocketHandle handle = socket.getHandle();
    if (handle != priv::SocketImpl::invalidSocket())
    {

#if !defined(SFML_SYSTEM_WINDOWS)

        if (handle >= FD_SETSIZE)
            return false;

#endif

        return FD_ISSET(handle, &m_impl->socketsReady) != 0;
    }

    return false;
}