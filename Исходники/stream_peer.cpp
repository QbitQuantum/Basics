void StreamPeer::put_utf8_string(const String &p_string) {

	CharString cs = p_string.utf8();
	put_data((const uint8_t *)cs.get_data(), cs.length());
}