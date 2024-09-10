ATF_TC_BODY(good_big5_getwc, tc)
{
	const char buf[] = { 0xcf, 0x40 };
	struct ibuf ib = {
		.buf = buf,
		.buflen = sizeof(buf),
	};
	FILE *fp = funopen(&ib, readfn, NULL, NULL, NULL);

	ATF_REQUIRE(fp != NULL);
	setlocale(LC_CTYPE, "zh_TW.Big5");
	/* XXX implementation detail knowledge (wchar_t encoding) */
	ATF_REQUIRE_EQ(getwc(fp), 0xcf40);
	fclose(fp);
}

ATF_TC(bad_big5_getwc);
ATF_TC_HEAD(bad_big5_getwc, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test bad big5 wchar getwc");
}