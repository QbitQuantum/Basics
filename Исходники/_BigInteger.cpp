  int main()
  {
    printf( "\nBig Integer multiplication\n\n");
    
    
    /*******************************/
    /* Testing of functionality    */
    /*******************************/
    
    /*
    * For testing, we can use different patterns as control samples
    * Numbers of form 0xFFFFF...FF are fit, as you can immediatly check
      the result by yourself.
    */
    
    printf( "Checking consistency!\n" );
    
    {
      const bigintexpo k = 7;
      const bigintlength l = 1 << k; /* Length */
      
      /*Iteration*/
      long int v = 0, vmax = 10;
      
      for( v = 0; v < vmax; v++ ){
    
        bigint P[l], Q[l];
        bigint R1[2*l], R2[2*l];
        
        bigintlength i;
        srand( clock() + rand() + v );
        
        /* Fill in sample */
        for( i = 0; i < l; i++ )
        {
          /* P[i] = 0xFFFFFFFF; */
          P[i] = rand()*rand();
        }
        
        for( i = 0; i < l; i++ )
        {
          /* Q[i] = 0xFFFFFFFF; */
          Q[i] = rand()*rand();
        }
        
        /* Naiv method */
        NaivMultiplication( k, R1, P, Q );
        
        /* Karatsuba-Ofmann */
        Multiply( k, R2, P, Q );
        
        /* Comparing */
        if( Compare( l*2, R1, R2 ) != 0 )
        {
          printf("Error occurred!\n Length:%ld\n", l );
          printf("Naiv method:\n");
          OutputBigint( l*2, R1 );
          printf("Karatsuba-Ofmann:\n");
          OutputBigint( l*2, R2 );
          return 1;
        }
        
      }
      
    }
    
    printf( "Comparison ok\n\n" );
     
    
    
    /*******************************/
    /* Testing of functionality    */
    /* Numbers of arbitrary length */
    /*******************************/
    
    printf( "Testing multiplikation of arbitrary length numbers!\n" );
    
    {
      
      const bigintlength l_act = 32;
      /* Factors have size 32 in memory */
      /* Only a part of this will be used semantically */
      const bigintlength l_1 = 5;
      const bigintlength l_2 = 17;
      const bigintlength l_prod = l_1 + l_2;
      
      /* iteration*/
      long int v = 0, vmax = 10;
      
      for( v = 0; v < vmax; v++ ){
    
        bigint P[l_act], Q[l_act];
        bigint R1[l_act*2], R2[l_act*2];
        
        bigintexpo k = getFittingExponent( l_1 > l_2 ? l_1 : l_2 );
        
        assert( k == 5 );
        
        bigintlength i;
        srand( clock() + rand() + v );
        
        /* Fill in samples */
        SetZero( l_act, P );
        for( i = 0; i < l_1; i++ )
        {
          /* P[i] = 0xFFFFFFFF; */
          P[i] = rand()*rand();
        }
        
        SetZero( l_act, Q );
        for( i = 0; i < l_2; i++ )
        {
          /* Q[i] = 0xFFFFFFFF; */
          Q[i] = rand()*rand();
        }
        
        SetZero( l_act*2, R1 );
        SetZero( l_act*2, R2 );
        
        /* Naiv method */
        NaivMultiplication( k, R1, P, Q );
        
        /* Karatsuba-Ofmann */
        Multiplikation( R2, l_1, P, l_2, Q );
        
        /* Comparison */
        if( Compare( l_prod, R1, R2 ) != 0 && Compare( l_act*2, R1, R2 ) != 0 )
        {
          printf("Error occured with arbitrary length numbers\n" );
          printf("Naiv method:\n");
          OutputBigint( l_prod, R1 );
          printf("Karatsuba-Ofmann:\n");
          OutputBigint( l_prod, R2 );
          return 1;
        }
        
      }
      
    }
    
    printf( "Comparison ok\n\n" );
    
    
    
    
    /***************/
    /* Performance */
    /***************/
    
    printf( "performance test\n" );
    
    long int t1, t2;
    
    t1 = clock();
    
    {
      const bigintexpo k = 11;
      const bigintlength l = 1 << k; /* Number of digits */
      
      long int v = 0, vmax = 100;
      
      /* printf( "Multiply %ld-times two numbers of length %ld\n", vmax, l ); */
      printf( "Multiply %ld-times two numbers of length %ld in base 2^32-system\n", vmax, l );
      printf( "approx. %lld decimal digits\n", (long long) 9 * l );

      /*
      * We can use several samples:
      * Iterate one specific multiplication
      * A specific subset of mulitplications
      * random numbers
      * ...
      */
      
      for( v = 0; v < vmax; v++ ){
    
        bigint P[l], Q[l];
        bigint R[2*l];
        
        bigintlength i;
        
        srand( time(NULL) * rand() + v*v*v*v );
        for( i = 0; i < l; i++ )
        {
          /* P[i] = 0x12345678; */
          //P[i] = (v << 16) + v;
           P[i] = rand() * UINT_MAX * rand(); 
        }
        for( i = 0; i < l; i++ ){
          /* Q[i] = 0x12345678; */
          //Q[i] = (v << 16) + v;
          Q[i] = rand() * UINT_MAX * rand(); 
        }
        
        Multiply( k, R, P, Q );
        
      }
      
    }
    
    t2 = clock();
    
    printf( "time: %ld0 ms \n", (t2-t1)/10000 );
    
    return 0;
    
    
  }