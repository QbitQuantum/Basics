TEST(spawn, posix_spawn_environment) {
  ExecTestHelper eth;
  eth.SetArgs({"sh", "-c", "exit $posix_spawn_environment_test", nullptr});
  eth.SetEnv({"posix_spawn_environment_test=66", nullptr});
  pid_t pid;
  ASSERT_EQ(0, posix_spawnp(&pid, eth.GetArg0(), nullptr, nullptr, eth.GetArgs(), eth.GetEnv()));
  AssertChildExited(pid, 66);
}