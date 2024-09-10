void disable_fpexcept(void)
{
	_clearfp();
	_controlfp(_controlfp(0, 0) | (_EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW), _MCW_EM);
}