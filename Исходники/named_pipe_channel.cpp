void NamedPipeChannel::Close() {
  base::AutoLock guard(lock_);

  if (handle_ != INVALID_HANDLE_VALUE) {
    CloseHandle(handle_);
    handle_ = INVALID_HANDLE_VALUE;
    end_point_ = EndPoint::kUnknown;
  }

  if (io_ != nullptr) {
    auto local_io = io_;
    io_ = nullptr;

    {
      base::AutoUnlock unlock(lock_);
      WaitForThreadpoolIoCallbacks(local_io, FALSE);
    }

    CloseThreadpoolIo(local_io);
  }
}