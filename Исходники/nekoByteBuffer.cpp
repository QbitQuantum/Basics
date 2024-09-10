	/// Compress data by Zlib
	bool nekoByteBuffer::Compress(int32 level)
	{
		nekoAssert(level >= 0 && level <= 9, "압축 레벨은 0과 9 사이의 정수 입니다.");

		// No data
		if(!length)
			return false;

		// Compress it.
		int32 destLen;
		char8 *destData = nekoNew char8[(destLen = (int32)((length + 12) * 1.1)) + sizeof(int32)];
		if(compress2((Bytef *)(destData + sizeof(int32)), (uLongf *)&destLen, (Bytef *)buf, (uLongf)length, level) != Z_OK)
		{
			delete []destData;
			return false;
		}

		SafeDeleteArray(buf);

		// 앞부분에 원래 길이 넣어두기
		memcpy(destData, &length, sizeof(int32));
		buf = destData;
		length = destLen + sizeof(int32);
		writePos = length;
		return true;
	}