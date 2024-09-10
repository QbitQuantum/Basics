TEST(ReaderTest, TestRemainigSizeAtTheEnd)
{
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

    reader.Initialize(array);
    reader.ReadByte();
    reader.ReadWordLE();
    reader.ReadDoubleWordLE();
    reader.ReadArray(3);
    reader.ReadByte();
    reader.ReadWordBE();
    ASSERT_THAT(reader.RemainingSize(), Eq(0));
}