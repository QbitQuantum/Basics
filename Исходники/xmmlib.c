/*---------------------------------------------------------------------------
// 16Byte Allignment calloc
//-------------------------------------------------------------------------*/
void* xmm_calloc(size_t nitems, size_t size)
{
	unsigned char*	t_RetPtr	 = (unsigned char*)_aligned_malloc(nitems*size, 16);

	if(t_RetPtr)
	{
#ifdef	__SSE__
		size_t	i,j, k;
		__m128	XMM0, XMM1, XMM2, XMM3;
		XMM0	 = 
		XMM1	 = 
		XMM2	 = 
		XMM3	 = _mm_setzero_ps();
		k	 = nitems*size;
		j	 = k&(~127);
		for(i=0;i<j;i+=128)
		{
			_mm_stream_ps((float*)(t_RetPtr+i    ), XMM0);
			_mm_stream_ps((float*)(t_RetPtr+i+ 16), XMM1);
			_mm_stream_ps((float*)(t_RetPtr+i+ 32), XMM2);
			_mm_stream_ps((float*)(t_RetPtr+i+ 48), XMM3);
			_mm_stream_ps((float*)(t_RetPtr+i+ 64), XMM0);
			_mm_stream_ps((float*)(t_RetPtr+i+ 80), XMM1);
			_mm_stream_ps((float*)(t_RetPtr+i+ 96), XMM2);
			_mm_stream_ps((float*)(t_RetPtr+i+112), XMM3);
		}
		j	 = k&(~63);
		for(;i<j;i+=64)
		{
			_mm_stream_ps((float*)(t_RetPtr+i    ), XMM0);
			_mm_stream_ps((float*)(t_RetPtr+i+ 16), XMM1);
			_mm_stream_ps((float*)(t_RetPtr+i+ 32), XMM2);
			_mm_stream_ps((float*)(t_RetPtr+i+ 48), XMM3);
		}
		j	 = k&(~31);
		for(;i<j;i+=32)
		{
			_mm_stream_ps((float*)(t_RetPtr+i    ), XMM0);
			_mm_stream_ps((float*)(t_RetPtr+i+ 16), XMM1);
		}
		j	 = k&(~15);
		for(;i<j;i+=16)
		{
			_mm_stream_ps((float*)(t_RetPtr+i    ), XMM0);
		}
		j	 = k&(~7);
		for(;i<j;i+=8)
		{
			_mm_storel_pi((__m64*)(t_RetPtr+i   ), XMM0);
		}
		j	 = k&(~3);
		for(;i<j;i+=4)
		{
			_mm_store_ss((float*)(t_RetPtr+i)   , XMM0);
		}
		for(;i<k;i++)
			*(t_RetPtr+i    )	 = 0;
		_mm_sfence();
#else
		memset(t_RetPtr, 0, nitems*size);
#endif
	}
	return	(void*)t_RetPtr;
}