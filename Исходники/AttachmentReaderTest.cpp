void AttachmentReaderTest::init(bool createReader) {
    m_sds = createSDS(TEST_SDS_BUFFER_SIZE_IN_BYTES);
    ASSERT_NE(m_sds, nullptr);
    m_writer = m_sds->createWriter(m_writerPolicy);
    ASSERT_NE(m_writer, nullptr);
    if (createReader) {
        m_reader = InProcessAttachmentReader::create(m_readerPolicy, m_sds);
        ASSERT_NE(m_reader, nullptr);
    }
    m_testPattern = createTestPattern(TEST_SDS_BUFFER_SIZE_IN_BYTES);
}