// set data to network byte order
void CCapsLoader::Swap(PUDWORD buf, int cnt)
{
#ifdef INTEL
	for (cnt>>=2; cnt > 0; cnt--, buf++) {
		UDWORD src=*buf;
		UDWORD dst=_lrotl(src, 8)&0x00ff00ff | _lrotr(src, 8)&0xff00ff00;
		*buf=dst;
	}
#endif
}