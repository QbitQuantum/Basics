u32 systemGetClock()
{
	if ( GetTickCount64() > 4294967296 )
		return 0;
	return (u32)GetTickCount64();
}