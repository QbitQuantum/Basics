void rcv_n_chk_against_rfc864_pattern(TCPSocket &sock)
{
    static const size_t total_size = 1024 * 100;
    static const size_t buff_size = 1220;
    uint8_t buff[buff_size];
    size_t recvd_size = 0;

    Timer timer;
    timer.start();

    // Verify received data
    while (recvd_size < total_size) {
        int rd = sock.recv(buff, buff_size);
        TEST_ASSERT(rd > 0);
        if (rd < 0) {
            break;
        }
        check_RFC_864_pattern(buff, rd, recvd_size);
        recvd_size += rd;
    }
    timer.stop();
    printf("MBED: Time taken: %fs\n", timer.read());
}