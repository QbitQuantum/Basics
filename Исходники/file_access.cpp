void FileAccess::store_pascal_string(const String &p_string) {

	CharString cs = p_string.utf8();
	store_32(cs.length());
	store_buffer((uint8_t *)&cs[0], cs.length());
};