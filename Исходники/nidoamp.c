/** returns a kernel averaged from the two kernels between them, sse
 * version
 *
 * @param kernel the return pointer for the kernel
 * @param amp the amp which holds the kernels
 */
void average_kernels_sse(float *kernel, Amp * amp)
{
    int i;
	__m128 right;
	__m128 left;
	__m128 out;
	__m128 leftindex = {1.0f, 2.0f, 3.0f, 4.0f};
	__m128 rightindex = { FOURIER_SIZE - 1.0, FOURIER_SIZE - 2.0, FOURIER_SIZE - 3.0, FOURIER_SIZE - 4.0};
	__m128 fouriersize = _mm_set_ps1((float)FOURIER_SIZE);
	__m128 jumpsize = _mm_set_ps1(4.0f);
    for (i = 0; i < FOURIER_SIZE; i=i+4) {
		left = _mm_loadu_ps(amp->previous_buffer + i);
		right = _mm_loadu_ps(amp->fourier_buffer + i);

		out = _mm_div_ps( _mm_add_ps( _mm_mul_ps(left, leftindex), _mm_mul_ps(right, rightindex)), fouriersize);

		leftindex = _mm_add_ps(leftindex, jumpsize);
		rightindex = _mm_sub_ps(rightindex, jumpsize);

		_mm_store_ps(kernel + i, out);
	}
	for (; i < FOURIER_SIZE; i++) {
        kernel[i] =
            (amp->previous_buffer[i] * (i + 1) +
             amp->fourier_buffer[i] * (FOURIER_SIZE - i -
                                       1)) / (FOURIER_SIZE);
    }
}