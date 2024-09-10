	void encryptMessage(SecBufferArray<1>& secBufferArray)
	{
		EncryptMessage(&contextHandle_, 0, &secBufferArray.getDescriptor(), 0);
	}