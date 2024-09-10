Error Assembler::embed(const void* data, uint32_t size) {
  if (getRemainingSpace() < size) {
    Error error = _grow(size);
    if (error != kErrorOk)
      return setError(error);
  }

  uint8_t* cursor = getCursor();
  ::memcpy(cursor, data, size);
  setCursor(cursor + size);

#if !defined(ASMJIT_DISABLE_LOGGER)
  if (_logger)
    _logger->logBinary(kLoggerStyleData, data, size);
#endif // !ASMJIT_DISABLE_LOGGER

  return kErrorOk;
}