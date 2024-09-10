BaseInStream::~BaseInStream() {
	_canCallOutStreamDetached = false;
	while (_linkedStreams.size() > 0) {
		UnLink(MAP_VAL(_linkedStreams.begin()), true);
	}
}