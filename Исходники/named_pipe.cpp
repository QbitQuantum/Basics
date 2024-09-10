void NamedPipe::Close() {
  base::AutoLock guard(lock_);

  CloseHandle(pipe_);
  pipe_ = INVALID_HANDLE_VALUE;

  if (io_ != nullptr) {
    auto local_io = io_;
    io_ = nullptr;

    base::AutoUnlock unlock(lock_);

    WaitForThreadpoolIoCallbacks(local_io, FALSE);
    CloseThreadpoolIo(local_io);
  }
}