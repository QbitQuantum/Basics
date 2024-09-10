/**
* test the stream utility, read bytes
*/
VOID TEST(KernelStreamTest, StreamReadBytes)
{
    SrsStream s;
    char data[] = "Hello, world!";
    
    EXPECT_TRUE(ERROR_SUCCESS == s.initialize(data, sizeof(data) - 1));
    
    char bytes[64];
    s.read_bytes(bytes, 2);
    bytes[2] = 0;
    EXPECT_STREQ("He", bytes);
    
    s.read_bytes(bytes, 2);
    bytes[2] = 0;
    EXPECT_STREQ("ll", bytes);
    
    s.skip(3);
    s.read_bytes(bytes, 6);
    bytes[6] = 0;
    EXPECT_STREQ("world!", bytes);
    
    EXPECT_TRUE(s.empty());
}