void quick_exit(int exit_code) {
  std::lock_guard<std::mutex> lock(quick_exit_mutex);
  for (auto it = quick_exit_handlers.rbegin(); it != quick_exit_handlers.rend(); ++it) {
    (*it)();
  }
  _Exit(exit_code);
}