	extern "C" int __cdecl __isnanf(float x)
	{
		return _finitef(x)?0:1;
	}