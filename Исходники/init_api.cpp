void app_start(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    MBED_HOSTTEST_TIMEOUT(5);
    MBED_HOSTTEST_SELECT(default);
    MBED_HOSTTEST_DESCRIPTION(Socket Abstraction Layer construction and utility test);
    MBED_HOSTTEST_START("SAL_INIT_UTIL");

    int tests_pass = 1;
    int rc;
    EthernetInterface eth;
    /* Initialise with DHCP, connect, and start up the stack */
    eth.init();
    eth.connect();

    do {
        socket_error_t err = lwipv4_socket_init();
        if (!TEST_EQ(err,SOCKET_ERROR_NONE)) {
            tests_pass = 0;
            break;
        }
        rc = socket_api_test_create_destroy(SOCKET_STACK_LWIP_IPV4, SOCKET_AF_INET6);
        tests_pass = tests_pass && rc;

        rc = socket_api_test_socket_str2addr(SOCKET_STACK_LWIP_IPV4, SOCKET_AF_INET6);
        tests_pass = tests_pass && rc;

    } while (0);
    MBED_HOSTTEST_RESULT(tests_pass);
}