bool wait_on_child_and_print_progress (process &child_proc) {
  const size_t BUF_SIZE = 4096;
  char buf[BUF_SIZE];
  ssize_t bytes_read;
  bool success = true;
  while( (bytes_read = child_proc.read_from_child(buf, BUF_SIZE)) > 0 ) {
    logprogress_stream << std::string(buf, buf + bytes_read);
    if (cppipc::must_cancel()) {
      logprogress_stream << "Cancel by user" << std::endl;
      child_proc.kill(false);
      success = false;
      break;
    }
  }
  logprogress_stream << std::endl;

  return success;
}