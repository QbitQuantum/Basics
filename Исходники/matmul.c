void *calculate_row(void *thread_id)
{
	long id = (long)thread_id;
	int i, j, ii, jj, ii_limit, jj_limit, l, start_i, end_i, jj_limit_minus_3;
	__m128 a_line, b_line, r_line;
	const float *A = matrix_a, *B= matrix_b;
	const int n = matrix_n, m = matrix_m, k = matrix_k;
	float *row_in_B, *row_in_C, ii_l_in_A;

	start_i = row_per_thread * id;
	end_i = row_per_thread * (id + 1);
	if(end_i >= m)
		end_i = m;
	
	for(i = start_i ; i < end_i ; i += TILE_SIZE) // i: row block index in C 
	{
		ii_limit = min(end_i, i + TILE_SIZE);

		for(j = 0 ; j < n ; j += TILE_SIZE2) // j : col block index in C
		{
			jj_limit = min(n, j + TILE_SIZE2);
			jj_limit_minus_3 = jj_limit - 3;

			for(l = 0; l < k; ++l)
			{
				row_in_B = B + l*n;
				for(ii = i ; ii < ii_limit; ++ii)
				{
					ii_l_in_A = A[ii * k + l];
					a_line = _mm_set1_ps(ii_l_in_A); //A[ii * k + l]);  
					row_in_C = matrix_c + ii * n;
					for(jj = j; jj < jj_limit_minus_3 ; jj += 4)
					{
						b_line = _mm_loadu_ps(row_in_B + jj);
						r_line = _mm_loadu_ps(row_in_C + jj);
						_mm_storeu_ps(row_in_C + jj, _mm_add_ps(_mm_mul_ps(a_line, b_line), r_line));
					}
					for(; jj < jj_limit; ++jj)
					{
						*(row_in_C + jj) += ii_l_in_A * *(row_in_B + jj);
					}
				}
			}
		}
	}
	pthread_exit(NULL);
}