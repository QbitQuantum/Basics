ATF_TC_BODY(tanhf_zero_pos, tc)
{
#ifndef __vax__
	const float x = 0.0L;
	float y = tanhf(x);

	ATF_CHECK(x == y);
	ATF_CHECK(signbit(x) == 0);
	ATF_CHECK(signbit(y) == 0);
#endif
}