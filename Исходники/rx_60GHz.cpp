// Thread to import data from the USRP !Size of the arrays in complex -> 2*buffer_size !
void usrpGetData(uhd::rx_streamer::sptr rx_stream, uhd::usrp::multi_usrp::sptr dev, size_t buffer_size, board_60GHz_RX *my_60GHz_RX) {
    // Set priority of the thread
    int which = PRIO_PROCESS;
    id_t pid;
    int priority = -20;
    int ret;

    pid = getpid();
    ret = setpriority(which, pid, priority);
    if(ret!=0) {
        std::cout << "Main priority went wrong in usrpT: " << ret << std::endl ;
    }

    // Create storage for a single buffer from USRP
    short *buff_short;
    buff_short=new short[2*buffer_size];


    size_t n_rx_last;
    uhd::rx_metadata_t md;
    //int time=buffer_size/(25)-100; // microsecondes

    while (1) {
        n_rx_last=0;

        // Fill buff_short
        while (n_rx_last==0) {
            n_rx_last=rx_stream->recv(&buff_short[0], buffer_size, md, 3.0);
            std::this_thread::yield(); // Avoid active waiting
        };

        // Check if no overflow
        if (n_rx_last!=buffer_size) {
            std::cerr << "I expect the buffer size to be always the same!\n";
            std::cout<<"Read only:"<<n_rx_last<<"\n";
            std::cout<<"Buffer:"<<buffer_size<<"\n";
            //exit(1);
        };

        // Add the just received buffer to the queue
        mtxUsrp.lock();
        usrpQ.push(buff_short);
        mtxUsrp.unlock();
        // Change memory cell used
        buff_short=new short [2*buffer_size];

        // Gives the start to detection part
        sem_post( &usrpReady);

    }//end while 1
}