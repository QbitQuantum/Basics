	return true;
}

uint256 CLotData::GetClottoFileHash() {
	CAutoFile fileout = CAutoFile(OpenFile(0, true), SER_DISK, CLIENT_VERSION);
	if (!fileout)
		return error("CLotDB::GetClottoFileHash : open failed");
	fseek(fileout, 0, SEEK_END);	//move the point to the end of file
	long filesize = ftell(fileout);	//get the file size
	if (filesize < 0)
		return error("CLotDB::GetClottoFileHash : ftell failed");
	rewind(fileout);	//move the point to the start of file

	vector<unsigned char> vchData;
	vchData.resize(filesize);

	try {
		fileout.read((char *) &vchData[0], filesize);
	} catch (std::exception &e) {
		return error("CLotDB::GetClottoFileHash : read failed");
	}
	fileout.fclose();
