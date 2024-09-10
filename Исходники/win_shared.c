static int IsMMX( void )
{
	unsigned regs[4];

	// get CPU feature bits
	__cpuid( regs, 1 );

	// bit 23 of EDX denotes MMX existence
	if ( regs[3] & ( 1 << 23 ) )
		return qtrue;
	return qfalse;
}