	Stream* Gmkrypt::Decrypt(Stream* stream)
	{
		Stream* value = new Stream();

		unsigned int c = stream->GetPosition() + 1;

		value->WriteByte(stream->ReadByte());
		while(stream->GetPosition() < stream->GetLength())
		{
			Stream::StreamBuffer buffer(512);
			stream->ReadData(buffer);

			for(int i = 0; i < 512; ++i)
				buffer[i] = (table[1][(int)buffer[i]] - c++) & 0xFF;

			value->WriteData(buffer);
		}

		value->Rewind();

		return value;
	}