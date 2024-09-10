void speed_test_rx(struct etherate *eth)
{

    int16_t tx_ret = 0;
    int16_t rx_len = 0;

    // Wait for the first test frame to be received before starting the test loop
    uint8_t first_frame = false;
    while (!first_frame)
    {

        rx_len = recv(eth->intf.sock_fd, eth->frm.rx_buffer,
                      eth->params.f_size_total, MSG_PEEK);

        // Check if this is an Etherate test frame
        if (ntohl(*eth->frm.rx_tlv_value) == VALUE_TEST_SUB_TLV &&
            ntohs(*eth->frm.rx_sub_tlv_type) == TYPE_FRAMEINDEX)
        {

            first_frame = true;

        }  else {

           // If the frame is not an Etherate frame it needs to be
           // "consumed" otherwise the next MSG_PEEK will show the
           // same frame:
           rx_len = recv(eth->intf.sock_fd, eth->frm.rx_buffer,
                         eth->params.f_size_total, MSG_DONTWAIT);

        }

    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &eth->params.elapsed_time);

    // Rx test loop
    while (*eth->speed_test.testBase <= *eth->speed_test.testMax)
    {

        clock_gettime(CLOCK_MONOTONIC_RAW, &eth->params.current_time);

        // If one second has passed
        if ((eth->params.current_time.tv_sec - eth->params.elapsed_time.tv_sec) >= 1)
        {
            eth->params.s_elapsed += 1;
            eth->speed_test.b_speed   = (double)(eth->speed_test.b_rx - eth->speed_test.b_rx_prev) * 8 / 1000000;
            eth->speed_test.b_rx_prev = eth->speed_test.b_rx;
            eth->speed_test.f_speed   = (eth->params.f_rx_count - eth->params.f_rx_count_prev);
            eth->params.f_rx_count_prev = eth->params.f_rx_count;

            printf("%" PRIu64 "\t\t%.2f\t\t%" PRIu64 "\t\t%" PRIu64 "\t\t%" PRIu64 "\n",
                   eth->params.s_elapsed,
                   eth->speed_test.b_speed,
                   (eth->speed_test.b_rx / 1024) / 1024,
                   (eth->speed_test.f_speed),
                   eth->params.f_rx_count);

            if (eth->speed_test.b_speed > eth->speed_test.b_speed_max)
                eth->speed_test.b_speed_max = eth->speed_test.b_speed;

            if (eth->speed_test.f_speed > eth->speed_test.f_speed_max)
                eth->speed_test.f_speed_max = eth->speed_test.f_speed;

            eth->speed_test.b_speed_avg += eth->speed_test.b_speed;
            eth->speed_test.f_speed_avg += eth->speed_test.f_speed;
            eth->params.elapsed_time.tv_sec = eth->params.current_time.tv_sec;
            eth->params.elapsed_time.tv_nsec = eth->params.current_time.tv_nsec;

        }

        // Poll has been disabled in favour of a non-blocking recv (for now)
        rx_len = recv(eth->intf.sock_fd,
                      eth->frm.rx_buffer,
                      eth->params.f_size_total,
                      MSG_DONTWAIT);

        if (rx_len > 0)
        {

            // Check if this is an Etherate test frame
            if (likely(ntohl(*eth->frm.rx_tlv_value) == VALUE_TEST_SUB_TLV &&
                ntohs(*eth->frm.rx_sub_tlv_type) == TYPE_FRAMEINDEX))
            {

                // If a VLAN tag is used Linux helpfully strips it off
                if (eth->frm.vlan_id != VLAN_ID_DEF) rx_len += 4;

                // Update test stats
                eth->params.f_rx_count += 1;
                eth->speed_test.b_rx += rx_len;

                // Record if the frame is in-order, early or late
                if (likely(ntohll(*eth->frm.rx_sub_tlv_value) == eth->params.f_rx_count)) {
                    eth->params.f_rx_ontime  += 1;
                } else if (ntohll(*eth->frm.rx_sub_tlv_value) > eth->params.f_rx_count) {
                    eth->params.f_rx_early   += 1;
                } else if (ntohll(*eth->frm.rx_sub_tlv_value) < eth->params.f_rx_count) {
                    eth->params.f_rx_late    += 1;
                }

                // If running in ACK mode Rx needs to ACK to Tx host
                if (eth->params.f_ack)
                {

                    build_sub_tlv(&eth->frm, htons(TYPE_ACKINDEX),
                                  *eth->frm.rx_sub_tlv_value);

                    tx_ret = send(eth->intf.sock_fd,
                                  eth->frm.tx_buffer,
                                  eth->params.f_size_total,
                                  MSG_DONTWAIT);

                    if (tx_ret > 0)
                    {
                        eth->params.f_tx_count += 1;
                    } else {

                        if (errno != EAGAIN || errno != EWOULDBLOCK)
                        {
                            perror("Speed test Tx error ");
                            return;
                        }
                        
                    }

                    
                }

            } else {
                // Received a non-test frame
                eth->params.f_rx_other += 1;
            }

            // Check if Tx host has quit/died;
            if (unlikely(ntohl(*eth->frm.rx_tlv_value) == VALUE_DYINGGASP))
            {

                printf("\nTx host has quit\n");
                speed_test_results(eth);
                return;

            }
                  

        } else { // rx_len <= 0
            if (errno != EAGAIN || errno != EWOULDBLOCK)
                perror("Speed test Rx error ");
        }


    } // *testBase<=*testMax

}