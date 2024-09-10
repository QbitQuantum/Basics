 * \f[ \prod_{k=0}^{K-1}\frac{\mathrm{poles}[k]-1}{\mathrm{poles}[k]-z^{-1}}
 = \frac{c[0]}{1+\sum_{k=1}^K c[k] z^{-k}}. \f]
 *
 * For handling the right boundary, the routine precomputes the inverse
 * to the linear system
 * \f[ u_{N-m} = b_0 q_{N-m} - \sum_{k=1}^K a_k \Tilde{u}_{N-m+k},
 \quad m=1,\ldots,K. \f]
 * The inverse is stored in matrix `c->M`, ordered such that
 * \f[ u_{N-K+m}=\sum_{n=0}^{K-1}M(m,n)\,q_{N-K+m},\quad m=0,\ldots,K-1. \f]
 */

template <typename T>
void vyv_precomp_(vyv_coeffs<T> *c, T sigma, int K, T tol)
{
	/* Optimized unscaled pole locations. */
	__declspec(align(16)) static const complex4c poles0[VYV_MAX_K - VYV_MIN_K + 1][5] = {
		{ { 1.4165, 1.00829 }, { 1.4165, -1.00829 }, { 1.86543, 0 } },
		{ { 1.13228, 1.28114 }, { 1.13228, -1.28114 },
		{ 1.78534, 0.46763 }, { 1.78534, -0.46763 } },
		{ { 0.8643, 1.45389 }, { 0.8643, -1.45389 },
		{ 1.61433, 0.83134 }, { 1.61433, -0.83134 }, { 1.87504, 0 } }
	};
	__declspec(align(16)) complex4c poles[VYV_MAX_K];
	double q;
	__declspec(align(16)) double filter[VYV_MAX_K + 1];
	__declspec(align(16)) double A[VYV_MAX_K * VYV_MAX_K], inv_A[VYV_MAX_K * VYV_MAX_K];
	int i, j, matrix_size;

	assert(c && sigma > 0 && VYV_VALID_K(K) && tol > 0);

	/* Make a crude initial estimate of q. */