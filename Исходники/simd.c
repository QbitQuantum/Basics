PHP_METHOD(Float32x4, __construct) {
	double lanes[4] = php_float32x4_empty;
	float  flanes[4] = php_float32x4_empty;
	php_float32x4_t *p = php_float32x4_fetch();
	
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "dddd", &lanes[0], &lanes[1], &lanes[2], &lanes[3]) != SUCCESS) {
		return;
	}
	
	flanes[0] = (float) lanes[0];
	flanes[1] = (float) lanes[1];
	flanes[2] = (float) lanes[2];
	flanes[3] = (float) lanes[3];
	
	if (posix_memalign(
		(void**) &p->v, 16, sizeof(__m128)) != SUCCESS) {
		zend_throw_exception_ex(php_float32x4_exception_ce, 0, "memory alignment error");
	}
	
	*p->v = _mm_load_ps (flanes);
}