physx::shdfnd::FPUGuard::~FPUGuard()
{
	_clearfp();

#if defined(PX_X64) || defined(PX_WINMODERN)
	// reset FP state
	unsigned int cw;
	_controlfp_s(&cw, *mControlWords, _MCW_ALL);
#else
	
	// reset FP state
	unsigned int x87, sse;
	__control87_2(mControlWords[0], _MCW_ALL, &x87, 0);
	__control87_2(mControlWords[1], _MCW_ALL, 0, &sse);
#endif
}