void service_pcnfs(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port) {
  int run = 1, next_run = 1, sock = -1;

  hydra_register_socket(sp);
  if (port == 0) {
    fprintf(stderr, "Error: pcnfs module called without -s port!\n");
    hydra_child_exit(0);
  }
  if ((options & OPTION_SSL) != 0) {
    fprintf(stderr, "Error: pcnfs module can not be used with SSL!\n");
    hydra_child_exit(0);
  }

  if (memcmp(hydra_get_next_pair(), &HYDRA_EXIT, sizeof(HYDRA_EXIT)) == 0)
    return;

  while (1) {
    next_run = 0;
    switch (run) {
    case 1:                    /* connect and service init function */
      {
        if (sock >= 0)
          sock = hydra_disconnect(sock);
//        usleep(275000);
        if ((sock = hydra_connect_udp(ip, port)) < 0) {
          fprintf(stderr, "Error: Child with pid %d terminating, can not connect\n", (int) getpid());
          hydra_child_exit(1);
        }
        next_run = 2;
        break;
      }
    case 2:                    /* run the cracking function */
      next_run = start_pcnfs(sock, ip, port, options, miscptr, fp);
      break;
    case 3:                    /* clean exit */
      if (sock >= 0)
        sock = hydra_disconnect(sock);
      hydra_child_exit(0);
      return;
    default:
      fprintf(stderr, "Caught unknown return code, exiting!\n");
      hydra_child_exit(0);
    }
    run = next_run;
  }
}