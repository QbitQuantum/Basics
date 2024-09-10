bool WPUtils::removePadding(QByteArray & out) {
	char paddingLength = out[out.length() - 1];
	if (paddingLength < 1 || paddingLength > 16) {
		//toast
		qDebug() << "Invalid padding length. Were the keys good?";
		out.clear();
		return false;
	}
	if (paddingLength > out.length()) {
		//toast
		qDebug() << "Padding is claiming to be longer than the buffer!";
		out.clear();
		return false;
	}
	for (int i = 1; i < paddingLength; ++i) {
		char next = out[out.length() - 1 - i];
		if (next != paddingLength) {
			qDebug()  << "Not all padding bytes are correct!";
			out.clear();
			return false;
		}
	}
	out.remove(out.length() - paddingLength, paddingLength);
	return true;
}