void StatusResMsg:: create_payload_file_data(char* homeDir, uint32_t file_index)
{
	char metaDataFileName[256];
	memset(metaDataFileName , 0, 256);
	create_metaDataFilename(metaDataFileName, homeDir, file_index);
	uint32_t recordLen = getFilesize(metaDataFileName);
	header.dataLen += 4;
	header.dataLen += recordLen;	
	recordLengths.push_back(recordLen);
	fileIndexes.push_back(file_index);
}