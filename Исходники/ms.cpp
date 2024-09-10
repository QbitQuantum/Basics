			extern "C" YEP_PRIVATE_SYMBOL double sqrt(double x) {
				const __m128d xmm = _mm_set_sd(x);
				return _mm_cvtsd_f64(_mm_sqrt_sd(xmm, xmm));
			}