void RijndaelEncrypt(RijndaelContextPtr context,void* pInput,unsigned int nSize,void* pOutput)
{
	unsigned int i;
	//需要计算的最小长度
	unsigned int plainSize = context->plainSize;
	if (nSize % plainSize != 0)
	{
		nSize += plainSize - (nSize % plainSize);
		//清0
		memset((unsigned char*)pOutput + nSize,0,plainSize - (nSize % plainSize));
	}
	for (i=0; i<nSize; i += plainSize)
	{
		memcpy((unsigned char*)pOutput + i,(unsigned char*)pInput + i,plainSize);
		Encrypt(context,(unsigned char*)pOutput + i);
	}
}