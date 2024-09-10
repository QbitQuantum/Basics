filepos_t EbmlCrc32::ReadData(IOCallback & input, ScopeMode ReadFully)
{
	if (ReadFully != SCOPE_NO_DATA)
	{
		binary *Buffer = new binary[GetSize()];
		if (Buffer == NULL) {
			// impossible to read, skip it
			input.setFilePointer(GetSize(), seek_current);
		} else {
			input.readFully(Buffer, GetSize());

			memcpy((void *)&m_crc_final, Buffer, 4);
			delete [] Buffer;
			SetValueIsSet();
		}
	}

	return GetSize();
}