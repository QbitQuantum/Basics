ulong
getFPstatus(void)
{
	ulong fsr = 0, fsr32 = _statusfp();
	if(fsr32&_SW_INEXACT) fsr |= INEX;
	if(fsr32&_SW_OVERFLOW) fsr |= OVFL;
	if(fsr32&_SW_UNDERFLOW) fsr |= UNFL;
	if(fsr32&_SW_ZERODIVIDE) fsr |= ZDIV;
	if(fsr32&_SW_INVALID) fsr |= INVAL;
	return fsr;
}