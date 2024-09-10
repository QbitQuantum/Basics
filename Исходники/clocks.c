uint64_t _MCFCRT_GetFastMonoClock(void){
	return GetTickCount64() + MONO_CLOCK_OFFSET * 3;
}