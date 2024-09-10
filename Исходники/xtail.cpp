///Gets a file length.
__int64 XTail::getFileLength(LPWSTR fileName)
{
	len = 0;

	filename = fileName;

	FILE *file;
	//file.open(fileName, ios::in | ios::binary);
	if (_wfopen_s(&file, fileName, L"rb") != 0)
	//if (file.bad() || file.fail())
		goto exit;

	//file.seekg(0, ios::beg);
	if (_fseeki64(file, 0, SEEK_SET) != 0)
		goto exit;
	//streamoff begin = file.tellg();
	__int64 begin = _ftelli64(file);

	//file.seekg(0, ios::end);
	if (_fseeki64(file, 0, SEEK_END) != 0)
		goto exit;
	//streamoff end = file.tellg();
	__int64 end = _ftelli64(file);

	len = end - begin;
	
exit:
	//if (file.is_open())
	//	file.close();
	if (file)
		fclose(file);

	return len;

}