Share<IStream> MemoryPackage::OnWriteFile(FileEntry& file, FileOpenMode openMode /*= FileOpenMode::ReadOnly*/, FileDataType dataType /*= FileDataType::Binary*/)
{
	UN_USED(dataType);
	Share<MemoryStream> memoryStream = mMemoryStreamDict.GetOptional(&file, nullptr);
	if (memoryStream == nullptr)
	{
		if (openMode == FileOpenMode::ReadOnly)
		{
			return nullptr;
		}
		memoryStream = new MemoryStream();
		mMemoryStreamDict.Add(&file, memoryStream);
	}
	memoryStream->Rewind();

	return memoryStream;
}