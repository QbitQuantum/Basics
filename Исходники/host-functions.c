/**
 * Called when running on the host, this performs some maths operation
 */
struct value_defn performMathsOp(unsigned short operation, struct value_defn value) {
	struct value_defn result;
	result.dtype=SCALAR;
	if (operation== RANDOM_MATHS_OP) {
		result.type=INT_TYPE;
		int r=rand();
		cpy(result.data, &r, sizeof(int));
	} else {
		float fvalue, r;
		if (value.type==REAL_TYPE) {
			fvalue=*((float*) value.data);
		} else if (value.type==INT_TYPE) {
			fvalue=(float) *((int*) value.data);
		}
		result.type=REAL_TYPE;
		if (operation==SQRT_MATHS_OP) r=sqrtf(fvalue);
		if (operation==SIN_MATHS_OP) r=sinf(fvalue);
		if (operation==COS_MATHS_OP) r=cosf(fvalue);
		if (operation==TAN_MATHS_OP) r=tanf(fvalue);
		if (operation==ASIN_MATHS_OP) r=asinf(fvalue);
		if (operation==ACOS_MATHS_OP) r=acosf(fvalue);
		if (operation==ATAN_MATHS_OP) r=atanf(fvalue);
		if (operation==SINH_MATHS_OP) r=sinhf(fvalue);
		if (operation==COSH_MATHS_OP) r=coshf(fvalue);
		if (operation==TANH_MATHS_OP) r=tanhf(fvalue);
		if (operation==FLOOR_MATHS_OP) r=floorf(fvalue);
		if (operation==CEIL_MATHS_OP) r=ceilf(fvalue);
		if (operation==LOG_MATHS_OP) r=logf(fvalue);
		if (operation==LOG10_MATHS_OP) r=log10f(fvalue);
		cpy(result.data, &r, sizeof(float));
	}
	return result;
}