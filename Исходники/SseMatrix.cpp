// ~~~~~~~~~~~~~~~ Task3
void mulMatrix_IJKAlgSse(MATRIX_TYPE** first, MATRIX_TYPE** second, MATRIX_TYPE** result, size_t size) {
	transpose(second, size);

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			__m128 temp = _mm_setzero_ps();

			for (size_t k = 0; k < size; k += 4) {
				__m128 tempFirst = _mm_load_ps(&first[i][k]);
				__m128 tempSecond = _mm_load_ps(&second[j][k]);
				temp = _mm_add_ps(temp, _mm_mul_ps(tempFirst, tempSecond));
			}

			temp = _mm_hadd_ps(temp, temp);
			temp = _mm_hadd_ps(temp, temp);
			_mm_store_ss(&result[i][j], temp);
		}
	}

	transpose(second, size);
}