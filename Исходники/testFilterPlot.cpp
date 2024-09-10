int main(int argc, char* argv[] )
{
    atexit( closeFiles );

    // Copy to char pointers
    char outputChanChar[1024];
    strcpy(outputChanChar, PERCEPTION_CHANNEL.c_str());
    char debugChanChar[1024];
    strcpy(debugChanChar, DEBUG_CHANNEL.c_str());

    // open the channels
    int r = ach_open( &channel, outputChanChar, NULL );
    int rdebug = ach_open( &debug_channel, debugChanChar, NULL );

    assert(ACH_OK == r && ACH_OK == rdebug);

    r = ach_flush(&channel);
    r = ach_flush(&debug_channel);

    // test receive
    double percep[NUM_OBJECTS][NDIM];
    memset(percep, 0, NUM_OBJECTS*NDIM*sizeof(double));
    double debug[NUM_OBJECTS][NDIM];
    memset(debug, 0, NUM_OBJECTS*NDIM*sizeof(double));
    size_t frame_size;

    // Open files for debug
    for( int i = 0; i < NUM_OBJECTS; ++i ) {
        char name[50];
        sprintf( name, "logging_est%d.txt", i );
        pF.push_back(fopen( name, "w+"));
    }

    int counter = 0;
    while( true ) {

        if( counter > 60 ) {
            std::cout << "Getting out of loop"<< std::endl;
            break;
        }

        // PERCEP CHANNEL
        r = ach_get( &channel, &percep,
                     sizeof(percep),
                     &frame_size,
                     NULL,
                     ACH_O_WAIT );

        std::cout << "Received traj (visible, x, y, angle): " << std::endl;
        print_arr_2d( percep, NUM_OBJECTS );

        // DEBUG CHANNEL
        r = ach_get( &debug_channel, &debug,
                     sizeof(debug),
                     &frame_size,
                     NULL,
                     ACH_O_WAIT );

        std::cout << "[DEBUG] Received traj (visible, x, y, angle): " << std::endl;
        print_arr_2d( debug, NUM_OBJECTS );


        // Store them (to cm and to degrees)
        for( int i = 0; i < NUM_OBJECTS; ++i ) {
            fprintf( pF[i], " %f %f %f %f %f %f \n", percep[i][0]*100.0, percep[i][1]*100.0, percep[i][2]*57.3, debug[i][0]*100.0, debug[i][1]*100.0, debug[i][2]*57.3 );
        }

        // Read every second
        usleep(0.25*1e6);

        counter++;
    }

    return 0;

}