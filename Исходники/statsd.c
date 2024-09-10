static int statsd_network_init(struct pollfd **ret_fds, /* {{{ */
                               size_t *ret_fds_num) {
  struct pollfd *fds = NULL;
  size_t fds_num = 0;

  struct addrinfo *ai_list;
  int status;

  char const *node = (conf_node != NULL) ? conf_node : STATSD_DEFAULT_NODE;
  char const *service =
      (conf_service != NULL) ? conf_service : STATSD_DEFAULT_SERVICE;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_PASSIVE | AI_ADDRCONFIG,
                              .ai_socktype = SOCK_DGRAM};

  status = getaddrinfo(node, service, &ai_hints, &ai_list);
  if (status != 0) {
    ERROR("statsd plugin: getaddrinfo (\"%s\", \"%s\") failed: %s", node,
          service, gai_strerror(status));
    return status;
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    int fd;
    struct pollfd *tmp;

    char str_node[NI_MAXHOST];
    char str_service[NI_MAXSERV];

    fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0) {
      ERROR("statsd plugin: socket(2) failed: %s", STRERRNO);
      continue;
    }

    /* allow multiple sockets to use the same PORT number */
    int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
      ERROR("statsd plugin: setsockopt (reuseaddr): %s", STRERRNO);
      close(fd);
      continue;
    }

    getnameinfo(ai_ptr->ai_addr, ai_ptr->ai_addrlen, str_node, sizeof(str_node),
                str_service, sizeof(str_service),
                NI_DGRAM | NI_NUMERICHOST | NI_NUMERICSERV);
    DEBUG("statsd plugin: Trying to bind to [%s]:%s ...", str_node,
          str_service);

    status = bind(fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0) {
      ERROR("statsd plugin: bind(2) to [%s]:%s failed: %s", str_node,
            str_service, STRERRNO);
      close(fd);
      continue;
    }

    tmp = realloc(fds, sizeof(*fds) * (fds_num + 1));
    if (tmp == NULL) {
      ERROR("statsd plugin: realloc failed.");
      close(fd);
      continue;
    }
    fds = tmp;
    tmp = fds + fds_num;
    fds_num++;

    memset(tmp, 0, sizeof(*tmp));
    tmp->fd = fd;
    tmp->events = POLLIN | POLLPRI;
    INFO("statsd plugin: Listening on [%s]:%s.", str_node, str_service);
  }

  freeaddrinfo(ai_list);

  if (fds_num == 0) {
    ERROR("statsd plugin: Unable to create listening socket for [%s]:%s.",
          (node != NULL) ? node : "::", service);
    return ENOENT;
  }

  *ret_fds = fds;
  *ret_fds_num = fds_num;
  return 0;
} /* }}} int statsd_network_init */

static void *statsd_network_thread(void *args) /* {{{ */
{
  struct pollfd *fds = NULL;
  size_t fds_num = 0;
  int status;

  status = statsd_network_init(&fds, &fds_num);
  if (status != 0) {
    ERROR("statsd plugin: Unable to open listening sockets.");
    pthread_exit((void *)0);
  }

  while (!network_thread_shutdown) {
    status = poll(fds, (nfds_t)fds_num, /* timeout = */ -1);
    if (status < 0) {

      if ((errno == EINTR) || (errno == EAGAIN))
        continue;

      ERROR("statsd plugin: poll(2) failed: %s", STRERRNO);
      break;
    }

    for (size_t i = 0; i < fds_num; i++) {
      if ((fds[i].revents & (POLLIN | POLLPRI)) == 0)
        continue;

      statsd_network_read(fds[i].fd);
      fds[i].revents = 0;
    }
  } /* while (!network_thread_shutdown) */

  /* Clean up */
  for (size_t i = 0; i < fds_num; i++)
    close(fds[i].fd);
  sfree(fds);

  return (void *)0;
} /* }}} void *statsd_network_thread */

static int statsd_config_timer_percentile(oconfig_item_t *ci) /* {{{ */
{
  double percent = NAN;
  double *tmp;
  int status;

  status = cf_util_get_double(ci, &percent);
  if (status != 0)
    return status;

  if ((percent <= 0.0) || (percent >= 100)) {
    ERROR("statsd plugin: The value for \"%s\" must be between 0 and 100, "
          "exclusively.",
          ci->key);
    return ERANGE;
  }

  tmp =
      realloc(conf_timer_percentile,
              sizeof(*conf_timer_percentile) * (conf_timer_percentile_num + 1));
  if (tmp == NULL) {
    ERROR("statsd plugin: realloc failed.");
    return ENOMEM;
  }
  conf_timer_percentile = tmp;
  conf_timer_percentile[conf_timer_percentile_num] = percent;
  conf_timer_percentile_num++;

  return 0;
} /* }}} int statsd_config_timer_percentile */