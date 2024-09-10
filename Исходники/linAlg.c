/* ||v||_2 */
scs_float calcNorm(const scs_float * v, scs_int len) {
	return SQRTF(calcNormSq(v, len));
}