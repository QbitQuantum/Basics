////////////////////////////////////////////////////////////////////////////////////////
// Make Sure Entire Vector Has Valid Numbers
////////////////////////////////////////////////////////////////////////////////////////
bool	CVec3::IsFinite()
{
#if defined(_MSC_VER) 
		return 	(_finite(v[0]) && _finite(v[1]) && _finite(v[2]));
#else
		return isfinite(v[0]) && isfinite(v[1]) && isfinite(v[2]);
#endif
}