uint64 EbmlString::ReadData(IOCallback & input, ScopeMode ReadFully)
{
	if (ReadFully != SCOPE_NO_DATA)
	{
		if (Size == 0) {
			Value = "";
			bValueIsSet = true;
		} else {
			char *Buffer = new char[Size + 1];
			if (Buffer == NULL) {
				// unable to store the data, skip it
				input.setFilePointer(Size, seek_current);
			} else {
				input.readFully(Buffer, Size);
				if (Buffer[Size-1] != '\0') {
					Buffer[Size] = '\0';
				}
				Value = Buffer;
				delete [] Buffer;
				bValueIsSet = true;
			}
		}
	}

	return Size;
}