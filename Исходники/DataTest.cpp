TEST_F(DataTest, testGetData) {{
	InSequence s;
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	HDDEDATA hData = (HDDEDATA)88772;
		
	EXPECT_CALL(winApi, DdeGetData(hData, _, sizeof(buffer), 5))
		.Times(1)
		.WillOnce(Invoke(this, &DataTest::DdeGetData));

	auto_drop<Data> data(new Data(&instance, &winApi, hData));

	ASSERT_EQ(8, data->getData((LPBYTE)buffer, sizeof(buffer), 5));
	ASSERT_STREQ("zulu 19", buffer);
}}