int wmain(int argc, WCHAR* argv[]) {

	
	
	if (!pipeline.LoopFrames()) wprintf_s(L"Failed to intialize or stream data\n"); 
    return 0;
}