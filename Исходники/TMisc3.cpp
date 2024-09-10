static void TestMath()
	{
	double eps = 0.000001;

	double res = fabs(21.091);
	TEST((21.091 - res) < eps);
	res = fabs(-1.91);
	TEST((res - 1.91) < eps);

	res = atan(0.0);
	TEST(fabs(res) < eps);
	// 90 degrees
	res = tan(KPi/2);
	TEST(res > 1000000000.0);
	res = atan(res);
	TEST(fabs(res - KPi/2) < eps);
	// 45 degrees
	res = tan(KPi/4);
	TEST(fabs(res - 1.0) < eps);
	res = atan(res);
	TEST(fabs(res - KPi/4) < eps);
	// 135 degrees
	res = tan((3 * KPi) / 4);
	TEST(fabs(res + 1.0) < eps);
	res = atan(res);
	TEST(fabs((KPi + res) - (3 * KPi) / 4) < eps);

	// 0 degrees
	res = cos(0.0);
	TEST(fabs(res - 1) < eps);
	// 90 degrees
	res = cos(KPi/2);
	TEST(res < eps);
	// 180 degrees
	res = cos(KPi);
	TEST(fabs(res + 1.0) < eps);

	// 0 degrees
	res = sin(0.0);
	TEST(res < eps);
	// 90 degrees
	res = sin(KPi/2);
	TEST(fabs(res - 1) < eps);
	// 180 degrees
	res = sin(KPi);
	TEST(res < eps);

	res = tanh(1.0);
	TEST(fabs(res - 0.761594) < eps);

	int exponent;
	res = frexp(0.51E+2, &exponent);
	TEST((0.51E+2 - res * pow(2.0, exponent)) < eps);

	double integer;
	res = modf(34.567, &integer);
	TEST(fabs(res - 0.567) < eps);
	TEST(fabs(integer - 34.0) < eps);
	res = modf(-35.567, &integer);
	TEST(fabs(res + 0.567) < eps);
	TEST(fabs(integer + 35.0) < eps);

	res = ceil(245.8903);
	TEST(fabs(res - 246.0) < eps);
	res = ceil(-11.91);
	TEST(fabs(res + 11.0) < eps);

	res = floor(245.8903);
	TEST(fabs(res - 245.0) < eps);
	res = floor(-11.91);
	TEST(fabs(res + 12.0) < eps);

	res = copysign(4.789, -9.001);
	TEST((res + 4.789) < eps);
	res = copysign(-4.789, 9.001);
	TEST((res - 4.789) < eps);

	}