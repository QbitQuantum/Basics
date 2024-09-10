int test_CountOddsAndEvensFilter( Network * net, const char * so_file )
{
    int num_odds=0, num_evens=0, retval, tag=0;
    PacketPtr buf;
    std::string testname("test_CountOddsAndEvens"); 

    test->start_SubTest(testname);

    int filter_id = net->load_FilterFunc( so_file,
                                             "aggr_CountOddsAndEvens" );
    if( filter_id == -1 ){
        test->print("Stream::load_FilterFunc() failure\n", testname);
        test->end_SubTest(testname, MRNTEST_FAILURE);
        return -1;
    }

    Communicator * comm_BC = net->get_BroadcastCommunicator( );
    Stream * stream = net->new_Stream(comm_BC, filter_id, SFILTER_WAITFORALL);

    if( stream->send(PROT_COUNTODDSANDEVENS, "") == -1 ){
        test->print("stream::send() failure\n", testname);
        test->end_SubTest(testname, MRNTEST_FAILURE);
        return -1;
    }

    if( stream->flush( ) == -1 ){
        test->print("stream::flush() failure\n", testname);
        test->end_SubTest(testname, MRNTEST_FAILURE);
        return -1;
    }

    retval = stream->recv(&tag, buf);
    assert( retval != 0 ); //shouldn't be 0, either error or block till data
    if( retval == -1){
        //recv error
        test->print("stream::recv() failure\n", testname);
        test->end_SubTest(testname, MRNTEST_FAILURE);
        return -1;
    }
    else{
        //Got data
        if( buf->unpack( "%d %d", &num_odds, &num_evens ) == -1 ){
            test->print("stream::unpack() failure\n", testname);
            test->end_SubTest(testname, MRNTEST_FAILURE);
            return -1;
        }
        char tmp_buf[256];
        sprintf(tmp_buf, "num_odds = %d; num_evens = %d\n",
                num_odds, num_evens);
        test->print(tmp_buf, testname);
    }

    test->end_SubTest(testname, MRNTEST_SUCCESS);
    return 0;
}