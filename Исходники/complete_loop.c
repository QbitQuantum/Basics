int main(int argc, char **argv)
{
  burrow_st *burrow;
  client_st client;
  msg_st *msg;
  int use_http = 0;

  argc--;
  argv++;

  if (strcmp(argv[0], "http") == 0) {
    use_http = 1;
    argc--;
    argv++;
  }

  if (argc < 4 || argc % 2 != 0)
    return -1;

  client.account = argv[0];
  client.queue = argv[1];
  argc -= 2;
  argv += 2;

  client.messages = NULL;
  client.message_count = 0;

  while (argc) {
    msg = malloc(sizeof(msg_st));
    if (!msg)
      return -2;

    msg->msg_id = argv[0];
    msg->body = (uint8_t *)argv[1];
    msg->body_size = strlen(argv[1]);
    msg->next = client.messages;
    client.messages = msg;
    client.message_count++;

    argc -= 2;
    argv += 2;
  }

  client.return_code = 0;
  client.current_message = client.messages;

  if (use_http == 0) {
    burrow = burrow_create(NULL, "dummy");
    printf("burrow = %p\n", burrow);
  } else {
    burrow = burrow_create(NULL, "http");
    printf("burrow = %p\n", burrow);
    burrow_backend_set_option(burrow, "server", "localhost");
    burrow_backend_set_option(burrow, "port", "8080");
  }

  burrow_set_context(burrow, &client);
  burrow_set_complete_fn(burrow, &_complete);
  burrow_set_log_fn(burrow, &_log);

  /* Insert the first one here to kick the loop off. This only sets start state,
     it doesn't run the loop. */
  msg = client.current_message;
  burrow_create_message(burrow, client.account, client.queue,
    msg->msg_id, msg->body, msg->body_size, NULL);

  /* This runs until there are no more tasks. */
  burrow_process(burrow);
  burrow_destroy(burrow);

  return client.return_code;
}