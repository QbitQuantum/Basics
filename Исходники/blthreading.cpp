BLResult blThreadEventCreate(BLThreadEvent* self, bool manualReset, bool signaled) noexcept {
  HANDLE h = CreateEventW(nullptr, manualReset, signaled, nullptr);
  if (BL_UNLIKELY(!h)) {
    self->handle = -1;
    return blTraceError(blResultFromWinError(GetLastError()));
  }

  self->handle = (intptr_t)h;
  return BL_SUCCESS;
}