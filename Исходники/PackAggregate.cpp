bool PackAggregate::resortFilePack(const char* pack, std::vector<PackAggregate::stFileInfo> & files)
{
	char szDir[MAX_PATH] = { 0 };
	char tmpFile[MAX_PATH] = { 0 };
	char *p;
	strcpy(szDir, pack);
	p = strrchr(szDir, '\\');
	if (p)
		*p = 0;
	if (!GetTempFileNameA(szDir, "pak", 0, tmpFile))	//创建0字节文件名为szDir.pak的文件
	{
		return false;
	}

	if (!CopyFileA(pack, tmpFile, FALSE))	//把文件拷贝到临时文件夹
		return false;

	Data mdata = FileUtils::getInstance()->getDataFromFile(tmpFile);
	PackAggregate::stPackHeader hdr;
	mdata.read(&hdr, sizeof(PackAggregate::stPackHeader));

	size_t filesize = mdata.getSize();
	mdata.setPosition(filesize - hdr.headerSize);

	std::vector<BYTE> tmpBuff;
	tmpBuff.resize(files.size() * sizeof(stFileInfo));
	p = (char*)&tmpBuff[0];
	for (size_t i = 0; i < files.size(); ++i)
	{
		stFileInfo1 * dst1 = (stFileInfo1*)p;
		stFileInfo & st = files[i];
		p += sizeof(stFileInfo1);

		*dst1 = st.st1;

		char* pname = (char*)p;
		strcpy(pname, st.szName);
		p += strlen(pname) + 1;
	}

	size_t size = ((p - (char*)&tmpBuff[0]) + 7) & (~7);

	BYTE des_key[3][8];
	PasswordToDesKey(PackAggregate::GetDefaultPassword(), des_key[0], des_key[1], des_key[2]);
	EncryptHeaderData(&tmpBuff[0], size, des_key[0], des_key[1], des_key[2]);
	mdata.write(&tmpBuff[0], size);
	FileUtils::getInstance()->writeDataToFile(tmpFile, mdata);
	return FileUtilsWin32::updateFile(tmpFile, pack);
}