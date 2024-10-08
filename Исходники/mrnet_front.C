int main(int argc, char **argv)
{
    int send_val=32;
    int recv_val;
    int tag, retval;
    PacketPtr p;

    if( (argc != 4) && (argc != 5) ){
        fprintf(stderr, "Usage: %s <topology file> <so_file> <num BEs>\n", argv[0]);
        exit(-1);
    }
    const char * topology_file = argv[1];
    const char * so_file = argv[2];
    const char * dummy_argv=NULL;

    FILE * structureFile;
    structureFile = fopen ("/home/usw/Install/sight/sight/sight/mrnet/bin/mrnet.Attrib/structure","ab+");
    if (structureFile!=NULL) {
#ifdef DEBUG_ON
        printf("OUT File opened.. \n");
#endif
    }

    int nets = 1;

    int num_backends = 1;
    if( argc == 4 ){
        num_backends = atoi( argv[3] );
    }

    int n = 0;
    while( n++ < nets ) {

        saw_failure = false;

        if( nets > 1 )
            fprintf(stdout, "\n\n---------- Network Instance %d ----------\n\n", n);

#ifdef DEBUG_ON
        fprintf(stdout, "PID: %d top : %s , BE : %s dummy : %s num BEs : %d \n", getpid(),
                topology_file, "no initialized BE", dummy_argv, num_backends);
#endif
        // If backend_exe (2nd arg) and backend_args (3rd arg) are both NULL,
        // then all nodes specified in the topology are internal tree nodes.
        Network * net = Network::CreateNetworkFE( topology_file, NULL, NULL );
        if( net->has_Error() ) {
            net->perror("Network creation failed!!!");
            exit(-1);
        }

        if( ! net->set_FailureRecovery(false) ) {
            fprintf( stdout, "Failed to disable failure recovery\n" );
            delete net;
            return -1;
        }

        bool cbrett = net->register_EventCallback( Event::TOPOLOGY_EVENT,
                TopologyEvent::TOPOL_ADD_BE,
                BE_Add_Callback, NULL );
        if(cbrett == false) {
            fprintf( stdout, "Failed to register callback for back-end add topology event\n");
            delete net;
            return -1;
        }
        cbrett = net->register_EventCallback( Event::TOPOLOGY_EVENT,
                TopologyEvent::TOPOL_REMOVE_NODE,
                BE_Remove_Callback, NULL );
        if(cbrett == false) {
            fprintf( stdout, "Failed to register callback for back-end remove topology event\n");
            delete net;
            return -1;
        }

        // Query net for topology object
        NetworkTopology * topology = net->get_NetworkTopology();
        std::vector< NetworkTopology::Node * > internal_leaves;
        topology->get_Leaves(internal_leaves);
        topology->print(stdout);

        //print leaf info
        printLeafInfo(internal_leaves, num_backends);

        // Wait for backends to attach
        unsigned int waitfor_count = num_backends;
        fprintf( stdout, "Please start backends now.\n\nWaiting for %u backends to connect\n",
                waitfor_count );
        fflush(stdout);
        unsigned curr_count = 0;
        do {
            sleep(1);
            locker.set_mutex_lock(&cb_lock);
            curr_count = num_attach_callbacks;
            locker.set_mutex_unlock(&cb_lock);
            fprintf( stdout, " %d backends have been attached!\n", curr_count);
        } while( curr_count != waitfor_count );
#ifdef DEBUG_ON
        fprintf( stdout, "All %u backends have attached!\n", waitfor_count);
#endif
//        Make sure path to "so_file" is in LD_LIBRARY_PATH
        int filter_id = net->load_FilterFunc( so_file, "SightStreamAggregator" );
        if( filter_id == -1 ){
            fprintf( stderr, "Network::load_FilterFunc() failure\n" );
            delete net;
            return -1;
        }

        // A Broadcast communicator contains all the back-ends
        Communicator * comm_BC = net->get_BroadcastCommunicator( );

        // Create a stream that will use the Integer_Add filter for aggregation
        Stream * add_stream = net->new_Stream( comm_BC,
                                               filter_id,
//                                               TFILTER_SUM,
//                                               SFILTER_WAITFORALL );
                SFILTER_DONTWAIT );

        int num_backends2 = int(comm_BC->get_EndPoints().size());

        // Broadcast a control message to back-ends to send us "num_iters"
        // waves of integers
        tag = PROT_CONCAT;
        //total number of waves are calculated using --> total number of integers we like to send / number of intergers per wave
#ifdef DEBUG_ON
        fprintf( stdout, "preparing to send INIT tags.. num_be : %d\n", num_backends2);
#endif
        unsigned int num_iters= TOTAL_STREAM_SIZE / TOTAL_PACKET_SIZE;

        if( add_stream->send( tag, "%d %d", send_val, num_iters ) == -1 ){
            fprintf( stderr, "stream::send() failure\n" );
            return -1;
        }
        if( add_stream->flush( ) == -1 ){
            fprintf( stderr, "stream::flush() failure\n" );
            return -1;
        }
#ifdef DEBUG_ON
        fprintf( stdout, "INIT tag flush() done... \n");
#endif

/*
* Main  loop where merged output is recieved from child nodes
* */
        char* recv_Ar;
        unsigned length;
        int total_len = 0 ;
        // We expect "num_iters" aggregated responses from all back-ends
        while(true){

            retval = add_stream->recv(&tag, p);
#ifdef DEBUG_ON
            fprintf(stdout, "\n[FE: STREM->recv done ; retval : %d] \n", retval);
#endif
            if(tag == PROT_END_PHASE){
                //print any stream coming with protocol end phase
#ifdef DEBUG_ON
                fprintf(stdout, "FE: Iteration PROTOCOL END SUCCESS %d: \n", 0);
#endif
                if( p->unpack( "%ac", &recv_Ar, &length ) == -1 ){
                    fprintf( stderr, "PROTOCOL END stream::unpack() failure\n" );
                    return -1;
                }
                total_len+= length;
                for(int j = 0 ; j < length ; j++){
                    fprintf(structureFile, "%c", recv_Ar[j]);
                }
                fprintf(stdout, "\n[FE: PROTOCOL SUCCESS: Output stored: bytes written => most recent  : [%d] total : [%d] ] \n",
                        length, total_len);
                fflush(structureFile);
                break;
            }
            if( retval == 0 ) {
                //shouldn't be 0, either error or block for data, unless a failure occured
                fprintf( stderr, "stream::recv() returned zero\n" );
                if( saw_failure ) break;
                return -1;
            }
            if( retval == -1 ) {
                //recv error
                fprintf( stderr, "stream::recv() unexpected failure\n" );
                if( saw_failure ) break;
                return -1;
            }

            if( p->unpack( "%ac", &recv_Ar, &length ) == -1 ){
                fprintf( stderr, "stream::unpack() failure\n" );
                return -1;
            }

            total_len += length;
            for(int j = 0 ; j < length ; j++){
                fprintf(structureFile, "%c", recv_Ar[j]);
            }
//            fprintf(stdout, "\n[FE: Display values done!] \n");

        }

        if( saw_failure ) {
            fprintf( stderr, "FE: a network process has failed, killing network\n" );
            fflush(structureFile);
            fclose(structureFile);
            delete net;
        }
        else {
            delete add_stream;
            fflush(structureFile);
            fclose(structureFile);
            // Tell back-ends to exit
            Stream * ctl_stream = net->new_Stream( comm_BC, TFILTER_MAX,
                    SFILTER_WAITFORALL );
            if(ctl_stream->send(PROT_EXIT, "") == -1){
                fprintf( stderr, "stream::send(exit) failure\n" );
                return -1;
            }
            if(ctl_stream->flush() == -1){
                fprintf( stderr, "stream::flush() failure\n" );
                return -1;
            }
            retval = ctl_stream->recv(&tag, p);
            if( retval == -1){
                //recv error
                fprintf( stderr, "stream::recv() failure\n" );
                return -1;
            }
            delete ctl_stream;
            if( tag == PROT_EXIT ) {
                // The Network destructor will cause all internal and leaf tree nodes to exit
                delete net;
                break;
            }
        }
    }


    return 0;
}