/**
 * Constructor for the SocketEvents class.
 */
SocketEvents::SocketEvents(const Socket::Ptr& socket, Object *lifesupportObject)
	: m_ID(m_NextID++), m_FD(socket->GetFD()), m_EnginePrivate(NULL)
{
	boost::call_once(l_SocketIOOnceFlag, &SocketEvents::InitializeEngine);

	Register(lifesupportObject);
}