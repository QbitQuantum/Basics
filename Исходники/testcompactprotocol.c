static void
test_read_and_write_primitives (void)
{
  int status;
  pid_t pid;
  ThriftSocket *tsocket = NULL;
  ThriftTransport *transport = NULL;
  ThriftCompactProtocol *tc = NULL;
  ThriftProtocol *protocol = NULL;
  gpointer binary = (gpointer *) TEST_STRING;
  guint32 len = strlen (TEST_STRING);
  int port = TEST_PORT;

  /* fork a server from the client */
  pid = fork ();
  assert (pid >= 0);

  if (pid == 0)
  {
    /* child listens */
    thrift_server_primitives (port);
    exit (0);
  } else {
    /* parent.  wait a bit for the socket to be created. */
    sleep (1);

    /* create a ThriftSocket */
    tsocket = g_object_new (THRIFT_TYPE_SOCKET, "hostname", "localhost",
                            "port", port, NULL);
    transport = THRIFT_TRANSPORT (tsocket);
    thrift_transport_open (transport, NULL);
    assert (thrift_transport_is_open (transport));

    /* create a ThriftCompactTransport */
    tc = g_object_new (THRIFT_TYPE_COMPACT_PROTOCOL, "transport",
                       tsocket, NULL);
    protocol = THRIFT_PROTOCOL (tc);
    assert (protocol != NULL);

    /* write a bunch of primitives */
    assert (thrift_compact_protocol_write_bool (protocol, TEST_BOOL, NULL) > 0);
    assert (thrift_compact_protocol_write_byte (protocol, TEST_BYTE, NULL) > 0);
    assert (thrift_compact_protocol_write_i16 (protocol, TEST_I16, NULL) > 0);
    assert (thrift_compact_protocol_write_i32 (protocol, TEST_I32, NULL) > 0);
    assert (thrift_compact_protocol_write_i64 (protocol, TEST_I64, NULL) > 0);
    assert (thrift_compact_protocol_write_i16 (protocol, TEST_NI16, NULL) > 0);
    assert (thrift_compact_protocol_write_i32 (protocol, TEST_NI32, NULL) > 0);
    assert (thrift_compact_protocol_write_i64 (protocol, TEST_NI64, NULL) > 0);
    assert (thrift_compact_protocol_write_i16 (protocol, 2, NULL) > 0);
    assert (thrift_compact_protocol_write_i32 (protocol, 2, NULL) > 0);
    assert (thrift_compact_protocol_write_i64 (protocol, 2, NULL) > 0);
    assert (thrift_compact_protocol_write_i16 (protocol, -2, NULL) > 0);
    assert (thrift_compact_protocol_write_i32 (protocol, -2, NULL) > 0);
    assert (thrift_compact_protocol_write_i64 (protocol, -2, NULL) > 0);
    assert (thrift_compact_protocol_write_double (protocol,
                                                 TEST_DOUBLE, NULL) > 0);
    assert (thrift_compact_protocol_write_string (protocol,
                                                 TEST_STRING, NULL) > 0);
    assert (thrift_compact_protocol_write_binary (protocol, binary,
                                                 len, NULL) > 0);
    assert (thrift_compact_protocol_write_binary (protocol, NULL, 0, NULL) > 0);
    assert (thrift_compact_protocol_write_binary (protocol, binary,
                                                 len, NULL) > 0);

    /* test write errors */
    transport_write_error = 1;
    assert (thrift_compact_protocol_write_byte (protocol, TEST_BYTE,
                                               NULL) == -1);
    assert (thrift_compact_protocol_write_i16 (protocol, TEST_I16, NULL) == -1);
    assert (thrift_compact_protocol_write_i32 (protocol, TEST_I32, NULL) == -1);
    assert (thrift_compact_protocol_write_i64 (protocol, TEST_I64, NULL) == -1);
    assert (thrift_compact_protocol_write_i16 (protocol, TEST_NI16,
                                               NULL) == -1);
    assert (thrift_compact_protocol_write_i32 (protocol, TEST_NI32,
                                               NULL) == -1);
    assert (thrift_compact_protocol_write_i64 (protocol, TEST_NI64,
                                               NULL) == -1);
    assert (thrift_compact_protocol_write_double (protocol, TEST_DOUBLE,
                                                 NULL) == -1);
    assert (thrift_compact_protocol_write_binary (protocol, binary, len,
                                                 NULL) == -1);
    transport_write_error = 0;

    /* test binary partial failure */
    transport_write_count = 0;
    transport_write_error_at = 1;
    assert (thrift_compact_protocol_write_binary (protocol, binary,
                                                 len, NULL) == -1);
    transport_write_error_at = -1;

    /* clean up */
    thrift_transport_close (transport, NULL);
    g_object_unref (tsocket);
    g_object_unref (protocol);
    assert (wait (&status) == pid);
    assert (status == 0);
  }
}