void AlphabeticIndexTest::TestChineseZhuyin() {
    UErrorCode status = U_ZERO_ERROR;
    char loc[100];
    uloc_forLanguageTag("zh-u-co-zhuyin", loc, LENGTHOF(loc), NULL, &status);
    AlphabeticIndex index(loc, status);
    LocalPointer<AlphabeticIndex::ImmutableIndex> immIndex(index.buildImmutableIndex(status));
    TEST_CHECK_STATUS; 
    assertEquals("getBucketCount()", 38, immIndex->getBucketCount());
    assertEquals("label 1", UnicodeString((UChar)0x3105), immIndex->getBucket(1)->getLabel());
    assertEquals("label 2", UnicodeString((UChar)0x3106), immIndex->getBucket(2)->getLabel());
    assertEquals("label 3", UnicodeString((UChar)0x3107), immIndex->getBucket(3)->getLabel());
    assertEquals("label 4", UnicodeString((UChar)0x3108), immIndex->getBucket(4)->getLabel());
    assertEquals("label 5", UnicodeString((UChar)0x3109), immIndex->getBucket(5)->getLabel());
}