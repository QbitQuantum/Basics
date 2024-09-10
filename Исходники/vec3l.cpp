vec3l& vec3l::Sub(const vec3l& v) {
	__m256i vxmm = _mm256_set_epi64x(0, v.z, v.y, v.x);
	__m256i xmm = _mm256_set_epi64x(0, z, y, x);
	xmm = _mm256_sub_epi64(xmm, vxmm);

	x = M256L(xmm, 0);
	y = M256L(xmm, 1);
	z = M256L(xmm, 2);

	return *this;
}