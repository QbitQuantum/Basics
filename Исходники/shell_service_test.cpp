// Tests a PTY subprocess with no protocol.
TEST_F(ShellServiceTest, PtyNoProtocolSubprocess) {
    // [ -t 0 ] checks if stdin is connected to a terminal.
    ASSERT_NO_FATAL_FAILURE(StartTestSubprocess(
                                "echo foo; echo bar >&2; [ -t 0 ]; echo $?",
                                SubprocessType::kPty, SubprocessProtocol::kNone));

    // [ -t 0 ] == 0 means we have a terminal (PTY).
    ExpectLinesEqual(ReadRaw(subprocess_fd_), {"foo", "bar", "0"});
}