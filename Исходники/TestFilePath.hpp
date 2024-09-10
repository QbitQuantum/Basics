 void testGetPath()
 {
     std::string c0("test/");
     std::string c1("/dir/test2/");
     std::string result = m_path.getPath(c1,c0);
     TS_ASSERT_EQUALS(result, "/dir/test2/test/");
     result = m_path.getPath(c1,c1);
     TS_ASSERT_EQUALS(result, "/dir/test2/");
 }