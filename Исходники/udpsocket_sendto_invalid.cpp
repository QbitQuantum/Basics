void UDPSOCKET_SENDTO_INVALID()
{
    UDPSocket sock;
    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock.open(NetworkInterface::get_default_instance()));

    TEST_ASSERT(sock.sendto(NULL, 9, NULL, 0) < 0);
    TEST_ASSERT(sock.sendto("", 9, NULL, 0) < 0);
    TEST_ASSERT(sock.sendto("", 0, NULL, 0) < 0);

    nsapi_error_t result = sock.sendto(MBED_CONF_APP_ECHO_SERVER_ADDR, 9, NULL, 0);
    if (result != NSAPI_ERROR_UNSUPPORTED) {
        TEST_ASSERT_EQUAL(0, result);
    }

    TEST_ASSERT_EQUAL(5, sock.sendto(MBED_CONF_APP_ECHO_SERVER_ADDR, 9, "hello", 5));

    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock.close());
}