void sc_SetDenormalFlags()
{
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
	_mm_setcsr(_mm_getcsr() | 0x40); // DAZ
}