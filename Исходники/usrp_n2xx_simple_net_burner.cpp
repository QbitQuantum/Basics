/***********************************************************************
 * Find USRP N2XX with specified IP address and return type
 **********************************************************************/
boost::uint32_t find_usrp(udp_simple::sptr udp_transport){
    boost::uint32_t hw_rev;
    bool found_it = false;

    const usrp2_fw_update_data_t *update_data_in = reinterpret_cast<const usrp2_fw_update_data_t *>(usrp2_update_data_in_mem);
    usrp2_fw_update_data_t hw_info_pkt = usrp2_fw_update_data_t();
    hw_info_pkt.proto_ver = htonx<boost::uint32_t>(USRP2_FW_PROTO_VERSION);
    hw_info_pkt.id = htonx<boost::uint32_t>(GET_HW_REV_CMD);
    udp_transport->send(boost::asio::buffer(&hw_info_pkt, sizeof(hw_info_pkt)));

    //Loop and receive until the timeout
    size_t len = udp_transport->recv(boost::asio::buffer(usrp2_update_data_in_mem), UDP_TIMEOUT);
    if(len > offsetof(usrp2_fw_update_data_t, data) and ntohl(update_data_in->id) == GET_HW_REV_ACK){
        hw_rev = ntohl(update_data_in->data.hw_rev);
        if(filename_map.has_key(hw_rev)){
            std::cout << boost::format("Found %s.\n\n") % filename_map[hw_rev];
            found_it = true;
        }
        else throw std::runtime_error("Invalid revision found.");
    }
    if(not found_it) throw std::runtime_error("No USRP N2XX found.");

    return hw_rev;
}