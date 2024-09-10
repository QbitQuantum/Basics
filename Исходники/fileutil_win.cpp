bool renameFile(const char* oldpath, const char* newpath)
{
	return !!MoveFileExW(fromUtf8(oldpath).c_str(), fromUtf8(newpath).c_str(), MOVEFILE_REPLACE_EXISTING);
}