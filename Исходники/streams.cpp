	void           CStream::WriteInt(int nValue)
	{
		//int nLen = 0;
		//const char* sString = NSFastIntToString::GetString(fabs(nValue), nLen);
		//if (sString)
		//{
		//	if (nValue < 0)
		//		WriteChar('-');

		//	Write((const BYTE*)sString, nLen);
		//}
		//else
		//{
			char pBuffer[32];
			memset(pBuffer, 0x00, 32);
			ItoA(pBuffer, nValue, pBuffer + 31);
			return WriteStr(pBuffer);
		//}
	}