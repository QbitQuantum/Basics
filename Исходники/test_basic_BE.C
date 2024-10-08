int main(int argc, char **argv){
    Stream * stream;
    PacketPtr pkt;
    int tag;
    char recv_char;
    char recv_uchar;
    int16_t recv_short;
    uint16_t recv_ushort;
    int32_t recv_int;
    uint32_t recv_uint;
    int64_t recv_long;
    uint64_t recv_ulong;
    float recv_float;
    double recv_double;
    char * recv_string;
    bool success=true;

	fprintf(stderr, "BE args...\n");
   	for(int i =0; i < argc; i++){
		fprintf(stderr, "Args were: %s\n", argv[i]);
	}
    /*if( argc != 6 ) {
        fprintf(stderr, "Usage: %s parent_hostname parent_port parent_rank my_hostname my_rank\n",
                argv[0]);
        exit( -1 );
    }*/

    Network * net = Network::CreateNetworkBE( argc, argv );

    do {
        if ( net->recv( &tag, pkt, &stream ) != 1 ) {
            fprintf(stderr, "BE: stream::recv() failure ... exiting\n");
            exit (-1);
        }

        switch(tag){
        case PROT_CHAR:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_CHAR ...\n");
#endif
            if( pkt->unpack( "%c", &recv_char ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%c) failure\n");
                success=false;
            }
            if( stream->send( tag, "%c", recv_char ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%c) failure\n");
                success=false;
            }
            break;
        case PROT_INT:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_INT ...\n");
#endif
            if( pkt->unpack( "%d", &recv_int ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%d) failure\n");
                success=false;
            }
            if( stream->send( tag, "%d", recv_int ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%d) failure\n");
                success=false;
            }
            break;
        case PROT_UINT:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_UINT ...\n");
#endif
            if( pkt->unpack( "%ud", &recv_uint ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%ud) failure\n");
                success=false;
            }
            if( stream->send( tag, "%ud", recv_uint ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%ud) failure\n");
                success=false;
            }
            break;
        case PROT_SHORT:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_SHORT ...\n");
#endif
            if( pkt->unpack( "%hd", &recv_short ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%hd) failure\n");
                success=false;
            }
            if( stream->send( tag, "%hd", recv_short ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%hd) failure\n");
                success=false;
            }
            break;
        case PROT_USHORT:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_USHORT ...\n");
#endif
            if( pkt->unpack( "%uhd", &recv_ushort ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%uhd) failure\n");
                success=false;
            }
            if( stream->send( tag, "%uhd", recv_ushort ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%uhd) failure\n");
                success=false;
            }
            break;
        case PROT_LONG:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_LONG ...\n");
#endif
            if( pkt->unpack( "%ld", &recv_long ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%ld) failure\n");
                success=false;
            }
            if( stream->send( tag, "%ld", recv_long ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%ld) failure\n");
                success=false;
            }
            break;
        case PROT_ULONG:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_ULONG ...\n");
#endif
            if( pkt->unpack( "%uld", &recv_ulong ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%uld) failure\n");
                success=false;
            }
            if( stream->send( tag, "%uld", recv_ulong ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%uld) failure\n");
                success=false;
            }
            break;
        case PROT_FLOAT:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_FLOAT ...\n");
#endif
            if( pkt->unpack( "%f", &recv_float ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%f) failure\n");
                success=false;
            }
            if( stream->send( tag, "%f", recv_float ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%f) failure\n");
                success=false;
            }
            break;
        case PROT_DOUBLE:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_DOUBLE ...\n");
#endif
            if( pkt->unpack( "%lf", &recv_double ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%lf) failure\n");
                success=false;
            }
            if( stream->send( tag, "%lf", recv_double ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%lf) failure\n");
                success=false;
            }
            break;
        case PROT_STRING:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_STRING ...\n");
#endif
            if( pkt->unpack( "%s", &recv_string ) == -1 ) {
                fprintf(stderr, "BE: stream::unpack(%%s) failure\n");
                success=false;
            }
            if( stream->send( tag, "%s", recv_string ) == -1 ) {
                fprintf(stderr, "BE: stream::send(%%s) failure\n");
                success=false;
            }
            if( stream->flush() == -1){
                fprintf(stderr, "BE: stream::flush() failure\n");
                return -1;
            }
            free(recv_string);
            break;
        case PROT_ALL:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_ALL ...\n");
#endif
            if( pkt->unpack( "%c %uc %hd %uhd %d %ud %ld %uld %f %lf %s",
                             &recv_char, &recv_uchar, &recv_short, &recv_ushort,
                             &recv_int, &recv_uint, &recv_long, &recv_ulong,
                             &recv_float, &recv_double, &recv_string ) == 1 ) {
                fprintf(stderr, "BE: stream::unpack(all) failure\n");
                success = false;
            }
            if( stream->send( tag, "%c %uc %hd %uhd %d %ud %ld %uld %f %lf %s",
                              recv_char, recv_uchar, recv_short, recv_ushort,
                              recv_int, recv_uint, recv_long, recv_ulong,
                              recv_float, recv_double, recv_string ) == 1 ) {
                fprintf(stderr, "BE: stream::send(all) failure\n");
                success=false;
            }
            break;
        case PROT_EXIT:
#if defined(DEBUG)
            fprintf( stderr, "BE: Processing PROT_EXIT ...\n");
#endif
            break;
        default:
            fprintf(stderr, "BE: Unknown Protocol: %d\n", tag);
            exit(-1);
        }

        if( tag != PROT_EXIT ) {
            if( stream->flush() == -1){
                fprintf(stderr, "BE: stream::flush() failure\n");
                return -1;
            }
        }

    } while( tag != PROT_EXIT );

    // FE delete net will shut us down, wait for it
    net->waitfor_ShutDown();
    if( net != NULL )
        delete net;

    return 0;
}