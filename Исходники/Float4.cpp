float Float4::Dot(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2) {
	// Task 8: replace with SSE
	__m128 v1 = _mm_setr_ps(x1, y1, z1, w1);
	__m128 v2 = _mm_setr_ps(x2,y2,z2,w2);
	__m128 dpResult = _mm_dp_ps(v1, v2, 0xf1);
	return _mm_cvtss_f32(dpResult);
	//return x1*x2 + y1*y2 + z1*z2 + w1*w2;
}