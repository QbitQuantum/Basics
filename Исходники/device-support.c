/**
 * Performs some maths operation
 */
static void performMathsOp(struct core_ctrl * core) {
	if (core->core_command-1000 == RANDOM_MATHS_OP) {
		core->data[0]=INT_TYPE;
		int r=rand();
		memcpy(&core->data[1], &r, sizeof(int));
	} else {
		float fvalue=0.0, r=0.0;
		if (core->data[0]==1) {
			fvalue=*((float*) &core->data[1]);
		} else if (core->data[0]==0) {
			fvalue=(float) *((int*) &core->data[1]);
		}
		if (core->core_command-1000 == SQRT_MATHS_OP) r=sqrtf(fvalue);
		if (core->core_command-1000 == SIN_MATHS_OP) r=sinf(fvalue);
		if (core->core_command-1000 == COS_MATHS_OP) r=cosf(fvalue);
		if (core->core_command-1000 == TAN_MATHS_OP) r=tanf(fvalue);
		if (core->core_command-1000 == ASIN_MATHS_OP) r=asinf(fvalue);
		if (core->core_command-1000 == ACOS_MATHS_OP) r=acosf(fvalue);
		if (core->core_command-1000 == ATAN_MATHS_OP) r=atanf(fvalue);
		if (core->core_command-1000 == SINH_MATHS_OP) r=sinhf(fvalue);
		if (core->core_command-1000 == COSH_MATHS_OP) r=coshf(fvalue);
		if (core->core_command-1000 == TANH_MATHS_OP) r=tanhf(fvalue);
		if (core->core_command-1000 == FLOOR_MATHS_OP) r=floorf(fvalue);
		if (core->core_command-1000 == CEIL_MATHS_OP) r=ceilf(fvalue);
		if (core->core_command-1000 == LOG_MATHS_OP) r=logf(fvalue);
		if (core->core_command-1000 == LOG10_MATHS_OP) r=log10f(fvalue);
		core->data[0]=REAL_TYPE;
		memcpy(&core->data[1], &r, sizeof(float));
	}
}