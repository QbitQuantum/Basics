static Try<HANDLE> getHandleFromFileDescriptor(
    const int fd,
    const Subprocess::IO::FDType type)
{
  Try<HANDLE> handle = getHandleFromFileDescriptor(fd);
  if (handle.isError()) {
    return Error(handle.error());
  }

  switch (type) {
    case Subprocess::IO::DUPLICATED: {
      const Try<HANDLE> duplicate = duplicateHandle(handle.get());

      if (duplicate.isError()) {
        return Error(duplicate.error());
      }

      return duplicate;
    }
    case Subprocess::IO::OWNED:
      return handle;

    // NOTE: By not setting a default we leverage the compiler
    // errors when the enumeration is augmented to find all
    // the cases we need to provide. Same for below.
  }
}