HistoryMessage::HistoryMessage(
	not_null<History*> history,
	const MTPDmessageService &data)
: HistoryItem(
		history,
		data.vid.v,
		mtpCastFlags(data.vflags.v),
		data.vdate.v,
		data.has_from_id() ? data.vfrom_id.v : UserId(0)) {
	CreateConfig config;

	if (data.has_reply_to_msg_id()) config.replyTo = data.vreply_to_msg_id.v;

	createComponents(config);

	switch (data.vaction.type()) {
	case mtpc_messageActionPhoneCall: {
		_media = std::make_unique<Data::MediaCall>(
			this,
			data.vaction.c_messageActionPhoneCall());
	} break;

	default: Unexpected("Service message action type in HistoryMessage.");
	}

	setText(TextWithEntities {});
}