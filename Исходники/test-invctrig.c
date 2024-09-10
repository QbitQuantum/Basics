/* Tests along the real and imaginary axes. */
void
test_axes(void)
{
	static const long double nums[] = {
		-2, -1, -0.5, 0.5, 1, 2
	};
	long double complex z;
	int i;

	for (i = 0; i < sizeof(nums) / sizeof(nums[0]); i++) {
		/* Real axis */
		z = CMPLXL(nums[i], 0.0);
		if (fabs(nums[i]) <= 1) {
			testall_tol(cacosh, z, CMPLXL(0.0, acos(nums[i])), 1);
			testall_tol(cacos, z, CMPLXL(acosl(nums[i]), -0.0), 1);
			testall_tol(casin, z, CMPLXL(asinl(nums[i]), 0.0), 1);
			testall_tol(catanh, z, CMPLXL(atanh(nums[i]), 0.0), 1);
		} else {
			testall_tol(cacosh, z,
				    CMPLXL(acosh(fabs(nums[i])),
					   (nums[i] < 0) ? pi : 0), 1);
			testall_tol(cacos, z,
				    CMPLXL((nums[i] < 0) ? pi : 0,
					   -acosh(fabs(nums[i]))), 1);
			testall_tol(casin, z,
				    CMPLXL(copysign(pi / 2, nums[i]),
					   acosh(fabs(nums[i]))), 1);
			testall_tol(catanh, z,
				    CMPLXL(atanh(1 / nums[i]), pi / 2), 1);
		}
		testall_tol(casinh, z, CMPLXL(asinh(nums[i]), 0.0), 1);
		testall_tol(catan, z, CMPLXL(atan(nums[i]), 0), 1);

		/* TODO: Test the imaginary axis. */
	}
}