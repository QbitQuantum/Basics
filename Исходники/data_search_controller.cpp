MTPmessages_Search PrepareSearchRequest(
		not_null<PeerData*> peer,
		Storage::SharedMediaType type,
		const QString &query,
		MsgId messageId,
		SparseIdsLoadDirection direction) {
	const auto filter = [&] {
		using Type = Storage::SharedMediaType;
		switch (type) {
		case Type::Photo:
			return MTP_inputMessagesFilterPhotos();
		case Type::Video:
			return MTP_inputMessagesFilterVideo();
		case Type::PhotoVideo:
			return MTP_inputMessagesFilterPhotoVideo();
		case Type::MusicFile:
			return MTP_inputMessagesFilterMusic();
		case Type::File:
			return MTP_inputMessagesFilterDocument();
		case Type::VoiceFile:
			return MTP_inputMessagesFilterVoice();
		case Type::RoundVoiceFile:
			return MTP_inputMessagesFilterRoundVoice();
		case Type::RoundFile:
			return MTP_inputMessagesFilterRoundVideo();
		case Type::GIF:
			return MTP_inputMessagesFilterGif();
		case Type::Link:
			return MTP_inputMessagesFilterUrl();
		case Type::ChatPhoto:
			return MTP_inputMessagesFilterChatPhotos();
		}
		return MTP_inputMessagesFilterEmpty();
	}();

	const auto minId = 0;
	const auto maxId = 0;
	const auto limit = messageId ? kSharedMediaLimit : 0;
	const auto offsetId = [&] {
		switch (direction) {
		case SparseIdsLoadDirection::Before:
		case SparseIdsLoadDirection::Around: return messageId;
		case SparseIdsLoadDirection::After: return messageId + 1;
		}
		Unexpected("Direction in PrepareSearchRequest");
	}();
	const auto addOffset = [&] {
		switch (direction) {
		case SparseIdsLoadDirection::Before: return 0;
		case SparseIdsLoadDirection::Around: return -limit / 2;
		case SparseIdsLoadDirection::After: return -limit;
		}
		Unexpected("Direction in PrepareSearchRequest");
	}();

	return MTPmessages_Search(
		MTP_flags(0),
		peer->input,
		MTP_string(query),
		MTP_inputUserEmpty(),
		filter,
		MTP_int(0),
		MTP_int(0),
		MTP_int(offsetId),
		MTP_int(addOffset),
		MTP_int(limit),
		MTP_int(maxId),
		MTP_int(minId));
}