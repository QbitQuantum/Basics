	void writeSRAM(const u32 pos, const u8 *data, u32 size) 
	{
		if (!fSRAM)
			return;

		fSRAM->fseek(pos, SEEK_SET);

		u32 writed = size;
		fSRAM->fwrite(data, size);
		fSRAM->fflush();
	}