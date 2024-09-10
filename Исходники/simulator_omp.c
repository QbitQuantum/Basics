/*------------------------------------------------------------------
Main driver for the simulator
------------------------------------------------------------------*/
int main( int argc, char **argv ){
    double *hz, *hhxh;     /* hamiltonian components */
    double complex *psi;   /* State vector */
    params_t par;
    uint64_t i, *largest, j, samples, maxIdx, ccount;
    struct timeval tend, tbegin;
    double delta;
    double tempV, maxV;
    
    //gettimeofday( &tbegin, NULL );
    
    /* - - - - - - - - - - - Parse configuration file - - - - - - - - - - -*/
    //if( argc < 3 ){
    if( argc < 4 ){
        fprintf( stderr, "Need a json configuration file or json string. Terminating...\n" );
        return 1;
    }

    parse_file( argv[1][1], argv[2], &par );
    samples = atoi( argv[3] );
    
    par.dim = 1 << par.nQ;
    
    hz   = (double *)calloc( (par.dim),sizeof(double) );
    hhxh = (double *)calloc( (par.dim),sizeof(double) );
    psi  = (double complex *)malloc( (par.dim)*sizeof(double complex) );
    
    /* - - - - - - Compute the Hamiltonian for the simulation - - - - - - -*/
    build_h( &par, hz, hhxh );
    free( par.al ); free( par.be ); free( par.de );

    ccount = 0UL;
    for( i = 0; i < samples; ++i ){
        /* - - - - - - Compute the state vector for the simulation - - - - - - */
        init_psi( &par, psi );
        
        /* - - - - - - - - - - - - Run the Simulation - - - - - - - - - - - - -*/
        run_sim( &par, hz, hhxh, psi );

        /* - - - - - - - - - - - - - Check results - - - - - - - - - - - - - - */
        maxV = 0.0;
        for( j = 0UL; j < par.dim; ++j ){
            tempV = cabs( psi[j]*psi[j] );
            if( tempV > maxV ){
                maxV = tempV;
                maxIdx = j;
            }
        }
        ccount += ( maxIdx == par.res ) ? 1UL : 0UL;
    }
    printf( "%f\n", ccount/(double)samples );

    /* - - - - - - - - - - - - - Check results - - - - - - - - - - - - - - */
    /*
    largest = (uint64_t *)calloc( par.L, sizeof(uint64_t) );
    findLargest( par.dim, par.L, psi, largest );
    for( i = par.L; i --> 0; ){ //remember that i is unsigned
        //printf( "|psi[%d]| = %.8f\n",
        printf( "%d %.8f\n",
            largest[i],
            cabs( psi[largest[i]]*psi[largest[i]] ) );
    }
    */
    //statm_t res;
    //read_off_memory_status( &res );
    
    /* - - - - - - - - - - - Clean up and output - - - - - - - - - - - - - */
    //free( largest );
    free( psi );
    free( hz );
    free( hhxh );
    
    //gettimeofday( &tend, NULL );
    //delta = ((tend.tv_sec - tbegin.tv_sec)*1000000u + tend.tv_usec - tbegin.tv_usec)/1.e6;
    //printf( "Total time: %f s\n", delta );
    //printf( "Memory used: %ld kB\n", res.resident );
    
    return 0;
}