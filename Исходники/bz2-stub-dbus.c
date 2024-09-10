/* Before main(), get an FD for the driver program, so that it is still
   accessible even if the application enters a sandbox. */
void __attribute__((constructor)) _stub_construct(void) {
  g_exe_fd = OpenDriver(g_exe_file);
}