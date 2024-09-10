TEST(SegmentInfoListTest, Write)
{
	RAMDirectory dir;

	SegmentInfoList infos;
	infos.add(SegmentInfo("segment_0", 42));
	infos.incNextSegmentNum();
	infos.add(SegmentInfo("segment_1", 66));
	infos.incNextSegmentNum();
	ScopedPtr<OutputStream> output(dir.createFile("segments_0"));
	infos.write(output.get());
	output.reset();

	ScopedPtr<InputStream> input(dir.openFile("segments_0"));
	ASSERT_EQ(2, input->readVInt32());
	ASSERT_EQ(2, input->readVInt32());
	ASSERT_EQ("segment_0", input->readString());
	ASSERT_EQ(42, input->readVInt32());
	ASSERT_EQ("segment_1", input->readString());
	ASSERT_EQ(66, input->readVInt32());
}