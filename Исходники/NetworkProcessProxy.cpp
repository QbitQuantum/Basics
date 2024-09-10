void NetworkProcessProxy::networkProcessCrashedOrFailedToLaunch()
{
    // The network process must have crashed or exited, send any pending sync replies we might have.
    while (!m_pendingConnectionReplies.isEmpty()) {
        RefPtr<Messages::WebProcessProxy::GetNetworkProcessConnection::DelayedReply> reply = m_pendingConnectionReplies.takeFirst();

#if PLATFORM(MAC)
        reply->send(CoreIPC::Attachment(0, MACH_MSG_TYPE_MOVE_SEND));
#else
        notImplemented();
#endif
    }

    // Tell the network process manager to forget about this network process proxy. This may cause us to be deleted.
    m_webContext->networkProcessCrashed(this);
}