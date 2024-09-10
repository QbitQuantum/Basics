TEST(TestFile, Stat)
{
  XFILE::CFile *file;
  struct __stat64 buffer;

  ASSERT_TRUE((file = XBMC_CREATETEMPFILE("")) != NULL);
  EXPECT_EQ(0, file->Stat(&buffer));
  file->Close();
  EXPECT_TRUE(buffer.st_mode | _S_IFREG);
  EXPECT_EQ(-1, XFILE::CFile::Stat("", &buffer));
  EXPECT_EQ(ENOENT, errno);
  EXPECT_TRUE(XBMC_DELETETEMPFILE(file));
}