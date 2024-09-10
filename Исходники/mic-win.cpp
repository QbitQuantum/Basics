static bool dataChunk(EMUFILE &inf)
{
	bool found = false;

	// seek to just after the RIFF header
	inf.fseek(12,SEEK_SET);

	// search for a format chunk
	for (;;)
	{
		char chunk_id[4];
		u32  chunk_length;

		if (inf.eof()) return found;
		if (inf.fread(chunk_id, 4) != 4) return found;
		if (!inf.read_32LE(chunk_length)) return found;

		// if we found a data chunk, excellent!
      if (memcmp(chunk_id, "data", 4) == 0)
	  {
		  found = true;
		  u8 *temp = new u8[chunk_length];
		  if (inf.fread(temp,chunk_length) != chunk_length)
		  {
			  delete[] temp;
			  return false;
		  }
		  newWavData.fwrite(temp,chunk_length);
		  delete[] temp;
		  chunk_length = 0;
	  }

	  inf.fseek(chunk_length,SEEK_CUR);
	}

	return found;
}