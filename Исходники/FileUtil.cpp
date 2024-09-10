bool CFileUtil::writeString(IFileObject* file, const CString &str)
{
	uint32 len = str.length();
	return file->write(&len, sizeof(uint32)) && file->write(*str, len);
}