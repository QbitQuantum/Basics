TEST(workload, success) {
  IOEventLoop loop;
  ASSERT_TRUE(loop.AddSignalEvent(SIGCHLD, [&]() {
    return loop.ExitLoop();
  }));
  auto workload = Workload::CreateWorkload({"sleep", "1"});
  ASSERT_TRUE(workload != nullptr);
  ASSERT_TRUE(workload->GetPid() != 0);
  ASSERT_TRUE(workload->Start());
  ASSERT_TRUE(loop.RunLoop());
}