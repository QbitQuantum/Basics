	Stream* Stream::Deserialize(bool decompress)
	{
		Stream* value = new Stream();
		unsigned int length = ReadDword();
		StreamBuffer tmpBuffer(length, 0);
		ReadData(tmpBuffer);
		value->WriteData(tmpBuffer);
		value->Rewind();
		if (decompress)
			value->Inflate();
		return value;
	}