ATF_TC_BODY(erfcf_nan, tc)
{
	const float x = 0.0L / 0.0L;

	ATF_CHECK(isnan(erfcf(x)) != 0);
}