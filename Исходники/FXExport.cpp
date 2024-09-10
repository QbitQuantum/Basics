void FX_PlayEffectID( int id, vec3_t org, vec3_t fwd, int vol, int rad, qboolean isPortal )
{
#ifdef __FXCHECKER
	if (_isnan(org[0]) || _isnan(org[1]) || _isnan(org[2]))
	{
		assert(0);
	}
	if (_isnan(fwd[0]) || _isnan(fwd[1]) || _isnan(fwd[2]))
	{
		assert(0);
	}
	if (fabs(fwd[0]) < 0.1 && fabs(fwd[1]) < 0.1 && fabs(fwd[2]) < 0.1)
	{
		assert(0);
	}
#endif // __FXCHECKER

	theFxScheduler.PlayEffect(id, org, fwd, vol, rad, !!isPortal );
}