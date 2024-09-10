void DBusSender::sendSyncMessage()
{
	QDBusConnection	sessionBus = QDBusConnection::connectToBus(QDBusConnection::SessionBus, m_senderName);

	if (!sessionBus.isConnected()) {
		qDebug() << m_senderName << "connectToBus() failed";
		return;
	}

	QDBusMessage stream = QDBusMessage::createSignal(
								m_objNameBase + m_senderName,
								com::servicename::ifname::staticInterfaceName(),
								"syncSend");

	stream << m_sender.text().toLocal8Bit();
	sessionBus.send(stream);
}