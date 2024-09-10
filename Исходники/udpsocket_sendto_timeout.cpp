void UDPSOCKET_SENDTO_TIMEOUT()
{
    char tx_buffer[100];
    fill_tx_buffer_ascii(tx_buffer, sizeof(tx_buffer));

    UDPSocket sock;
    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock.open(get_interface()));

    SocketAddress udp_addr;
    get_interface()->gethostbyname(MBED_CONF_APP_ECHO_SERVER_ADDR, &udp_addr);
    udp_addr.set_port(9);

    Timer timer;
    timer.start();
    int sent = sock.sendto(udp_addr, tx_buffer, sizeof(tx_buffer));
    timer.stop();
    TEST_ASSERT_EQUAL(sizeof(tx_buffer), sent);
    TEST_ASSERT(timer.read_ms() <= 100);

    timer.reset();
    timer.start();
    sent = sock.sendto(udp_addr, tx_buffer, sizeof(tx_buffer));
    timer.stop();
    TEST_ASSERT_EQUAL(sizeof(tx_buffer), sent);
    TEST_ASSERT(timer.read_ms() <= 100);
    printf("MBED: Time taken: %fs\n", timer.read());

    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock.close());
}