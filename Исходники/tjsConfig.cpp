void TJSRestoreFPUE()
{

#if defined(__WIN32__) && !defined(__GNUC__)
	if(!TJSFPUInit) return;
	_control87(TJSDefaultFPUCW, 0xffff);
#endif
}