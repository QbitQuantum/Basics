int cellJpgDecReadHeader(u32 mainHandle, u32 subHandle, mem_ptr_t<CellJpgDecInfo> info)
{
	cellJpgDec.Log("cellJpgDecReadHeader(mainHandle=0x%x, subHandle=0x%x, info_addr=0x%llx)", mainHandle, subHandle, info.GetAddr());

	if (!info.IsGood())
		return CELL_JPGDEC_ERROR_ARG;

	CellJpgDecSubHandle* subHandle_data;
	if(!cellJpgDec.CheckId(subHandle, subHandle_data))
		return CELL_JPGDEC_ERROR_FATAL;

	const u32& fd = subHandle_data->fd;
	const u64& fileSize = subHandle_data->fileSize;
	CellJpgDecInfo& current_info = subHandle_data->info;

	//Copy the JPG file to a buffer
	MemoryAllocator<u8> buffer(fileSize);
	MemoryAllocator<be_t<u64>> pos, nread;

	cellFsLseek(fd, 0, CELL_SEEK_SET, pos);
	cellFsRead(fd, buffer.GetAddr(), buffer.GetSize(), nread);

	if (*buffer.To<u32>(0) != 0xE0FFD8FF || // Error: Not a valid SOI header
		*buffer.To<u32>(6) != 0x4649464A)   // Error: Not a valid JFIF string
	{
		return CELL_JPGDEC_ERROR_HEADER; 
	}

	u32 i = 4;
	
	if(i >= fileSize)
		return CELL_JPGDEC_ERROR_HEADER;

	u16 block_length = buffer[i] * 0xFF + buffer[i+1];

	while(true)
	{
		i += block_length;                                  // Increase the file index to get to the next block
		if (i >= fileSize ||                                // Check to protect against segmentation faults
			buffer[i] != 0xFF)                              // Check that we are truly at the start of another block
		{
			return CELL_JPGDEC_ERROR_HEADER;
		}

		if(buffer[i+1] == 0xC0)
			break;                                          // 0xFFC0 is the "Start of frame" marker which contains the file size

		i += 2;                                             // Skip the block marker
		block_length = buffer[i] * 0xFF + buffer[i+1];      // Go to the next block
	}

	current_info.imageWidth    = buffer[i+7]*0x100 + buffer[i+8];
	current_info.imageHeight   = buffer[i+5]*0x100 + buffer[i+6];
	current_info.numComponents = 3; // Unimplemented
	current_info.colorSpace    = CELL_JPG_RGB;

	*info = current_info;

	return CELL_OK;
}