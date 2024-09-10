bool Math::is_inf(double p_val) {

#ifdef _MSC_VER
	return !_finite(p_val);
#else
	return isinf(p_val);
#endif

}