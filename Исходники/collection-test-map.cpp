TIMED_TEST(MapTests, iteratorVersionTest_Map, TEST_TIMEOUT_DEFAULT) {
    Map<std::string, int> map {{"a", 10}, {"b", 20}, {"c", 30}, {"d", 40}, {"e", 50}, {"f", 60}};
    try {
        for (std::string key : map) {
            int val = map[key];
            if (val % 2 == 0) {
                map.remove(key);
            }
        }
        assertFail("should not get to end of test; should throw exception before now");
    } catch (ErrorException ex) {
        assertPass("threw exception successfully");
    }
}