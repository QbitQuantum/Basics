static void quantize_block(const float *in_data, float *out_data, float *quant_tbl)
{
	int zigzag;

	__m256 result, dct_values, quant_values;
	__m256 factor = _mm256_set1_ps(0.25f);

	for (zigzag = 0; zigzag < 64; zigzag += 8)
	{
		// Set the dct_values for the current interation
		dct_values = _mm256_set_ps(in_data[UV_indexes[zigzag + 7]], in_data[UV_indexes[zigzag + 6]],
				in_data[UV_indexes[zigzag + 5]], in_data[UV_indexes[zigzag + 4]],
				in_data[UV_indexes[zigzag + 3]], in_data[UV_indexes[zigzag + 2]],
				in_data[UV_indexes[zigzag + 1]], in_data[UV_indexes[zigzag]]);

		// Multiply with 0.25 to divide by 4.0
		result = _mm256_mul_ps(dct_values, factor);

		// Load quant-values and multiply with previous product
		quant_values = _mm256_load_ps(quant_tbl + zigzag);
		result = _mm256_div_ps(result, quant_values);

		// Round off values and store in out_data buffer
		result = c63_mm256_roundhalfawayfromzero_ps(result);
		_mm256_store_ps(out_data + zigzag, result);
	}
}