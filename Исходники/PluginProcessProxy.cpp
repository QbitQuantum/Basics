void PluginProcessProxy::pluginProcessCrashedOrFailedToLaunch()
{
    // The plug-in process must have crashed or exited, send any pending sync replies we might have.
    while (!m_pendingConnectionReplies.isEmpty()) {
        RefPtr<Messages::WebProcessProxy::GetPluginProcessConnection::DelayedReply> reply = m_pendingConnectionReplies.takeFirst();

#if PLATFORM(MAC)
        reply->send(CoreIPC::Attachment(0, MACH_MSG_TYPE_MOVE_SEND));
#elif USE(UNIX_DOMAIN_SOCKETS)
        reply->send(CoreIPC::Attachment());
#else
        notImplemented();
#endif
    }

    while (!m_pendingGetSitesReplies.isEmpty())
        didGetSitesWithData(Vector<String>(), m_pendingGetSitesReplies.begin()->first);

    while (!m_pendingClearSiteDataReplies.isEmpty())
        didClearSiteData(m_pendingClearSiteDataReplies.begin()->first);

    // Tell the plug-in process manager to forget about this plug-in process proxy.
    m_pluginProcessManager->removePluginProcessProxy(this);
    delete this;
}