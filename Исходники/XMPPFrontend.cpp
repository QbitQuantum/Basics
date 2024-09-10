void XMPPFrontend::sendRosterRequest(Swift::RosterPayload::ref payload, Swift::JID to) {
	Swift::SetRosterRequest::ref request = Swift::SetRosterRequest::create(payload, to, m_iqRouter);
	request->send();
}