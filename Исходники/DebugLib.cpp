	void FBOutputDebugString(const char* msg){
#if defined(_PLATFORM_WINDOWS_)
		OutputDebugStringA(msg);		
#else
#endif
	}