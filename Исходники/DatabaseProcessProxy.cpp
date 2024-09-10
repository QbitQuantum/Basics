void DatabaseProcessProxy::didCreateDatabaseToWebProcessConnection(const IPC::Attachment& connectionIdentifier)
{
    ASSERT(!m_pendingConnectionReplies.isEmpty());

    RefPtr<Messages::WebProcessProxy::GetDatabaseProcessConnection::DelayedReply> reply = m_pendingConnectionReplies.takeFirst();

#if OS(DARWIN)
    reply->send(IPC::Attachment(connectionIdentifier.port(), MACH_MSG_TYPE_MOVE_SEND));
#elif USE(UNIX_DOMAIN_SOCKETS)
    reply->send(connectionIdentifier);
#else
    notImplemented();
#endif
}