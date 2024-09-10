/***********************************************************************
 * Data capture routine
 **********************************************************************/
static void capture_samples(
    shd::smini::multi_smini::sptr smini,
    shd::rx_streamer::sptr rx_stream,
    std::vector<samp_type > &buff,
    const size_t nsamps_requested
){
    buff.resize(nsamps_requested);
    shd::rx_metadata_t md;

    shd::stream_cmd_t stream_cmd(shd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
    stream_cmd.num_samps = buff.size();
    stream_cmd.stream_now = true;
    smini->issue_stream_cmd(stream_cmd);
    const size_t num_rx_samps = rx_stream->recv(&buff.front(), buff.size(), md);

    //validate the received data
    if (md.error_code != shd::rx_metadata_t::ERROR_CODE_NONE){
        throw std::runtime_error(str(boost::format(
            "Unexpected error code 0x%x"
        ) % md.error_code));
    }
    //we can live if all the data didnt come in
    if (num_rx_samps > buff.size()/2){
        buff.resize(num_rx_samps);
        return;
    }
    if (num_rx_samps != buff.size()){
        throw std::runtime_error("did not get all the samples requested");
    }
}