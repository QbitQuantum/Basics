int test_float(int argc, char *argv[])
{
	int ret = 0;

	printf("\n--- SINGLE PRECISION TESTS ---\n");
	printf("The single precision test involves calls to fabsf(),\nif test fails check this function as well.\n\n");

	float f1 = 1.55f;

	float sinf_zero = sinf(0.0f);
	float sinf_one = sinf(1.0f);
	float sqrt_two = sqrt(2.0f);

	if (sinf_zero == 0.0f) {
		printf("\t success: sinf(0.0f) == 0.0f\n");

	} else {
		printf("\t FAIL: sinf(0.0f) != 0.0f, result: %8.4f\n", (double)sinf_zero);
		ret = -4;
	}

	fflush(stdout);

	if (fabsf((sinf_one - 0.841470956802368164062500000000f)) < FLT_EPSILON) {
		printf("\t success: sinf(1.0f) == 0.84147f\n");

	} else {
		printf("\t FAIL: sinf(1.0f) != 0.84147f, result: %8.4f\n", (double)sinf_one);
		ret = -1;
	}

	fflush(stdout);

	float asinf_one = asinf(1.0f);

	if (fabsf((asinf_one - 1.570796251296997070312500000000f)) < FLT_EPSILON * 1.5f) {
		printf("\t success: asinf(1.0f) == 1.57079f\n");

	} else {
		printf("\t FAIL: asinf(1.0f) != 1.57079f, result: %f\n", asinf_one);
		ret = -1;
	}

	fflush(stdout);

	float cosf_one = cosf(1.0f);

	if (fabsf((cosf_one - 0.540302336215972900390625000000f)) < FLT_EPSILON) {
		printf("\t success: cosf(1.0f) == 0.54030f\n");

	} else {
		printf("\t FAIL: cosf(1.0f) != 0.54030f, result: %8.4f\n", (double)cosf_one);
		ret = -1;
	}

	fflush(stdout);


	float acosf_one = acosf(1.0f);

	if (fabsf((acosf_one - 0.000000000000000000000000000000f)) < FLT_EPSILON) {
		printf("\t success: acosf(1.0f) == 0.0f\n");

	} else {
		printf("\t FAIL: acosf(1.0f) != 0.0f, result: %8.4f\n", (double)acosf_one);
		ret = -1;
	}

	fflush(stdout);


	float sinf_zero_one = sinf(0.1f);

	if (fabs(sinf_zero_one - 0.0998334166f) < FLT_EPSILON) {
		printf("\t success: sinf(0.1f) == 0.09983f\n");

	} else {
		printf("\t FAIL: sinf(0.1f) != 0.09983f, result: %8.4f\n", (double)sinf_zero_one);
		ret = -2;
	}

	if (sqrt_two == 1.41421356f) {
		printf("\t success: sqrt(2.0f) == 1.41421f\n");

	} else {
		printf("\t FAIL: sqrt(2.0f) != 1.41421f, result: %8.4f\n", (double)sinf_zero_one);
		ret = -3;
	}

	float atan2f_ones = atan2(1.0f, 1.0f);

	if (fabsf(atan2f_ones - 0.785398163397448278999490867136f) < FLT_EPSILON) {
		printf("\t success: atan2f(1.0f, 1.0f) == 0.78539f\n");

	} else {
		printf("\t FAIL: atan2f(1.0f, 1.0f) != 0.78539f, result: %8.4f\n", (double)atan2f_ones);
		ret = -4;
	}

	char sbuf[30];
	sprintf(sbuf, "%8.4f", 0.553415f);

	if (sbuf[0] == ' ' && sbuf[1] == ' ' && sbuf[2] == '0' &&
		sbuf[3] == '.' && sbuf[4] == '5' && sbuf[5] == '5'
		&& sbuf[6] == '3' && sbuf[7] == '4' && sbuf[8] == '\0') {
		printf("\t success: printf(\"%%8.4f\", 0.553415f) == %8.4f\n", (double)0.553415f);
	} else {
		printf("\t FAIL: printf(\"%%8.4f\", 0.553415f) != \"  0.5534\", result: %s\n", sbuf);
		ret = -5;
	}

	sprintf(sbuf, "%8.4f", -0.553415f);

	if (sbuf[0] == ' ' && sbuf[1] == '-' && sbuf[2] == '0' &&
		sbuf[3] == '.' && sbuf[4] == '5' && sbuf[5] == '5'
		&& sbuf[6] == '3' && sbuf[7] == '4' && sbuf[8] == '\0') {
		printf("\t success: printf(\"%%8.4f\", -0.553415f) == %8.4f\n", (double)-0.553415f);
	} else {
		printf("\t FAIL: printf(\"%%8.4f\", -0.553415f) != \" -0.5534\", result: %s\n", sbuf);
		ret = -6;
	}





	printf("\n--- DOUBLE PRECISION TESTS ---\n");

	double d1 = 1.0111;
	double d2 = 2.0;

	double d1d2 = d1 * d2;

	if (d1d2 == 2.022200000000000219557705349871) {
		printf("\t success: 1.0111 * 2.0 == 2.0222\n");

	} else {
		printf("\t FAIL: 1.0111 * 2.0 != 2.0222, result: %8.4f\n", d1d2);
		ret = -7;
	}

	fflush(stdout);

	// Assign value of f1 to d1
	d1 = f1;

	if (f1 == (float)d1) {
		printf("\t success: (float) 1.55f == 1.55 (double)\n");

	} else {
		printf("\t FAIL: (float) 1.55f != 1.55 (double), result: %8.4f\n", f1);
		ret = -8;
	}

	fflush(stdout);


	double sin_zero = sin(0.0);
	double sin_one = sin(1.0);
	double atan2_ones = atan2(1.0, 1.0);

	if (sin_zero == 0.0) {
		printf("\t success: sin(0.0) == 0.0\n");

	} else {
		printf("\t FAIL: sin(0.0) != 0.0, result: %8.4f\n", sin_zero);
		ret = -9;
	}

	if (sin_one == 0.841470984807896504875657228695) {
		printf("\t success: sin(1.0) == 0.84147098480\n");

	} else {
		printf("\t FAIL: sin(1.0) != 1.0, result: %8.4f\n", sin_one);
		ret = -10;
	}

	if (atan2_ones != 0.785398) {
		printf("\t success: atan2(1.0, 1.0) == 0.785398\n");

	} else {
		printf("\t FAIL: atan2(1.0, 1.0) != 0.785398, result: %8.4f\n", atan2_ones);
		ret = -11;
	}

	printf("\t testing pow() with magic value\n");
	printf("\t   (44330.0 * (1.0 - pow((96286LL / 101325.0), 0.190295)));\n");
	fflush(stdout);
	usleep(20000);
	double powres = (44330.0 * (1.0 - pow((96286LL / 101325.0), 0.190295)));
	printf("\t success: result: %8.4f\n", (double)powres);

	sprintf(sbuf, "%8.4f", 0.553415);

	if (sbuf[0] == ' ' && sbuf[1] == ' ' && sbuf[2] == '0' &&
		sbuf[3] == '.' && sbuf[4] == '5' && sbuf[5] == '5'
		&& sbuf[6] == '3' && sbuf[7] == '4' && sbuf[8] == '\0') {
		printf("\t success: printf(\"%%8.4f\", 0.553415) == %8.4f\n", 0.553415);
	} else {
		printf("\t FAIL: printf(\"%%8.4f\", 0.553415) != \"  0.5534\", result: %s\n", sbuf);
		ret = -12;
	}

	sprintf(sbuf, "%8.4f", -0.553415);

	if (sbuf[0] == ' ' && sbuf[1] == '-' && sbuf[2] == '0' &&
		sbuf[3] == '.' && sbuf[4] == '5' && sbuf[5] == '5'
		&& sbuf[6] == '3' && sbuf[7] == '4' && sbuf[8] == '\0') {
		printf("\t success: printf(\"%%8.4f\", -0.553415) == %8.4f\n", -0.553415);
	} else {
		printf("\t FAIL: printf(\"%%8.4f\", -0.553415) != \" -0.5534\", result: %s\n", sbuf);
		ret = -13;
	}


	if (ret == 0) {
		printf("\n SUCCESS: All float and double tests passed.\n");

	} else {
		printf("\n FAIL: One or more tests failed.\n");
	}

	printf("\n");

	return ret;
}