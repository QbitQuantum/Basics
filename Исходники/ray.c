/**
 * Fill in the values for a ray starting in #origin and going through #point.
 */
void ray_from_points(struct ray *r, vector_t origin, const vector_t point){
	r->origin = origin;
	r->direction = vector_normalize(vector_substract(point, origin));
#ifndef DISABLE_SSE
	r->invDirection.m = _mm_rcp_ps(r->direction.m);
#else
	for(int i = 0; i < 3; ++i){
		r->invDirection.f[i] = 1 / r->direction.f[i];
	}
#endif
}