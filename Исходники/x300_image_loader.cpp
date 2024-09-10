/*
 * Ethernet communication functions
 */
static UHD_INLINE size_t x300_send_and_recv(udp_simple::sptr xport,
                                            uint32_t pkt_code,
                                            x300_fpga_update_data_t *pkt_out,
                                            uint8_t* data){
    pkt_out->flags = uhd::htonx<uint32_t>(pkt_code);
    xport->send(boost::asio::buffer(pkt_out, sizeof(*pkt_out)));
    return xport->recv(boost::asio::buffer(data, udp_simple::mtu), UDP_TIMEOUT);
}