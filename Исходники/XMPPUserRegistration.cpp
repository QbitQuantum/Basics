void XMPPUserRegistration::handleRegisterRemoteRosterResponse(boost::shared_ptr<Swift::RosterPayload> payload, Swift::ErrorPayload::ref remoteRosterNotSupported, const UserInfo &row){
	if (remoteRosterNotSupported || !payload) {
		// Remote roster is not support, so send normal Subscribe presence to add transport.
		Swift::Presence::ref response = Swift::Presence::create();
		response->setFrom(m_component->getJID());
		response->setTo(Swift::JID(row.jid));
		response->setType(Swift::Presence::Subscribe);
		m_component->getFrontend()->sendPresence(response);
	}
	else {
		// Remote roster is support, so use remoteroster XEP to add transport.
		Swift::RosterPayload::ref payload = Swift::RosterPayload::ref(new Swift::RosterPayload());
		Swift::RosterItemPayload item;
		item.setJID(m_component->getJID());
		item.setSubscription(Swift::RosterItemPayload::Both);
		payload->addItem(item);
		Swift::SetRosterRequest::ref request = Swift::SetRosterRequest::create(payload, row.jid, static_cast<XMPPFrontend *>(m_component->getFrontend())->getIQRouter());
		request->send();
	}

	onUserRegistered(row);

	// If the JID for registration notification is configured, send the notification message.
	std::vector<std::string> const &x = CONFIG_VECTOR(m_component->getConfig(),"registration.notify_jid");
	BOOST_FOREACH(const std::string &notify_jid, x) {
		boost::shared_ptr<Swift::Message> msg(new Swift::Message());
		msg->setBody(std::string("registered: ") + row.jid);
		msg->setTo(notify_jid);
		msg->setFrom(m_component->getJID());
		m_component->getFrontend()->sendMessage(msg);
	}