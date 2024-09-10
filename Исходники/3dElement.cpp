Vertex Vertex::muladd(const float & n, const Vertex & v) const
{
#ifdef FMA
	__m128 tmp = _mm_set1_ps(n);
	return _mm_fmadd_ps(dat, tmp, v);
#else
	return Vertex();
#endif
}