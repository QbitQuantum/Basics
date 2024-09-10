int64_t file_tell(FILE * file)
{
#ifdef _WIN32
	return _ftelli64(file);
#else
	return ftell(file);
#endif
}