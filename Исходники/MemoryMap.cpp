	MemoryMapImpl(const char *mappingObject,uint64_t size,bool createOk)
	{
		mData = NULL;
		mMapFile = NULL;
		mMapHandle = NULL;
		bool createFile = true;
		bool fileOk = false;

		HANDLE h = CreateFileA(mappingObject, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if ( h != NULL )
		{
			size = getFileSize(h);
			fileOk = true;
			createFile = false;
			printf("Found previous existing mapping file '%s' and using it.\r\n", mappingObject );
			CloseHandle(h);
		}

		if ( createFile && createOk )
		{
			printf("Creating memory map file: %s\r\n", mappingObject);
			HANDLE h = CreateFileA(mappingObject, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if ( h != NULL )
			{
				#define ONEMB (1024*1024)
				char *temp = (char *)malloc(ONEMB);
				if ( temp )
				{
					memset(temp,0,ONEMB);
					uint64_t writeSize = size;
					while ( writeSize > 0 )
					{
						DWORD w = writeSize >= ONEMB ? ONEMB : (DWORD)writeSize;
						DWORD bytesWritten=0;
						WriteFile(h,temp,w,&bytesWritten,NULL);
						if ( bytesWritten != w )
						{
							printf("Failed to write to file '%s', out of disk space?\r\n", mappingObject );
							break;
						}
						writeSize-=w;
					}
					if ( writeSize == 0)
					{
						fileOk = true;
						printf("Finished creating mapping file '%s'\r\n", mappingObject );
					}
				}
				CloseHandle(h);
			}
		}

		if ( fileOk )
		{
			mMapSize = size;
			mMapFile = CreateFileA(mappingObject, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (mMapFile != INVALID_HANDLE_VALUE)
			{
				mMapHandle = CreateFileMappingA(mMapFile, NULL, PAGE_READWRITE, 0, 0, NULL);
				if (mMapHandle == INVALID_HANDLE_VALUE) 
				{
					CloseHandle(mMapFile);
					mMapFile = NULL;
				}
				else
				{
					mData = MapViewOfFile(mMapHandle, FILE_MAP_WRITE, 0, 0, 0);
					if ( mData == NULL) 
					{
						CloseHandle(mMapHandle);
						CloseHandle(mMapFile);
						mMapHandle = NULL;
						mMapFile = NULL;
					}
				}
			}
		}
	}