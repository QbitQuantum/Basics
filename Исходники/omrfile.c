int32_t
omrfile_move(struct OMRPortLibrary *portLibrary, const char *pathExist, const char *pathNew)
{
	return rename(pathExist, pathNew);
}