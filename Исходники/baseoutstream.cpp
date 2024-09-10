BaseOutStream::~BaseOutStream() {
	_canCallDetachedFromInStream = false;
	UnLink(true);
}