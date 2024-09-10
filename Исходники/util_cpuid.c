/*
 * check_cpu_features -- validates CPU features detection
 */
static void
check_cpu_features(void)
{
	if (is_cpu_clflush_present()) {
		UT_OUT("CLFLUSH supported");
		_mm_clflush(Buf);
	} else {
		UT_OUT("CLFLUSH not supported");
	}

	if (is_cpu_clflushopt_present()) {
		UT_OUT("CLFLUSHOPT supported");
		_mm_clflushopt(Buf);
	} else {
		UT_OUT("CLFLUSHOPT not supported");
	}

	if (is_cpu_clwb_present()) {
		UT_OUT("CLWB supported");
		_mm_clwb(Buf);
	} else {
		UT_OUT("CLWB not supported");
	}
}