char * PakFile::readAlloc() const {
	
	char * buffer = (char*)malloc(size());
	
	read(buffer);
	
	return buffer;
}