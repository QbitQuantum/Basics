TEST(DefaultFileSystemTest, WriteMoveStatRemove)
{
  AdblockPlus::DefaultFileSystem fileSystem;
  WriteString(fileSystem, "foo");
  AdblockPlus::FileSystem::StatResult result = fileSystem.Stat(testPath);
  ASSERT_TRUE(result.exists);
  ASSERT_TRUE(result.isFile);
  ASSERT_FALSE(result.isDirectory);
  ASSERT_NE(0, result.lastModified);
  const std::string newTestPath = testPath + "-new";
  fileSystem.Move(testPath, newTestPath);
  result = fileSystem.Stat(testPath);
  ASSERT_FALSE(result.exists);
  result = fileSystem.Stat(newTestPath);
  ASSERT_TRUE(result.exists);
  fileSystem.Remove(newTestPath);
  result = fileSystem.Stat(newTestPath);
  ASSERT_FALSE(result.exists);
}