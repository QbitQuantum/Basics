void*	MT_DoubleBuffer::Request(U32 dwSize){
	//if(GetCurrentThreadId()!=g_uiMainThreadId){
	//	OutputDebugStringA("More than One Thread Push Command!===============================================\n");
	//	//MessageBoxA(NULL,"More than One Thread Push Command!",NULL,NULL);
	//}

	U32& uiOffset	=	m_BufferOffset[m_uiWriteIndex];
	if(uiOffset	+	dwSize	>	m_BufferSize[m_uiWriteIndex]){
		ReAlloc(uiOffset	+	dwSize);
	}
	void*	p		=	&m_Buffer[m_uiWriteIndex][uiOffset];
	uiOffset		+=	dwSize;
	return	p;
};