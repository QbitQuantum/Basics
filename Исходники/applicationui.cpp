void ApplicationUI::pad(QByteArray & in) {
	int padLength = 16 - (in.length() % 16);
	for (int i = 0; i < padLength; ++i) {
		in.append((char) padLength);
	}
}