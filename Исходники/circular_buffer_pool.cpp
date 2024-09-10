std::unique_ptr<LogBuffer> CircularBufferPool::Get() {
  unsigned int current_idx = GET_BUFFER_POOL_INDEX(tail_.fetch_add(1));
  while (true) {
    if (buffers_[current_idx]) {
      break;
    } else {
      // pause for a minimum amount of time
      _mm_pause();
    }
  }
  LOG_TRACE("CircularBufferPool::Get - current_idx: %u", current_idx);
  std::unique_ptr<LogBuffer> buff = std::move(buffers_[current_idx]);
  PL_MEMSET(buffers_ + current_idx, 0, sizeof(std::unique_ptr<LogBuffer>));
  return buff;
}