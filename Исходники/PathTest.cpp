TEST(CPath, DefaultConstructor)
{
	CPath tmp;

	ASSERT_FALSE(tmp.IsOk());
	ASSERT_EQUALS(tmp, CPath());

	ASSERT_FALSE(tmp.FileExists());
	ASSERT_FALSE(tmp.DirExists());

	ASSERT_EQUALS(wxEmptyString, tmp.GetRaw());
	ASSERT_EQUALS(wxEmptyString, tmp.GetPrintable());
	ASSERT_EQUALS(CPath(), tmp.GetPath());
	ASSERT_EQUALS(CPath(), tmp.GetFullName());
}