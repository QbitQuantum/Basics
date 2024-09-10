/*!
 * Test the time error message:
 *    Send a burst packet that occurs at a time in the past.
 *    We expect to get a time error async message.
 */
bool test_time_error_message(uhd::usrp::multi_usrp::sptr usrp, uhd::rx_streamer::sptr, uhd::tx_streamer::sptr tx_stream){
    std::cout << "Test time error message... " << std::flush;

    uhd::tx_metadata_t md;
    md.start_of_burst = true;
    md.end_of_burst   = true;
    md.has_time_spec  = true;
    md.time_spec      = uhd::time_spec_t(100.0); //send at 100s

    usrp->set_time_now(uhd::time_spec_t(200.0)); //time at 200s

    tx_stream->send("", 0, md);

    uhd::async_metadata_t async_md;
    if (not tx_stream->recv_async_msg(async_md)){
        std::cout << boost::format(
            "failed:\n"
            "    Async message recv timed out.\n"
        ) << std::endl;
        return false;
    }

    switch(async_md.event_code){
    case uhd::async_metadata_t::EVENT_CODE_TIME_ERROR:
        std::cout << boost::format(
            "success:\n"
            "    Got event code time error message.\n"
        ) << std::endl;
        return true;

    default:
        std::cout << boost::format(
            "failed:\n"
            "    Got unexpected event code 0x%x.\n"
        ) % async_md.event_code << std::endl;
        return false;
    }
}