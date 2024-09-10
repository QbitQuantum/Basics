void storeDataX(uhd::rx_streamer::sptr rx_stream, uhd::usrp::multi_usrp::sptr dev, size_t buffer_size, uint nDetect){



  // Create storage for a single buffer from USRP
  short *buff_short;
  buff_short=new short[2*buffer_size]; 
 
  short *storage_short;
  storage_short=new short [2*nDetect];

  uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
	  
    std::cout << "Stop the transmitter by pressing ctrl-c \n";
	  
      stream_cmd.num_samps = buffer_size;
      stream_cmd.stream_now = true;
    
       stream_cmd.stream_mode=uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS;

       dev->issue_stream_cmd(stream_cmd);


  uhd::rx_metadata_t md;
  size_t n_rx_samps=0;

  int n_rx_last;

  while (1){
    n_rx_samps=0;
    // Fill the storage buffer loop
    while (n_rx_samps<nDetect){
      n_rx_last=0;
      // Fill buff_short
      while (n_rx_last==0) {
	n_rx_last=rx_stream->recv(&buff_short[0], buffer_size, md, 3.0);
	//std::this_thread::yield();
      };

      sec_count++;
      // Check if no overflow
      if (n_rx_last!=(int)buffer_size) {
	std::cerr << "I expect the buffer size to be always the same!\n";
	std::cout<<"Read only:"<<n_rx_last<<"\n";
	std::cout<<"Buffer:"<<buffer_size<<"\n";
	exit(1); 
      };
      
      // Fill storage
      int i1=2*n_rx_samps;
      int i2=0;   
      while ((i1<(int) (2*nDetect)) && (i2<2*((int) buffer_size))){	  
	storage_short[i1]=buff_short[i2];
	i1++; i2++;
      };
      
      //storage_short=buff_short;
      n_rx_samps=n_rx_samps+n_rx_last;
      //std::cout << "n_rx_samps=" << n_rx_samps  << std::endl;	 
    }//storage_short now full


    mtxQ.lock();
    bufferQ.push(buff_short);
    mtxQ.unlock();
    //delete buff_short;
    buff_short=new short [2*buffer_size]; // Change memory cell used

    //usleep(1000000/4);
    sem_post( &isReady); // Gives the start to detection part

  }//end while 1
}