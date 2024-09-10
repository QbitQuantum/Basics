void Traverso::setup_fpu()
{

	// export TRAVERSO_RUNNING_UNDER_VALGRIND to disable assembler stuff below!
	if (getenv("TRAVERSO_RUNNING_UNDER_VALGRIND")) {
		printf("TRAVERSO_RUNNING_UNDER_VALGRIND=TRUE\n");
		// valgrind doesn't understand this assembler stuff
		// September 10th, 2007
		return;
	}

#if (defined(ARCH_X86) || defined(ARCH_X86_64)) && defined(USE_XMMINTRIN)
        
	int MXCSR;
	FPU fpu;

	/* XXX use real code to determine if the processor supports
	DenormalsAreZero and FlushToZero
	*/
	
	if (!fpu.has_flush_to_zero() && !fpu.has_denormals_are_zero()) {
		return;
	}

	MXCSR  = _mm_getcsr();

/*	switch (Config->get_denormal_model()) {
		case DenormalNone:
			MXCSR &= ~(_MM_FLUSH_ZERO_ON|0x8000);
			break;

		case DenormalFTZ:
			if (fpu.has_flush_to_zero()) {
				MXCSR |= _MM_FLUSH_ZERO_ON;
			}
			break;

		case DenormalDAZ:*/
			MXCSR &= ~_MM_FLUSH_ZERO_ON;
			if (fpu.has_denormals_are_zero()) {
				MXCSR |= 0x8000;
			}
// 			break;
// 		
// 		case DenormalFTZDAZ:
// 			if (fpu.has_flush_to_zero()) {
// 				if (fpu.has_denormals_are_zero()) {
// 					MXCSR |= _MM_FLUSH_ZERO_ON | 0x8000;
// 				} else {
// 					MXCSR |= _MM_FLUSH_ZERO_ON;
// 				}
// 			}
// 			break;
// 	}

	_mm_setcsr (MXCSR);

#endif
}