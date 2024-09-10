/***********************************************************************
 * Transmit thread
 **********************************************************************/
static void tx_thread(uhd::usrp::multi_usrp::sptr usrp,
    uhd::tx_streamer::sptr tx_stream,
    const double tx_wave_freq,
    const double tx_wave_ampl)
{
    uhd::set_thread_priority_safe();

    // set max TX gain
    usrp->set_tx_gain(usrp->get_tx_gain_range().stop());

    // setup variables and allocate buffer
    uhd::tx_metadata_t md;
    md.has_time_spec = false;
    std::vector<samp_type> buff(tx_stream->get_max_num_samps() * 10);

    // values for the wave table lookup
    size_t index         = 0;
    const double tx_rate = usrp->get_tx_rate();
    const size_t step    = boost::math::iround(wave_table_len * tx_wave_freq / tx_rate);
    wave_table table(tx_wave_ampl);

    // fill buff and send until interrupted
    while (not boost::this_thread::interruption_requested()) {
        for (size_t i = 0; i < buff.size(); i++)
            buff[i] = table(index += step);
        tx_stream->send(&buff.front(), buff.size(), md);
    }

    // send a mini EOB packet
    md.end_of_burst = true;
    tx_stream->send("", 0, md);
}