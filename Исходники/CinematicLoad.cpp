bool loadCinematic(Cinematic * c, const res::path & file) {
	
	LogInfo << "loading cinematic " << file;
	
	size_t size;
	char * data = resources->readAlloc(file, size);
	if(!data) {
		LogError << "cinematic " << file << " not found";
		return false;
	}
	
	bool ret = parseCinematic(c, data, size);
	free(data);
	if(!ret) {
		LogError << "loading cinematic " << file;
		c->New();
	}
	
	return ret;
}