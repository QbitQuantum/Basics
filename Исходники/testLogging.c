TEST(Logging, Logging__LogF_NULL_Module_MSG)
{
  Logf(NULL, "Msg");
	TEST_ASSERT_NOT_EQUAL(0, strlen(LogBuffer));
}