void lis_quad_x87_fpu_finalize(unsigned int cw)
{
#ifdef HAS_X87_FPU
#ifdef _WIN32
    _control87(cw, 0xFFFFFFFF);
#else
	asm volatile ("fldcw %0": :"m" (cw));
#endif
#endif
}