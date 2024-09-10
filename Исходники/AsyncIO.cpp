void AsyncIO::submit(Op* op) {
  CHECK_EQ(op->state(), Op::State::INITIALIZED);
  initializeContext();  // on demand

  // We can increment past capacity, but we'll clean up after ourselves.
  auto p = pending_.fetch_add(1, std::memory_order_acq_rel);
  if (p >= capacity_) {
    decrementPending();
    throw std::range_error("AsyncIO: too many pending requests");
  }
  iocb* cb = &op->iocb_;
  cb->data = nullptr;  // unused
  if (pollFd_ != -1) {
    io_set_eventfd(cb, pollFd_);
  }
  int rc = io_submit(ctx_, 1, &cb);
  if (rc < 0) {
    decrementPending();
    throwSystemErrorExplicit(-rc, "AsyncIO: io_submit failed");
  }
  submitted_++;
  DCHECK_EQ(rc, 1);
  op->start();
}