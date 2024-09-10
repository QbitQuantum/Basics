void test_primates() {

	////////////////////TEST 80 BIT//////////////
	//Prepare test vectors
	YMM YMM_p1_input_80bit[5][2];

	for (int i = 0; i < 5; i++) {
		YMM_p1_input_80bit[i][0] = _mm256_setzero_si256();
		YMM_p1_input_80bit[i][1] = _mm256_setzero_si256();
	}

	//use test vectors
	p1(YMM_p1_input_80bit);
	p1_inv(YMM_p1_input_80bit);

	//test if vectors are zero again... Dont test last 192 bits of section 2, as they are not part of the state (and sub elements turn the 0s there to 1s...)
	if (_mm256_extract_epi64(YMM_p1_input_80bit[0][0], 0) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[0][0], 1) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[0][0], 2) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[0][0], 3) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[1][0], 0) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[1][0], 1) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[1][0], 2) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[1][0], 3) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[2][0], 0) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[2][0], 1) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[2][0], 2) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[2][0], 3) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[3][0], 0) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[3][0], 1) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[3][0], 2) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[3][0], 3) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[4][0], 0) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[4][0], 1) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[4][0], 2) != 0 || _mm256_extract_epi64(YMM_p1_input_80bit[4][0], 3) != 0 ||

		_mm256_extract_epi64(YMM_p1_input_80bit[0][1], 0) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[1][1], 0) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[2][1], 0) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[3][1], 0) != 0 ||
		_mm256_extract_epi64(YMM_p1_input_80bit[4][1], 0) != 0) {
		printf("P1 inv not working \n");
	}
}