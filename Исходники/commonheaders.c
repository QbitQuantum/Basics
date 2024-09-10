int mir_realloc_proxy(void *ptr,int size)
{
	if (IsBadCodePtr((FARPROC)ptr))
	{
		char buf[256];
		mir_snprintf(buf,sizeof(buf),"Bad code ptr in mir_realloc_proxy ptr: %x\r\n",ptr);
		//ASSERT("Bad code ptr");
		DebugBreak();
		TRACE(buf);
		return 0;
	}
	memoryManagerInterface.mmi_realloc(ptr,size);
	return 0;

}