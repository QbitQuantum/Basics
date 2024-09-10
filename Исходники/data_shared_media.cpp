base::optional<int> SharedMediaWithLastSlice::indexOf(Value value) const {
	const auto result = indexOfImpl(value);
	if (result && (*result < 0 || *result >= size())) {
		// Should not happen.
		auto info = QStringList();
		info.push_back("slice:" + QString::number(_slice.size()));
		info.push_back(_slice.fullCount()
			? QString::number(*_slice.fullCount())
			: QString("-"));
		info.push_back(_slice.skippedBefore()
			? QString::number(*_slice.skippedBefore())
			: QString("-"));
		info.push_back(_slice.skippedAfter()
			? QString::number(*_slice.skippedAfter())
			: QString("-"));
		info.push_back("ending:" + (_ending
			? QString::number(_ending->size())
			: QString("-")));
		info.push_back((_ending && _ending->fullCount())
			? QString::number(*_ending->fullCount())
			: QString("-"));
		info.push_back((_ending && _ending->skippedBefore())
			? QString::number(*_ending->skippedBefore())
			: QString("-"));
		info.push_back((_ending && _ending->skippedAfter())
			? QString::number(*_ending->skippedAfter())
			: QString("-"));
		if (const auto msgId = base::get_if<FullMsgId>(&value)) {
			info.push_back("value:" + QString::number(msgId->channel));
			info.push_back(QString::number(msgId->msg));
			const auto index = _slice.indexOf(*base::get_if<FullMsgId>(&value));
			info.push_back("index:" + (index
				? QString::number(*index)
				: QString("-")));
		} else if (const auto photo = base::get_if<not_null<PhotoData*>>(&value)) {
			info.push_back("value:" + QString::number((*photo)->id));
		} else {
			info.push_back("value:bad");
		}
		info.push_back("isolated:" + QString(Logs::b(isolatedInSlice())));
		info.push_back("last:" + (_lastPhotoId
			? QString::number(*_lastPhotoId)
			: QString("-")));
		info.push_back("isolated_last:" + (_isolatedLastPhoto
			? QString(Logs::b(*_isolatedLastPhoto))
			: QString("-")));
		info.push_back("skip:" + (lastPhotoSkip()
			? QString::number(*lastPhotoSkip())
			: QString("-")));
		CrashReports::SetAnnotation("DebugInfo", info.join(','));
		Unexpected("Result in SharedMediaWithLastSlice::indexOf");
	}
	return _reversed
		? (result | func::negate | func::add(size() - 1))
		: result;
}