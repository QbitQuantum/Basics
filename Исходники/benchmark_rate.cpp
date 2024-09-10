/***********************************************************************
 * Benchmark TX Rate
 **********************************************************************/
void benchmark_tx_rate(
        uhd::usrp::multi_usrp::sptr usrp,
        const std::string &tx_cpu,
        uhd::tx_streamer::sptr tx_stream,
        std::atomic<bool>& burst_timer_elapsed,
        const boost::posix_time::ptime &start_time,
        bool random_nsamps=false
) {
    uhd::set_thread_priority_safe();

    //print pre-test summary
    std::cout << boost::format(
        "[%s] Testing transmit rate %f Msps on %u channels"
    ) % NOW() % (usrp->get_tx_rate()/1e6) % tx_stream->get_num_channels() << std::endl;

    //setup variables and allocate buffer
    uhd::tx_metadata_t md;
    md.time_spec = usrp->get_time_now() + uhd::time_spec_t(INIT_DELAY);
    md.has_time_spec = (tx_stream->get_num_channels() > 1);
    const size_t max_samps_per_packet = tx_stream->get_max_num_samps();
    std::vector<char> buff(max_samps_per_packet*uhd::convert::get_bytes_per_item(tx_cpu));
    std::vector<const void *> buffs;
    for (size_t ch = 0; ch < tx_stream->get_num_channels(); ch++)
        buffs.push_back(&buff.front()); //same buffer for each channel
    md.has_time_spec = (buffs.size() != 1);

    if (random_nsamps) {
        std::srand((unsigned int)time(NULL));
        while (not burst_timer_elapsed) {
            size_t total_num_samps = rand() % max_samps_per_packet;
            size_t num_acc_samps = 0;
            const float timeout = 1;

            usrp->set_time_now(uhd::time_spec_t(0.0));
            while(num_acc_samps < total_num_samps){
                //send a single packet
                num_tx_samps += tx_stream->send(buffs, max_samps_per_packet, md, timeout)*tx_stream->get_num_channels();
                num_acc_samps += std::min(total_num_samps-num_acc_samps, tx_stream->get_max_num_samps());
            }
        }
    } else {
        while (not burst_timer_elapsed) {
            const size_t num_tx_samps_sent_now = tx_stream->send(buffs, max_samps_per_packet, md)*tx_stream->get_num_channels();
            num_tx_samps += num_tx_samps_sent_now;
            if (num_tx_samps_sent_now == 0) {
                num_timeouts_tx++;
                if ((num_timeouts_tx % 10000) == 1) {
                    std::cerr << "[" << NOW() << "] Tx timeouts: " << num_timeouts_tx << std::endl;
                }
            }
            md.has_time_spec = false;
        }
    }

    //send a mini EOB packet
    md.end_of_burst = true;
    tx_stream->send(buffs, 0, md);
}