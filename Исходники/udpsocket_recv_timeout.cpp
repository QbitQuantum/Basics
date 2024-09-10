void UDPSOCKET_RECV_TIMEOUT()
{
    SocketAddress udp_addr;
    NetworkInterface::get_default_instance()->gethostbyname(MBED_CONF_APP_ECHO_SERVER_ADDR, &udp_addr);
    udp_addr.set_port(MBED_CONF_APP_ECHO_SERVER_PORT);

    static const int DATA_LEN = 100;
    char buff[DATA_LEN] = {0};

    UDPSocket sock;
    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock.open(NetworkInterface::get_default_instance()));
    sock.set_timeout(100);
    sock.sigio(callback(_sigio_handler, ThisThread::get_id()));

    int recvd;
    Timer timer;
    SocketAddress temp_addr;
    int pkt_success = 0;
    for (int i = 0; i < PKT_NUM; i++) {
        TEST_ASSERT_EQUAL(DATA_LEN, sock.sendto(udp_addr, buff, DATA_LEN));
        timer.reset();
        timer.start();
        recvd = sock.recvfrom(&temp_addr, buff, sizeof(buff));
        timer.stop();

        if (recvd == NSAPI_ERROR_WOULD_BLOCK) {
            osSignalWait(SIGNAL_SIGIO, SIGIO_TIMEOUT);
            printf("MBED: recvfrom() took: %dms\n", timer.read_ms());
            TEST_ASSERT_INT_WITHIN(51, 150, timer.read_ms());
            continue;
        } else if (recvd < 0) {
            printf("[bt#%02d] network error %d\n", i, recvd);
            continue;
        } else if (temp_addr != udp_addr) {
            printf("[bt#%02d] packet from wrong address\n", i);
            continue;
        }
        TEST_ASSERT_EQUAL(DATA_LEN, recvd);
        pkt_success++;
    }

    printf("MBED: %d out of %d packets were received.\n", pkt_success, PKT_NUM);
    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock.close());
}