DWORDLONG Target::Rand(DWORDLONG limit)
{
#if defined(IOMTR_OSFAMILY_UNIX) && defined(WORKAROUND_MOD_BUG)
	return ((DWORDLONG)fmodl(spec.random = A * spec.random + B, limit));
#else
#ifdef _DEBUG
	assert(limit > 0);
#endif
	return (spec.random = A * spec.random + B) % limit;
#endif
}