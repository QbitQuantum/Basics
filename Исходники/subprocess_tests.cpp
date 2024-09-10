TEST_F(SubprocessTest, FdInput)
{
  string in = path::join(os::getcwd(), "stdin");

  ASSERT_SOME(os::write(in, "hello\n"));

  Try<int> inFd = os::open(in, O_RDONLY | O_CLOEXEC);
  ASSERT_SOME(inFd);

  Try<Subprocess> s = subprocess(
      "read word ; echo $word",
      Subprocess::FD(inFd.get()),
      Subprocess::PIPE(),
      Subprocess::FD(STDERR_FILENO));

  ASSERT_SOME(os::close(inFd.get()));

  ASSERT_SOME(s);
  ASSERT_SOME(s.get().out());
  AWAIT_EXPECT_EQ("hello\n", io::read(s.get().out().get()));

  // Advance time until the internal reaper reaps the subprocess.
  Clock::pause();
  while (s.get().status().isPending()) {
    Clock::advance(MAX_REAP_INTERVAL());
    Clock::settle();
  }
  Clock::resume();

  AWAIT_ASSERT_READY(s.get().status());
  ASSERT_SOME(s.get().status().get());

  int status = s.get().status().get().get();
  EXPECT_TRUE(WIFEXITED(status));
  EXPECT_EQ(0, WEXITSTATUS(status));
}