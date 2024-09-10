_inline float process_folded_fir_sse2(const float *fir_kernel, const float *queue_head, const float *queue_tail, int len)
{
	__m128 acc = _mm_set_ps(0, 0, 0, 0);

	queue_tail -= 3;

	len >>= 2;
	while (len > 0)
	{
		__m128 head = _mm_loadu_ps(queue_head);
		__m128 tail = _mm_loadu_ps(queue_tail);
		__m128 kern = _mm_load_ps(fir_kernel);

		tail = _mm_shuffle_ps(tail, tail, 0x1b);  // swap the order
		__m128 t1 = _mm_add_ps(tail, head);       // add the head
		t1 = _mm_mul_ps(t1, kern);                // mul
		acc = _mm_add_ps(acc, t1);                // add

		queue_head += 4;
		queue_tail -= 4;
		fir_kernel += 4;
		len--;
	}

	// horizontal sum
	const __m128 t = _mm_add_ps(acc, _mm_movehl_ps(acc, acc));
	const __m128 sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));

	return sum.m128_f32[0];
}