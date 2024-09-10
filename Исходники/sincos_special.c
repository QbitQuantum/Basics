float _sinf_cosf_special(float x, char *name)
{
    UT32 xu;
	unsigned int is_snan;

	xu.f32 = x;

    if((xu.u32 & EXPBITS_SP32) == EXPBITS_SP32)
    {
        // x is Inf or NaN
        if((xu.u32 & MANTBITS_SP32) == 0x0)
        {
            // x is Inf	
            _mm_setcsr(_mm_getcsr() | MXCSR_ES_INVALID);
#ifdef WIN64
            xu.u32 = INDEFBITPATT_SP32;
			__amd_handle_errorf(DOMAIN, EDOM, name, x, 0, 0.0f, 0, xu.f32, 0);
#else
			xu.u32 = QNANBITPATT_SP32; 
            name = *(&name); // dummy statement to avoid warning
#endif
		}
		else {
			// x is NaN
            is_snan = (((xu.u32 & QNAN_MASK_32) == QNAN_MASK_32) ? 0 : 1);
			if(is_snan) {
				xu.u32 |= QNAN_MASK_32;
				_mm_setcsr(_mm_getcsr() | MXCSR_ES_INVALID);
			}
#ifdef WIN64
			__amd_handle_errorf(DOMAIN, EDOM, name, x, is_snan, 0.0f, 0, xu.f32, 0);
#endif
		}
		
	}

	return xu.f32;
}