int main(void) {
  int ret;
  // register Ctrl-C handler
  std::signal(SIGINT, exitGraceful);

  if (0 != initialize_enclave(&eid)) {
    cerr << "failed to init enclave" << endl;
    exit(-1);
  }

  mbedtls_net_context listen_fd, client_fd;
  // initialize the object
  ssl_conn_init(eid);
  // initialize threads
  memset(threads, 0, sizeof(threads));

  mbedtls_printf("  . Bind on https://localhost:4433/ ...");
  fflush(stdout);

  if ((ret = mbedtls_net_bind(&listen_fd, NULL, "4433", MBEDTLS_NET_PROTO_TCP)) != 0) {
    mbedtls_printf(" failed\n  ! mbedtls_net_bind returned %d\n\n", ret);
    std::exit(-1);
  }

  mbedtls_printf(" ok\n");

  mbedtls_printf("  [ main ]  Waiting for a remote connection\n");

  // non-block accept
  while (true) {
    // check for Ctrl-C flag
    std::this_thread::sleep_for (std::chrono::seconds(1));
    if (quit.load()) {
      cerr << "Ctrl-C pressed. Quiting..." << endl;
      break;
    }

#ifdef MBEDTLS_ERROR_C
    if (ret != 0) {
      char error_buf[100];
      mbedtls_strerror(ret, error_buf, 100);
      mbedtls_printf("  [ main ]  Last error was: -0x%04x - %s\n", -ret, error_buf);
    }
#endif

    /*
     * 3. Wait until a client connects
     */

    if (0 != mbedtls_net_set_nonblock(&listen_fd)) {
      cerr << "can't set nonblock for the listen socket" << endl;
    }
    ret = mbedtls_net_accept(&listen_fd, &client_fd, NULL, 0, NULL);
    if (ret == MBEDTLS_ERR_SSL_WANT_READ) {
      ret = 0;
      continue;
    } else if (ret != 0) {
      mbedtls_printf("  [ main ] failed: mbedtls_net_accept returned -0x%04x\n", ret);
      break;
    }

    mbedtls_printf("  [ main ]  ok\n");
    mbedtls_printf("  [ main ]  Creating a new thread for client %d\n", client_fd.fd);

    if ((ret = thread_create(&client_fd)) != 0) {
      mbedtls_printf("  [ main ]  failed: thread_create returned %d\n", ret);
      mbedtls_net_free(&client_fd);
      continue;
    }
    ret = 0;
  } // while (true)

  sgx_destroy_enclave(eid);
  return (ret);
}