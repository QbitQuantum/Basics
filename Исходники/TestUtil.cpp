void enableInvalidParameters(SavedState state) {
  _set_thread_local_invalid_parameter_handler(
      (_invalid_parameter_handler)state.previousThreadLocalHandler);
  _CrtSetReportMode(_CRT_ASSERT, state.previousCrtReportMode);
}