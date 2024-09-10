TEST(IndexInfoTest, WriteIntoDir)
{
    RAMDirectory dir;

    IndexInfo infos;
    infos.addSegment(SegmentInfo(0, 42, 100, 123));
    infos.incLastSegmentId();
    infos.addSegment(SegmentInfo(1, 66, 200, 456));
    infos.incLastSegmentId();
    infos.setAttribute("foo", "bar");
    infos.save(&dir);

    ScopedPtr<InputStream> input(dir.openFile("info_0"));
    ASSERT_EQ(2, input->readVInt32());
    ASSERT_EQ(2, input->readVInt32());
    ASSERT_EQ(0, input->readVInt32());
    ASSERT_EQ(42, input->readVInt32());
    ASSERT_EQ(100, input->readVInt32());
    ASSERT_EQ(123, input->readVInt32());
    ASSERT_EQ(1, input->readVInt32());
    ASSERT_EQ(66, input->readVInt32());
    ASSERT_EQ(200, input->readVInt32());
    ASSERT_EQ(456, input->readVInt32());
    ASSERT_EQ(1, input->readVInt32());
    ASSERT_EQ("foo", input->readString());
    ASSERT_EQ("bar", input->readString());
    ASSERT_EQ(3656423981u, input->readInt32());
}