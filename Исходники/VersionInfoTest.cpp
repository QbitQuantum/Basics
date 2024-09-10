TEST(VersionInfo, getVersion) {
  VersionInfo version;
  jsonxx::Object versionJson = version.getVersion();
  
  ASSERT_EQ(1, versionJson.size());
  ASSERT_EQ(VERSION, versionJson.get<string>("version"));
}