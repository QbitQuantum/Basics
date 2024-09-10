//_______________________________________________________________________________________________________________________
///
/// \brief min-mod function, see Eq. (16.52) in Randall LeVeque. Numerical Methods for Conservation Laws (1992)
///
static inline double minmod(const double a, const double b)
{
	return 0.5 * (copysign(1, a) + copysign(1, b)) * minf(fabs(a), fabs(b));
}