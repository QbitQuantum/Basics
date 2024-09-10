bool CopyFileToPak(FArchive& InPak, const FString& InMountPoint, const FPakInputPair& InFile, uint8*& InOutPersistentBuffer, int64& InOutBufferSize, FPakEntryPair& OutNewEntry)
{	
	TAutoPtr<FArchive> FileHandle(IFileManager::Get().CreateFileReader(*InFile.Source));
	bool bFileExists = FileHandle.IsValid();
	if (bFileExists)
	{
		const int64 FileSize = FileHandle->TotalSize();
		const int64 PaddedEncryptedFileSize = Align(FileSize, FAES::AESBlockSize); 
		OutNewEntry.Filename = InFile.Dest.Mid(InMountPoint.Len());
		OutNewEntry.Info.Offset = 0; // Don't serialize offsets here.
		OutNewEntry.Info.Size = FileSize;
		OutNewEntry.Info.UncompressedSize = FileSize;
		OutNewEntry.Info.CompressionMethod = COMPRESS_None;
		OutNewEntry.Info.bEncrypted = InFile.bNeedEncryption;

		if (InOutBufferSize < PaddedEncryptedFileSize)
		{
			InOutPersistentBuffer = (uint8*)FMemory::Realloc(InOutPersistentBuffer, PaddedEncryptedFileSize);
			InOutBufferSize = FileSize;
		}

		// Load to buffer
		FileHandle->Serialize(InOutPersistentBuffer, FileSize);

		{
			int64 SizeToWrite = FileSize;
			if (InFile.bNeedEncryption)
			{
				for(int64 FillIndex=FileSize; FillIndex < PaddedEncryptedFileSize && InFile.bNeedEncryption; ++FillIndex)
				{
					// Fill the trailing buffer with random bytes from file
					InOutPersistentBuffer[FillIndex] = InOutPersistentBuffer[rand()%FileSize];
				}

				//Encrypt the buffer before writing it to disk
				FAES::EncryptData(InOutPersistentBuffer, PaddedEncryptedFileSize);
				// Update the size to be written
				SizeToWrite = PaddedEncryptedFileSize;
				OutNewEntry.Info.bEncrypted = true;
			}

			// Calculate the buffer hash value
			FSHA1::HashBuffer(InOutPersistentBuffer,FileSize,OutNewEntry.Info.Hash);

			// Write to file
			OutNewEntry.Info.Serialize(InPak,FPakInfo::PakFile_Version_Latest);
			InPak.Serialize(InOutPersistentBuffer,SizeToWrite);
		}
	}
	return bFileExists;
}