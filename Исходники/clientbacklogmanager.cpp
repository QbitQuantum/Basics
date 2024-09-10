void ClientBacklogManager::receiveBacklog(BufferId bufferId, MsgId first, MsgId last, int limit, int additional, QVariantList msgs) {
  Q_UNUSED(first) Q_UNUSED(last) Q_UNUSED(limit) Q_UNUSED(additional)

  emit messagesReceived(bufferId, msgs.count());

  MessageList msglist;
  foreach(QVariant v, msgs) {
    Message msg = v.value<Message>();
    msg.setFlags(msg.flags() | Message::Backlog);
    msglist << msg;
  }