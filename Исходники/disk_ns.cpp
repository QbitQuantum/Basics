Common::SeekableReadStream* DosDisk_ns::loadMusic(const char* name) {
	char path[PATH_LEN];
	sprintf(path, "%s.mid", name);
	return openFile(path);
}