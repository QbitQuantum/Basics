void SpringEmbedderFRExact::mainStep_sse3(ArrayGraph &C)
{
//#if (defined(OGDF_ARCH_X86) || defined(OGDF_ARCH_X64)) && !(defined(__GNUC__) && !defined(__SSE3__))
#ifdef OGDF_SSE3_EXTENSIONS

	const int n            = C.numberOfNodes();

#ifdef _OPENMP
	const int work = 256;
	const int nThreadsRep  = min(omp_get_max_threads(), 1 + n*n/work);
	const int nThreadsPrev = min(omp_get_max_threads(), 1 + n  /work);
#endif

	const double k       = m_idealEdgeLength;
	const double kSquare = k*k;
	const double c_rep   = 0.052 * kSquare; // 0.2 = factor for repulsive forces as suggested by Warshal

	const double minDist       = 10e-6;//100*DBL_EPSILON;
	const double minDistSquare = minDist*minDist;

	double *disp_x = (double*) System::alignedMemoryAlloc16(n*sizeof(double));
	double *disp_y = (double*) System::alignedMemoryAlloc16(n*sizeof(double));

	__m128d mm_kSquare       = _mm_set1_pd(kSquare);
	__m128d mm_minDist       = _mm_set1_pd(minDist);
	__m128d mm_minDistSquare = _mm_set1_pd(minDistSquare);
	__m128d mm_c_rep         = _mm_set1_pd(c_rep);

	#pragma omp parallel num_threads(nThreadsRep)
	{
		double tx = m_txNull;
		double ty = m_tyNull;
		int cF = 1;

		for(int i = 1; i <= m_iterations; i++)
		{
			// repulsive forces

			#pragma omp for
			for(int v = 0; v < n; ++v)
			{
				__m128d mm_disp_xv = _mm_setzero_pd();
				__m128d mm_disp_yv = _mm_setzero_pd();

				__m128d mm_xv = _mm_set1_pd(C.m_x[v]);
				__m128d mm_yv = _mm_set1_pd(C.m_y[v]);

				int u;
				for(u = 0; u+1 < v; u += 2)
				{
					__m128d mm_delta_x = _mm_sub_pd(mm_xv, _mm_load_pd(&C.m_x[u]));
					__m128d mm_delta_y = _mm_sub_pd(mm_yv, _mm_load_pd(&C.m_y[u]));

					__m128d mm_distSquare = _mm_max_pd(mm_minDistSquare,
						_mm_add_pd(_mm_mul_pd(mm_delta_x,mm_delta_x),_mm_mul_pd(mm_delta_y,mm_delta_y))
					);

					__m128d mm_t = _mm_div_pd(_mm_load_pd(&C.m_nodeWeight[u]), mm_distSquare);
					mm_disp_xv = _mm_add_pd(mm_disp_xv, _mm_mul_pd(mm_delta_x, mm_t));
					mm_disp_yv = _mm_add_pd(mm_disp_yv, _mm_mul_pd(mm_delta_y, mm_t));
					//mm_disp_xv = _mm_add_pd(mm_disp_xv, _mm_mul_pd(mm_delta_x, _mm_div_pd(mm_kSquare,mm_distSquare)));
					//mm_disp_yv = _mm_add_pd(mm_disp_yv, _mm_mul_pd(mm_delta_y, _mm_div_pd(mm_kSquare,mm_distSquare)));
				}
				int uStart = u+2;
				if(u == v) ++u;
				if(u < n) {
					__m128d mm_delta_x = _mm_sub_sd(mm_xv, _mm_load_sd(&C.m_x[u]));
					__m128d mm_delta_y = _mm_sub_sd(mm_yv, _mm_load_sd(&C.m_y[u]));

					__m128d mm_distSquare = _mm_max_sd(mm_minDistSquare,
						_mm_add_sd(_mm_mul_sd(mm_delta_x,mm_delta_x),_mm_mul_sd(mm_delta_y,mm_delta_y))
					);

					__m128d mm_t = _mm_div_sd(_mm_load_sd(&C.m_nodeWeight[u]), mm_distSquare);
					mm_disp_xv = _mm_add_sd(mm_disp_xv, _mm_mul_sd(mm_delta_x, mm_t));
					mm_disp_yv = _mm_add_sd(mm_disp_yv, _mm_mul_sd(mm_delta_y, mm_t));
					//mm_disp_xv = _mm_add_sd(mm_disp_xv, _mm_mul_sd(mm_delta_x, _mm_div_sd(mm_kSquare,mm_distSquare)));
					//mm_disp_yv = _mm_add_sd(mm_disp_yv, _mm_mul_sd(mm_delta_y, _mm_div_sd(mm_kSquare,mm_distSquare)));
				}

				for(u = uStart; u < n; u += 2)
				{
					__m128d mm_delta_x = _mm_sub_pd(mm_xv, _mm_load_pd(&C.m_x[u]));
					__m128d mm_delta_y = _mm_sub_pd(mm_yv, _mm_load_pd(&C.m_y[u]));

					__m128d mm_distSquare = _mm_max_pd(mm_minDistSquare,
						_mm_add_pd(_mm_mul_pd(mm_delta_x,mm_delta_x),_mm_mul_pd(mm_delta_y,mm_delta_y))
					);

					__m128d mm_t = _mm_div_pd(_mm_load_pd(&C.m_nodeWeight[u]), mm_distSquare);
					mm_disp_xv = _mm_add_pd(mm_disp_xv, _mm_mul_pd(mm_delta_x, mm_t));
					mm_disp_yv = _mm_add_pd(mm_disp_yv, _mm_mul_pd(mm_delta_y, mm_t));
					//mm_disp_xv = _mm_add_pd(mm_disp_xv, _mm_mul_pd(mm_delta_x, _mm_div_pd(mm_kSquare,mm_distSquare)));
					//mm_disp_yv = _mm_add_pd(mm_disp_yv, _mm_mul_pd(mm_delta_y, _mm_div_pd(mm_kSquare,mm_distSquare)));
				}
				if(u < n) {
					__m128d mm_delta_x = _mm_sub_sd(mm_xv, _mm_load_sd(&C.m_x[u]));
					__m128d mm_delta_y = _mm_sub_sd(mm_yv, _mm_load_sd(&C.m_y[u]));

					__m128d mm_distSquare = _mm_max_sd(mm_minDistSquare,
						_mm_add_sd(_mm_mul_sd(mm_delta_x,mm_delta_x),_mm_mul_sd(mm_delta_y,mm_delta_y))
					);

					__m128d mm_t = _mm_div_sd(_mm_load_sd(&C.m_nodeWeight[u]), mm_distSquare);
					mm_disp_xv = _mm_add_sd(mm_disp_xv, _mm_mul_sd(mm_delta_x, mm_t));
					mm_disp_yv = _mm_add_sd(mm_disp_yv, _mm_mul_sd(mm_delta_y, mm_t));
					//mm_disp_xv = _mm_add_sd(mm_disp_xv, _mm_mul_sd(mm_delta_x, _mm_div_sd(mm_kSquare,mm_distSquare)));
					//mm_disp_yv = _mm_add_sd(mm_disp_yv, _mm_mul_sd(mm_delta_y, _mm_div_sd(mm_kSquare,mm_distSquare)));
				}

				mm_disp_xv = _mm_hadd_pd(mm_disp_xv,mm_disp_xv);
				mm_disp_yv = _mm_hadd_pd(mm_disp_yv,mm_disp_yv);

				_mm_store_sd(&disp_x[v], _mm_mul_sd(mm_disp_xv, mm_c_rep));
				_mm_store_sd(&disp_y[v], _mm_mul_sd(mm_disp_yv, mm_c_rep));
			}

			// attractive forces

			#pragma omp single
			for(int e = 0; e < C.numberOfEdges(); ++e)
			{
				int v = C.m_src[e];
				int u = C.m_tgt[e];

				double delta_x = C.m_x[v] - C.m_x[u];
				double delta_y = C.m_y[v] - C.m_y[u];

				double dist = max(minDist, sqrt(delta_x*delta_x + delta_y*delta_y));

				disp_x[v] -= delta_x * dist / k;
				disp_y[v] -= delta_y * dist / k;

				disp_x[u] += delta_x * dist / k;
				disp_y[u] += delta_y * dist / k;
			}

			// limit the maximum displacement to the temperature (m_tx,m_ty)

			__m128d mm_tx = _mm_set1_pd(tx);
			__m128d mm_ty = _mm_set1_pd(ty);

			#pragma omp for nowait
			for(int v = 0; v < n-1; v += 2)
			{
				__m128d mm_disp_xv = _mm_load_pd(&disp_x[v]);
				__m128d mm_disp_yv = _mm_load_pd(&disp_y[v]);

				__m128d mm_dist = _mm_max_pd(mm_minDist, _mm_sqrt_pd(
					_mm_add_pd(_mm_mul_pd(mm_disp_xv,mm_disp_xv),_mm_mul_pd(mm_disp_yv,mm_disp_yv))
				));

				_mm_store_pd(&C.m_x[v], _mm_add_pd(_mm_load_pd(&C.m_x[v]),
					_mm_mul_pd(_mm_div_pd(mm_disp_xv, mm_dist), _mm_min_pd(mm_dist,mm_tx))
				));
				_mm_store_pd(&C.m_y[v], _mm_add_pd(_mm_load_pd(&C.m_y[v]),
					_mm_mul_pd(_mm_div_pd(mm_disp_yv, mm_dist), _mm_min_pd(mm_dist,mm_ty))
				));
			}
			#pragma omp single nowait
			{
				if(n % 2) {
					int v = n-1;
					double dist = max(minDist, sqrt(disp_x[v]*disp_x[v] + disp_y[v]*disp_y[v]));

					C.m_x[v] += disp_x[v] / dist * min(dist,tx);
					C.m_y[v] += disp_y[v] / dist * min(dist,ty);
				}
			}

			cool(tx,ty,cF);

			#pragma omp barrier
		}
	}

	System::alignedMemoryFree(disp_x);
	System::alignedMemoryFree(disp_y);

#else
	mainStep(C);
#endif
}