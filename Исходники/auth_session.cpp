QByteArray AuthSessionData::serialize() const {
	auto size = sizeof(qint32) * 2;

	auto result = QByteArray();
	result.reserve(size);
	{
		QBuffer buffer(&result);
		if (!buffer.open(QIODevice::WriteOnly)) {
			Unexpected("Can't open data for AuthSessionData::serialize()");
		}

		QDataStream stream(&buffer);
		stream.setVersion(QDataStream::Qt_5_1);
		stream << static_cast<qint32>(_variables.emojiPanelTab);
		stream << qint32(_variables.lastSeenWarningSeen ? 1 : 0);
	}
	return result;
}