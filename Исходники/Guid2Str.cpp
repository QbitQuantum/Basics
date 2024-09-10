TEST(Guid2StrTest, RandomGUID) {
	GUID guid = { 0 };
	UuidCreate(&guid);
	Guid2Str *o = new Guid2Str(guid);
	EXPECT_TRUE(o->Str() != NULL);
	delete o;
}