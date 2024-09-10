END_TEST

START_TEST(getversion_returns_a_version)
{
	ck_assert_int_gt((int)strlen(getversion()), 1);
	ck_assert(strchr(getversion(), '_') == NULL);
	ck_assert(strchr(getversion(), '.') != NULL);
}