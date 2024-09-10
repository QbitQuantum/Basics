// Wait for a subprocess and test the status code for the following
// conditions of 'expected_status':
//   1. 'None' = Anything but '0'.
//   2. 'Some' = the value of 'expected_status'.
// Returns Nothing if the resulting status code matches the
// expectation otherwise a Failure with the output of the subprocess.
// TODO(jmlvanre): Turn this into a generally useful abstraction for
// gtest where we can have a more straigtforward 'expected_status'.
Future<Nothing> await_subprocess(
    const Subprocess& subprocess,
    const Option<int>& expected_status = None())
{
  // Dup the pipe fd of the subprocess so we can read the output if
  // needed.
  Try<int_fd> dup = os::dup(subprocess.out().get());
  if (dup.isError()) {
    return Failure(dup.error());
  }

  int_fd out = dup.get();

  // Once we get the status of the process.
  return subprocess.status()
    .then([=](const Option<int>& status) -> Future<Nothing> {
      // If the status is not set, fail out.
      if (status.isNone()) {
        return Failure("Subprocess status is none");
      }

      // If the status is not what we expect then fail out with the
      // output of the subprocess. The failure message will include
      // the assertion failures of the subprocess.
      if ((expected_status.isSome() && status.get() != expected_status.get()) ||
          (expected_status.isNone() && status.get() == 0)) {
        return io::read(out)
          .then([](const string& output) -> Future<Nothing> {
            return Failure("\n[++++++++++] Subprocess output.\n" + output +
                           "[++++++++++]\n");
          });
      }

      // If the subprocess ran successfully then return nothing.
      return Nothing();
    }).onAny([=]() {
      os::close(out);
    });
}