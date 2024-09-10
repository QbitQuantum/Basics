TEST(FunctionScheduler, StartThrows) {
  FunctionScheduler fs;
  PThreadCreateFailure fail;
  EXPECT_ANY_THROW(fs.start());
  EXPECT_NO_THROW(fs.shutdown());
}