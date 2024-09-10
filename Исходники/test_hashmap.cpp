  void testRemove ()
  {
    map->put ((char*)"one", 1);
    map->remove ((char*)"one");

    CPPUNIT_ASSERT_EQUAL (map->get ((char*)"one"), 0);
  }