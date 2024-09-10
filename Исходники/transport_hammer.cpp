/***********************************************************************
 * TX Hammer
 **********************************************************************/
void tx_hammer(uhd::usrp::multi_usrp::sptr usrp, const std::string &tx_cpu, uhd::tx_streamer::sptr tx_stream){
    uhd::set_thread_priority_safe();

    uhd::tx_metadata_t md;
    const size_t max_samps_per_packet = tx_stream->get_max_num_samps();
    std::vector<char> buff(max_samps_per_packet*uhd::convert::get_bytes_per_item(tx_cpu));
    std::vector<void *> buffs;
    for (size_t ch = 0; ch < tx_stream->get_num_channels(); ch++)
        buffs.push_back(&buff.front()); //same buffer for each channel

    //print pre-test summary
    std::cout << boost::format(
        "Testing transmit rate %f Msps"
    ) % (usrp->get_tx_rate()/1e6) << std::endl;

    //setup variables and allocate buffer
    std::srand( time(NULL) );
    while(not boost::this_thread::interruption_requested()){
        size_t total_num_samps = rand() % 100000;
        size_t num_acc_samps = 0;
        float timeout = 1;

        usrp->set_time_now(uhd::time_spec_t(0.0));
        while(num_acc_samps < total_num_samps){

            //send a single packet
            num_tx_samps += tx_stream->send(buffs, max_samps_per_packet, md, timeout);

            num_acc_samps += std::min(total_num_samps-num_acc_samps, tx_stream->get_max_num_samps());
        }
        //send a mini EOB packet
        md.end_of_burst = true;
        tx_stream->send("", 0, md);
    }
}