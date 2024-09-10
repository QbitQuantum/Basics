tAsyncCall* System_IO_FileInternal_GetCurrentDirectory(PTR pThis_, PTR pParams, PTR pReturnValue) {
	U32 *pError = ((U32**)pParams)[0];
	HEAP_PTR curDir;
#ifdef WIN32
	unsigned short dir[256];
	GetCurrentDirectoryW(256, dir);
	curDir = SystemString_FromCharPtrUTF16(dir);
#else
	unsigned char dir[256];
	getcwd(dir, 256);
	curDir = SystemString_FromCharPtrASCII(dir);
#endif
	*pError = 0;
	*(HEAP_PTR*)pReturnValue = curDir;
	return NULL;
}