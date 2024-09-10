static off_t custom_seek(void* io, off_t offset, int seek_type) {
	FILE* f = reinterpret_cast<FILE*>(io);
	fseek(f, offset, seek_type);
	return ftell(f);
}