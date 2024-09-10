BOOST_FIXTURE_TEST_CASE(test19, base_fixture_t)
{
  UnicodeString ProgramsFolder;
  ::SpecialFolderLocation(CSIDL_PROGRAM_FILES, ProgramsFolder);
  BOOST_TEST_MESSAGE("ProgramsFolder = " << W2MB(ProgramsFolder.c_str()).c_str());
  BOOST_CHECK(ProgramsFolder.Length() > 0);
}