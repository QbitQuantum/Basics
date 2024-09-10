static size_t FolderOutStream_Write2(CFolderOutStream *p, const void *data, size_t size)
{
	SizeT processedSize = 0;
	UInt16 *fullPath = NULL;
	SizeT pathLen = 0;
	SizeT curSize = 0;
	SRes res = SZ_OK;
	UInt32 i;
	SizeT dirLen = 0;
	
	if(p->outputDir)
		dirLen = wcslen(p->outputDir);

	while(size != 0)
	{
		if(p->file.handle == INVALID_HANDLE_VALUE)
		{
			UInt16 *filename;
			UInt32 index  = p->startIndex + p->currentIndex;
			const CSzFileItem *fileItem = p->ar->db.Files + index;
			SizeT len = SzArEx_GetFileNameUtf16(p->ar, index, NULL);
			if(len + dirLen > pathLen)
			{
				free(fullPath);
				pathLen = len + dirLen;
				fullPath = (UInt16*)malloc(pathLen * sizeof(fullPath[0]));
				if(fullPath == 0)
				{
					res = SZ_ERROR_MEM;
					break;
				}

				if(p->outputDir)
					wcscpy_s(fullPath,pathLen,p->outputDir);
			}

			filename = fullPath + dirLen;
			SzArEx_GetFileNameUtf16(p->ar, index, filename);
			for (i = 0; fullPath[i] != 0 && i<pathLen; i++)
				if (fullPath[i] == '/')
				{
					fullPath[i] = 0;
					CreateDirectoryW(fullPath,NULL);
					fullPath[i] = CHAR_PATH_SEPARATOR;
				}
				
			if (fileItem->IsDir)
			{
				CreateDirectoryW(fullPath,NULL);
				continue;
			}
			else if(OutFile_OpenW(&p->file, fullPath))
			{
				res = SZ_ERROR_FAIL;
				break;
			}

#ifdef _SZ_ALLOC_DEBUG
			wprintf(L"\nExtract: %s", fullPath);
#endif
			p->fileSize = fileItem->Size;
			p->checkCrc = fileItem->CrcDefined;
			p->crc = CRC_INIT_VAL;
		}

		curSize = size < p->fileSize ? size : (SizeT)p->fileSize;
		if(S_OK != File_Write(&p->file, data, &curSize))
		{
			File_Close(&p->file);
			res = SZ_ERROR_FAIL;
			break;
		}

		if(p->checkCrc)
			p->crc = CrcUpdate(p->crc,data,curSize);

		data = (const Byte*)data + curSize;
		size -= curSize;
		p->fileSize -= curSize;
		p->folderSize -= curSize;
		processedSize += curSize;

		if(p->fileSize == 0)
		{
			UInt32 index  = p->startIndex + p->currentIndex;
			const CSzFileItem *fileItem = p->ar->db.Files + index;

			p->currentIndex += 1;

			if(fileItem->MTimeDefined)
				SetFileTime(p->file.handle,NULL,NULL,(const FILETIME*)&fileItem->MTime);

			File_Close(&p->file);

			if(fileItem->AttribDefined)
				SetFileAttributesW(fullPath, fileItem->Attrib);

			if(fileItem->CrcDefined && CRC_GET_DIGEST(p->crc) != fileItem->Crc)
			{
				res = SZ_ERROR_CRC;
				break;
			}
		}
	}

	free(fullPath);
	return processedSize;
}