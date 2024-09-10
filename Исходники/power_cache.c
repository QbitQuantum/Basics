static void inline sse_sum_unaligned_F(int count, float *partial, float *accum)
{
#if MANUAL_SSE
#if USE_AVX
int i;
__m256 v8in, v8acc;

//fprintf(stderr, "unaligned %d %p %p\n", i, partial, accum);
for(i=0; ((long)&(accum[i]) & 0x0f) && (i<count);i++) {
	accum[i]+=partial[i];
	}

PRAGMA_IVDEP
for(;i<(count-7);i+=8) {
	v8in=_mm256_loadu_ps(&(partial[i]));
	v8acc=_mm256_load_ps(&(accum[i]));
	v8acc=_mm256_add_ps(v8acc, v8in);
	_mm256_store_ps(&(accum[i]), v8acc);
	}

PRAGMA_IVDEP
for(;i<count;i++) {
	accum[i]+=partial[i];
	}
#else
int i;
__m128 v4in, v4acc;
float *tmp=aligned_alloca(16*sizeof(*tmp));

for(i=0; ((long)&(accum[i]) & 0x0f) && (i<count);i++) {
	accum[i]+=partial[i];
	}

//fprintf(stderr, "unaligned %d %p %p\n", i, partial, accum);

PRAGMA_IVDEP
for(;i<(count-15);i+=16) {
	memcpy(tmp, &(partial[i]), 16*sizeof(*tmp));

	v4in=_mm_load_ps(tmp);
	v4acc=_mm_load_ps(&(accum[i]));
	v4acc=_mm_add_ps(v4acc, v4in);
	_mm_store_ps(&(accum[i]), v4acc);

	v4in=_mm_load_ps(&(tmp[4]));
	v4acc=_mm_load_ps(&(accum[i+4]));
	v4acc=_mm_add_ps(v4acc, v4in);
	_mm_store_ps(&(accum[i+4]), v4acc);

	v4in=_mm_load_ps(&(tmp[8]));
	v4acc=_mm_load_ps(&(accum[i+8]));
	v4acc=_mm_add_ps(v4acc, v4in);
	_mm_store_ps(&(accum[i+8]), v4acc);

	v4in=_mm_load_ps(&(tmp[12]));
	v4acc=_mm_load_ps(&(accum[i+12]));
	v4acc=_mm_add_ps(v4acc, v4in);
	_mm_store_ps(&(accum[i+12]), v4acc);
	}

PRAGMA_IVDEP
for(;i<count;i++) {
	accum[i]+=partial[i];
	}
#endif
#else
fprintf(stderr, "**** MANUAL_SSE disabled in %s\n", __FUNCTION__);
exit(-2);
#endif
}