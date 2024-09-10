void TLSSOCKET_ECHOTEST_BURST()
{
    TLSSocket *sock = new TLSSocket;
    tlssocket_connect_to_echo_srv(*sock);
    sock->sigio(callback(_sigio_handler, ThisThread::get_id()));

    // TX buffer to be preserved for comparison
    fill_tx_buffer_ascii(tls_global::tx_buffer, BURST_SIZE);

    int recvd;
    int bt_left;
    int sent;
    for (int i = 0; i < BURST_CNT; i++) {
        bt_left = BURST_SIZE;
        while (bt_left > 0) {
            sent = sock->send(&(tls_global::tx_buffer[BURST_SIZE - bt_left]), bt_left);
            if (sent == NSAPI_ERROR_WOULD_BLOCK) {
                if (osSignalWait(SIGNAL_SIGIO, SIGIO_TIMEOUT).status == osEventTimeout) {
                    TEST_FAIL();
                    goto END;
                }
                continue;
            } else if (sent < 0) {
                printf("[%02d] network error %d\n", i, sent);
                TEST_FAIL();
                goto END;
            }
            bt_left -= sent;
        }

        bt_left = BURST_SIZE;
        while (bt_left > 0) {
            recvd = sock->recv(&(tls_global::rx_buffer[BURST_SIZE - bt_left]), BURST_SIZE);
            if (recvd < 0) {
                printf("[%02d] network error %d\n", i, recvd);
                break;
            }
            bt_left -= recvd;
        }

        if (bt_left != 0) {
            TEST_FAIL_MESSAGE("bt_left != 0");
            goto END;
        }

        TEST_ASSERT_EQUAL(0, memcmp(tls_global::tx_buffer, tls_global::rx_buffer, BURST_SIZE));
    }
END:
    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock->close());
    delete sock;
}