SHVStringBufferUTF8 SHVStringUTF8::Copy(const TPtrC8& aPtr)
{
SHVStringBufferUTF8 retVal;
size_t len = aPtr.Length();

	if (len)
	{
		retVal.Buffer = (SHVChar*)::malloc((len+1)*sizeof(SHVChar));
		if (retVal.Buffer)
		{
			memcpy(retVal.Buffer, aPtr.Ptr(), len*sizeof(SHVChar));
			retVal.Buffer[len] = 0;
		}
	}

	return retVal;
}