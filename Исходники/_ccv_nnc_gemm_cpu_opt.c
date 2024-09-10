static int _ccv_nnc_gemm_forw_sse2(const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_view_t* const w, const ccv_nnc_tensor_view_t* const bias, ccv_nnc_tensor_view_t* const b)
{
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	const int* adim = (a_nd == 1) ? a->info.dim : a->info.dim + 1;
	const int b_nd = ccv_nnc_tensor_nd(b->info.dim);
	const int* bdim = (b_nd == 1) ? b->info.dim : b->info.dim + 1;
	assert(bdim[0] == bias->info.dim[0]);
	assert(bdim[0] == w->info.dim[0]);
	assert(adim[0] == w->info.dim[1]);
	const int* ainc = CCV_IS_TENSOR_VIEW(a) ? (a_nd == 1 ? a->inc : a->inc + 1) : adim;
	const int* binc = CCV_IS_TENSOR_VIEW(b) ? (b_nd == 1 ? b->inc : b->inc + 1) : bdim;
	const int* winc = CCV_IS_TENSOR_VIEW(w) ? w->inc : w->info.dim;
	const int batch_size = a_nd == 1 ? 1 : ccv_max(1, a->info.dim[0]);
	int i;
	for (i = 0; i < batch_size; i++)
	{
		const float* const ap = a->data.f32 + i * ainc[0];
		float* const bp = b->data.f32 + i * binc[0];
		parallel_for(j, bdim[0]) {
			const float* const wp = w->data.f32 + j * winc[1];
			int k;
			__m128 v40 = _mm_set_ss(bias->data.f32[j]);
			__m128 v41 = _mm_setzero_ps();
			for (k = 0; k < adim[0] - 7; k += 8)
			{
				__m128 ap40 = _mm_load_ps(ap + k);
				__m128 ap41 = _mm_load_ps(ap + k + 4);
				__m128 w40 = _mm_load_ps(wp + k);
				__m128 w41 = _mm_load_ps(wp + k + 4);
				v40 =_mm_add_ps(_mm_mul_ps(w40, ap40), v40);
				v41 =_mm_add_ps(_mm_mul_ps(w41, ap41), v41);
			}
			v40 = _mm_add_ps(v40, v41);
			v41 = _mm_add_ps(v40, _mm_movehl_ps(v40, v40));
			v40 = _mm_add_ss(v41, _mm_shuffle_ps(v41, v41, 1));
			_mm_store_ss(bp + j, v40);
		} parallel_endfor
	}
	return CCV_NNC_EXEC_SUCCESS;
}