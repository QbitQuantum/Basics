TEST(WebURLRequestTest, ExtraData)
{
    bool alive = false;
    {
        WebURLRequest urlRequest;
        TestExtraData* extraData = new TestExtraData(&alive);
        EXPECT_TRUE(alive);

        urlRequest.initialize();
        urlRequest.setExtraData(extraData);
        EXPECT_EQ(extraData, urlRequest.extraData());
        {
            WebURLRequest otherUrlRequest = urlRequest;
            EXPECT_TRUE(alive);
            EXPECT_EQ(extraData, otherUrlRequest.extraData());
            EXPECT_EQ(extraData, urlRequest.extraData());
        }
        EXPECT_TRUE(alive);
        EXPECT_EQ(extraData, urlRequest.extraData());
    }
    EXPECT_FALSE(alive);
}