void YabThreadSetCurrentThreadAffinityMask(int mask)
{
	SetThreadIdealProcessor(GetCurrentThread(), mask);
}