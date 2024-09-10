/*---------------------------------------------------------------------------*/
void
slip_init(void)
{
  setvbuf(stdout, NULL, _IOLBF, 0);     /* Line buffered output. */

  if(slip_config_host != NULL) {
    if(slip_config_port == NULL) {
      slip_config_port = "60001";
    }
    slipfd = connect_to_server(slip_config_host, slip_config_port);
    if(slipfd == -1) {
      LOG6LBR_FATAL("can't connect to %s:%s\n", slip_config_host,
          slip_config_port);
      exit(1);
    }

  } else if(slip_config_siodev != NULL) {
    if(strcmp(slip_config_siodev, "null") == 0) {
      /* Disable slip */
      return;
    }
    slipfd = devopen(slip_config_siodev, O_RDWR | O_NONBLOCK);
    if(slipfd == -1) {
      LOG6LBR_FATAL( "can't open siodev /dev/%s : %s\n", slip_config_siodev, strerror(errno));
      exit(1);
    }

  } else {
    static const char *siodevs[] = {
      "ttyUSB0", "cuaU0", "ucom0"       /* linux, fbsd6, fbsd5 */
    };
    int i;

    for(i = 0; i < 3; i++) {
      slip_config_siodev = siodevs[i];
      slipfd = devopen(slip_config_siodev, O_RDWR | O_NONBLOCK);
      if(slipfd != -1) {
        break;
      }
    }
    if(slipfd == -1) {
      LOG6LBR_FATAL("can't open siodev : %s\n", strerror(errno));
      exit(1);
    }
  }

  select_set_callback(slipfd, &slip_callback);

  if(slip_config_host != NULL) {
    LOG6LBR_INFO("SLIP opened to %s:%s\n", slip_config_host,
           slip_config_port);
  } else {
    LOG6LBR_INFO("SLIP started on /dev/%s\n", slip_config_siodev);
    stty_telos(slipfd);
  }

  timer_set(&send_delay_timer, 0);
  slip_send(slipfd, SLIP_END);
  inslip = fdopen(slipfd, "r");
  if(inslip == NULL) {
    LOG6LBR_FATAL("main: fdopen: %s\n", strerror(errno));
    exit(1);
  }
}