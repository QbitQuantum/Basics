void ParseXpck(FILE *infile, bool quietMode)
{
	ArchiveHeaderXpck header = { 0 };
	int archiveSize = 0;

	fseek(infile,0,SEEK_END);
	archiveSize = ftell(infile);
	rewind(infile);

	fread(header.magic, 1, 4, infile);
	fread(&header.fileCount, 1, 1, infile);
	fread(&header.unknown, 1, 1, infile);
	fread(&header.fileInfoOffset, 1, 2, infile);
	fread(&header.filenameTableOffset, 1, 2, infile);
	fread(&header.dataOffset, 1, 2, infile);
	fread(&header.fileInfoSize, 1, 2, infile);
	fread(&header.filenameTableSize, 1, 2, infile);
	fread(&header.dataSize, 1, 4, infile);

	header.fileInfoOffset *= 4;
	header.filenameTableOffset *= 4;
	header.dataOffset *= 4;
	header.fileInfoSize *= 4;
	header.filenameTableSize *= 4;
	header.dataSize *= 4;

	ParseFilenames(infile, header);
	ParseFileEntries(infile, header);

	// Create all of the possible directory paths in one go instead of trying to create 
	// each full path during the file dumping loop
	for(int i = 0; i < foldernames.size(); i++)
	{
		CreateFullPath(foldernames[i]);
	}

	std::string currentFolder = "";
	int dumped = 0;
	char *buffer = NULL;
	int bufferSize = 0;
	for(int i = 0; i < filenames.size(); i++)
	{
		if(filenames[i][filenames[i].size() - 1] == '/')
		{
			currentFolder = filenames[i];
		}
		else
		{
			std::string fullpath = currentFolder + filenames[i];
			unsigned int crc32 = CalculateCrc32((char*)filenames[i].c_str(), filenames[i].size());

			if(file_index.find(crc32) != file_index.end())
			{
				int idx = file_index[crc32];

				if(file_entries[idx].filesize > bufferSize)
				{
					bufferSize = file_entries[idx].filesize * 2;

					if(buffer == NULL)					
					{
						buffer = (char*)calloc(bufferSize, sizeof(char));
					}
					else
					{
						buffer = (char*)realloc(buffer, bufferSize);
					}
				}

				if(header.dataOffset + file_entries[idx].offset > archiveSize)
				{
					//printf("Couldn't seek passed end of file\n");
					continue;
				}

				fseek(infile,header.dataOffset + file_entries[idx].offset,SEEK_SET);
				fread(buffer, 1, file_entries[idx].filesize, infile);

				// Try to decompress data
				if(memcmp(buffer + 4, "\0DVLB", 5) == 0 || 
					memcmp(buffer + 4, "\0XPCK", 5) == 0 || 
					memcmp(buffer + 4, "\0CHRC", 5) == 0 || 
					memcmp(buffer + 4, "\0RESC", 5) == 0)
				{
					int length = *(int*)buffer;
					length /= 8;

					int output_len = 0;
					char *data = decompress(buffer, file_entries[idx].filesize, &output_len);

					// Replace the running buffer with the decompressed data's buffer.
					// Lazy way to handle this without changign the code after.
					free(buffer);
					buffer = data;

					file_entries[idx].filesize = output_len;
					bufferSize = output_len;
				}

				if(!quietMode)
				{
					printf("[%06d] %-38s size[%08x] offset[%08x]\n", dumped, fullpath.c_str(), file_entries[idx].filesize, file_entries[idx].offset);
				}

				dumped++;

				FILE *outfile = fopen(fullpath.c_str(), "wb");

				if(!outfile)
				{
					printf("Could not open %s\n", fullpath.c_str());
					exit(-1);
				}

				fwrite(buffer, 1, file_entries[idx].filesize, outfile);
				fclose(outfile);
			}
			else
			{
				printf("Could not find crc32 %08x: %s\n",crc32, filenames[i].c_str());
				exit(1);
			}
		}
	}

	if(buffer != NULL)
		free(buffer);
}