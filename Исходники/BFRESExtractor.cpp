static void WriteEmbeddedFileToDisk(int nodeIndex, int nodeOffsetFromStartOfFile, IndexGroup *pSubFileData, FRESHeader *pHeader, char *pFileName)
{
	// Figure out the data offset location.
	int dataOffsetFromBoF = nodeOffsetFromStartOfFile + 0xC + pSubFileData->GetNode(nodeIndex)->GetDataOffset();
	int dataOffset = _byteswap_ulong(*(int *)((char *)pHeader + dataOffsetFromBoF));
	int dataLength = _byteswap_ulong(*(int *)((char *)pHeader + dataOffsetFromBoF + 0x4));

	std::cout << "\t\tEmbedded Data Offset: " << dataOffset << " Length: " << dataLength << std::endl;

	std::string outputDir = CurrentWorkingDir + GetFolderNameForGroupIndex(11);
	outputDir.append("\\");
	CreateDirectoryAbsolute(outputDir);
	outputDir.append(pFileName);

	std::filebuf fb;
	fb.open(outputDir, std::ios::out | std::ios::ate | std::ios::binary);

	std::ostream outFile(&fb);
	outFile.write((char *)pHeader + sizeof(FRESHeader) + dataOffset + (nodeIndex * 0x8), dataLength);
	fb.close();
}