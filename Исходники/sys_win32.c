void Sys_SetFloatEnv(void)
{
	_controlfp(FPUCW, FPUCWMASK);
}