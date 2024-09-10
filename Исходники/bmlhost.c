int
main (int argc, char **argv)
{
  char *socket_file = NULL;
  const char *debug_log_flag_str = getenv ("BML_DEBUG");
  const int debug_log_flags =
      debug_log_flag_str ? atoi (debug_log_flag_str) : 0;
  BMLDebugLogger logger;
  int server_socket, client_socket;
  socklen_t addrlen;
  ssize_t size;
  struct sockaddr_un address = { 0, };
  int running = TRUE;
  BmlIpcBuf bo = IPC_BUF_INIT, bi = IPC_BUF_INIT;
  BmAPI id;

  logger = TRACE_INIT (debug_log_flags);
  TRACE ("beg\n");

  if (argc > 1) {
    socket_file = argv[1];
  } else {
    fprintf (stderr, "Usage: bmlhost <socket file>\n");
    return EXIT_FAILURE;
  }
  TRACE ("socket file: '%s'\n", socket_file);

  if (!_bmlw_setup (logger)) {
    TRACE ("bmlw setup failed\n");
    return EXIT_FAILURE;
  }
  // TODO: maybe switch to SOCK_SEQPACKET
  if ((server_socket = socket (PF_LOCAL, SOCK_STREAM, 0)) > 0) {
    TRACE ("server socket created\n");
  }

  unlink (socket_file);
  address.sun_family = PF_LOCAL;
  strcpy (&address.sun_path[1], socket_file);
  if (bind (server_socket, (struct sockaddr *) &address,
          sizeof (sa_family_t) + strlen (socket_file) + 1) != 0) {
    TRACE ("socket path already in use!\n");
  }
  // number of pending connections
  // upper limmit is /proc/sys/net/core/somaxconn usually 128 == SOMAXCONN
  // right we just have one anyway
  listen (server_socket, /* backlog of pending connections */ SOMAXCONN);
  addrlen = sizeof (struct sockaddr_in);
  client_socket =
      accept (server_socket, (struct sockaddr *) &address, &addrlen);
  if (client_socket > 0) {
    TRACE ("client connected\n");
  }
  while (running) {
    TRACE ("waiting for command ====================\n");
    bmlipc_clear (&bi);
    size = recv (client_socket, bi.buffer, IPC_BUF_SIZE, 0);
    if (size == 0) {
      TRACE ("got EOF\n");
      running = FALSE;
      continue;
    }
    if (size == -1) {
      TRACE ("ERROR: recv returned %d: %s\n", errno, strerror (errno));
      // TODO(ensonic): specific action depending on error
      continue;
    }
    bi.size = (int) size;
    TRACE ("got %d bytes\n", bi.size);
    // parse message
    id = bmlipc_read_int (&bi);
    if (bi.io_error) {
      TRACE ("message should be at least 4 bytes");
      continue;
    }
    TRACE ("command: %d\n", id);
    bmlipc_clear (&bo);
    switch (id) {
      case 0:
        running = FALSE;
        break;
      case BM_SET_MASTER_INFO:
        _bmlw_set_master_info (&bi, &bo);
        break;
      case BM_OPEN:
        _bmlw_open (&bi, &bo);
        break;
      case BM_CLOSE:
        _bmlw_close (&bi, &bo);
        break;
      case BM_GET_MACHINE_INFO:
        _bmlw_get_machine_info (&bi, &bo);
        break;
      case BM_GET_GLOBAL_PARAMETER_INFO:
        _bmlw_get_global_parameter_info (&bi, &bo);
        break;
      case BM_GET_TRACK_PARAMETER_INFO:
        _bmlw_get_track_parameter_info (&bi, &bo);
        break;
      case BM_GET_ATTRIBUTE_INFO:
        _bmlw_get_attribute_info (&bi, &bo);
        break;
      case BM_DESCRIBE_GLOBAL_VALUE:
        _bmlw_describe_global_value (&bi, &bo);
        break;
      case BM_DESCRIBE_TRACK_VALUE:
        _bmlw_describe_track_value (&bi, &bo);
        break;
      case BM_NEW:
        _bmlw_new (&bi, &bo);
        break;
      case BM_FREE:
        _bmlw_free (&bi, &bo);
        break;
      case BM_INIT:
        _bmlw_init (&bi, &bo);
        break;
      case BM_GET_TRACK_PARAMETER_VALUE:
        _bmlw_get_track_parameter_value (&bi, &bo);
        break;
      case BM_SET_TRACK_PARAMETER_VALUE:
        _bmlw_set_track_parameter_value (&bi, &bo);
        break;
      case BM_GET_GLOBAL_PARAMETER_VALUE:
        _bmlw_get_global_parameter_value (&bi, &bo);
        break;
      case BM_SET_GLOBAL_PARAMETER_VALUE:
        _bmlw_set_global_parameter_value (&bi, &bo);
        break;
      case BM_GET_ATTRIBUTE_VALUE:
        _bmlw_get_attribute_value (&bi, &bo);
        break;
      case BM_SET_ATTRIBUTE_VALUE:
        _bmlw_set_attribute_value (&bi, &bo);
        break;
      case BM_TICK:
        _bmlw_tick (&bi, &bo);
        break;
      case BM_WORK:
        _bmlw_work (&bi, &bo);
        break;
      case BM_WORK_M2S:
        _bmlw_work_m2s (&bi, &bo);
        break;
      case BM_STOP:
        _bmlw_stop (&bi, &bo);
        break;
      case BM_ATTRIBUTES_CHANGED:
        _bmlw_attributes_changed (&bi, &bo);
        break;
      case BM_SET_NUM_TRACKS:
        _bmlw_set_num_tracks (&bi, &bo);
        break;
      case BM_SET_CALLBACKS:
        TRACE ("FIXME");
        break;
      default:
        break;
    }
    if (bo.size) {
      size = send (client_socket, bo.buffer, bo.size, MSG_NOSIGNAL);
      TRACE ("sent %d of %d bytes\n", size, bo.size);
      if (size == -1) {
        TRACE ("ERROR: send returned %d: %s\n", errno, strerror (errno));
        // TODO(ensonic): specific action depending on error
      }
    }
  }
  close (client_socket);
  close (server_socket);
  unlink (socket_file);

  _bmlw_finalize ();
  TRACE ("end\n");
  return EXIT_SUCCESS;
}