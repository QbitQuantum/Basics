/***********************************************************************
 * tx_worker function
 * A function to be used in its own thread for transmitting.  Push all
 * tx values into the USRP buffer as USRP buffer space is available,
 * but allow other actions to occur concurrently.
 **********************************************************************/
void tx_worker(
    unsigned int bufflen,
    uhd::tx_streamer::sptr tx_stream,
    uhd::time_spec_t start_time,
    std::complex<int16_t>* vec_ptr,
    int end
){
    unsigned int acc_samps = 0;

    uhd::tx_metadata_t md;
    md.start_of_burst = true;
    md.has_time_spec = true;
    md.time_spec = start_time;

    size_t spb = tx_stream->get_max_num_samps();
    if (spb > bufflen) spb = bufflen;

	while(acc_samps < bufflen-spb){
            size_t nsamples = tx_stream->send(vec_ptr, spb, md);
            vec_ptr += spb;
            acc_samps += nsamples;
            //std::cout << acc_samps <<std::endl;
            md.start_of_burst = false;
            md.has_time_spec = false;
    }
    // Now on the last packet
    if (end) md.end_of_burst = true;
    spb = bufflen - acc_samps;
    size_t nsamples = tx_stream->send(vec_ptr, spb, md);
}