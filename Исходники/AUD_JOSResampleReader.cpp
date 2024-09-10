static inline int lrint(double d)
{
		return _mm_cvtsd_si32(_mm_load_sd(&d));
}