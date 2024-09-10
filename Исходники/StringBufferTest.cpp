    //////////////////////////////////////////////////////// Test /////
    void testSprintf() {
        StringBuffer buf;

        buf.sprintf("foo %s %d", "bar", 42);
        CPPUNIT_ASSERT(buf == "foo bar 42");

        buf = doSprintf("foo %s %d", "bar", 42);
        CPPUNIT_ASSERT(buf == "foo bar 42");

        for (unsigned long size = 1; size < (1<<10); size *= 2) {
            buf.sprintf("%*s", (int)size, "");
            CPPUNIT_ASSERT_EQUAL(size, buf.length());
        }
    }