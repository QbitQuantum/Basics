		/*!
		 * \brief
		 * Decompresses a single file from a 7zip archive.
		 * 
		 * \param archive_file
		 * Path to the archive to extract the file from.
		 * 
		 * \param file_name
		 * The fine within the archive to extract.
		 * 
		 * \param uncompressed_data
		 * Reference parameter to set the uncompressed datas pointer to.
		 * 
		 * \param uncompressed_data_size
		 * Reference parameter to set the uncompressed data size to.
		 * 
		 * \returns
		 * Returns true if the decompresseion was successfull, otherwise returns false.
		 * 
		 * Decompresses a single file from a 7zip archive.
		 */
		bool DecompressFileEntry(cstring archive_file,
			cstring file_name,
			byte*& uncompressed_data,
			size_t& uncompressed_data_size)
		{
			CFileInStream archive_stream;
			CLookToRead look_stream;
			CSzArEx archive_desc;
			SRes result;
			ISzAlloc alloc_imp;
			wchar_t wide_file_name[MAX_PATH] = L"";

			// open the archive for reading
			if (InFile_Open(&archive_stream.file, archive_file))
				return false;

			// convert the search file name to a wide char string for comparison later
			if(-1 == swprintf_s(wide_file_name, MAX_PATH, L"%S", file_name))
				return false;

			// set up the memory handling functions
			alloc_imp.Alloc = AllocFunc;
			alloc_imp.Free = FreeFunc;

			FileInStream_CreateVTable(&archive_stream);
			LookToRead_CreateVTable(&look_stream, False);

			look_stream.realStream = &archive_stream.s;
			LookToRead_Init(&look_stream);

			CrcGenerateTable();

			SzArEx_Init(&archive_desc);
			result = SzArEx_Open(&archive_desc, &look_stream.s, &alloc_imp, &alloc_imp);

			if(result == SZ_OK)
			{
				int index = -1;
				// search for the file in the archive
				for (uint32 i = 0; (index == -1) && (i < archive_desc.db.NumFiles); i++)
				{
					if(archive_desc.db.Files[i].IsDir)
						continue;

					// get the name of the file in the archive
					uint32 name_length = SzArEx_GetFileNameUtf16(&archive_desc, i, NULL);
					wchar_t* archive_file_name = new wchar_t[name_length];
					SzArEx_GetFileNameUtf16(&archive_desc, i, (UInt16*)archive_file_name);

					// compare the file names
					if(wcscmp(wide_file_name, archive_file_name) == 0)
						index = i;

					// delete allocated memory
					delete [] archive_file_name;
				}

				if(index > -1)
				{
					// file found, so decompress it
					result = Decompress(archive_stream,
						archive_desc,
						look_stream,
						index,
						uncompressed_data,
						uncompressed_data_size);
				}
			}

			SzArEx_Free(&archive_desc, &alloc_imp);

			File_Close(&archive_stream.file);

			return result == SZ_OK;
		}