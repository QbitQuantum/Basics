static int core_netio_shutdown_cb(pr_netio_stream_t *nstrm, int how) {
  return shutdown(nstrm->strm_fd, how);
}