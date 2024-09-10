// Update location by velocity, one time-step
void update_coords(uint32_t i, float* x, float* y, float* z, float* vx, float* vy, float* vz) {
	__m128 vec, flo, out;


	vec = _mm_set_ss(vx[i]);
	flo = _mm_set_ss(x[i]);
	out = _mm_add_ss(vec, flo);
	_mm_store_ss(&x[i], out);

	vec = _mm_set_ss(vy[i]);
	flo = _mm_set_ss(y[i]);
	out = _mm_add_ss(vec, flo);
	_mm_store_ss(&y[i], out);

	vec = _mm_set_ss(vz[i]);
	flo = _mm_set_ss(z[i]);
	out = _mm_add_ss(vec, flo);
	_mm_store_ss(&z[i], out);

}