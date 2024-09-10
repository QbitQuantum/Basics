// function that implements the kernel of the seismic modeling algorithm
void seismic_exec(float **VEL, float **PPF, float **APF, float **NPF, float* seismicPulseVector, int spPosX, int spPosY, int xDim, int yDim, int timeSteps)
{
  int i,j;  // spatial loops counters
  int t;    // time loop counter
  #ifdef _VERBOSE
    int progressTimer = -1;
  #endif

  // make sure packing _all_ the data into sets of 4 element is ok
  assert( xDim % 4 == 0 );

  #ifdef _VERBOSE
    printf("processing...\n");
    printf("point of explosion = %d, %d\n", spPosX, spPosY);
  #endif

  // there are 16 XMM registers in 64 bit mode, so there is no need to spill to stack
  __m128 s_ppf, s_vel, s_actual, s_above1, s_left1, s_under1, s_right1, s_two, s_sixteen, s_sixty;
  __m128 s_above2, s_under2, s_left2, s_right2;

  float two[4] = {2.0f, 2.0f, 2.0f, 2.0f };
  float sixteen[4] = {16.0f,16.0f,16.0f,16.0f};
  float sixty[4] = {60.f,60.f,60.f,60.f};

  // preload XMM registers with constant values.
  s_two = _mm_load_ps( two );
  s_sixteen = _mm_load_ps( sixteen );
  s_sixty = _mm_load_ps( sixty );

  // time loop
  for (t = 0; t < timeSteps; t++)
  {
    #ifdef _VVERBOSE
      printf("----------------------------------------------\ntimestep: %d\n\n", t );
    #endif

    // add pulse
    APF[spPosY][spPosX] += seismicPulseVector[t];

    for(i=2; i<(yDim-2); i++)
    {
      for(j=2 + ALIGNMENT_OFFSET; j<(xDim-2); j+=4)
      {
        s_ppf = _mm_load_ps( &(PPF[i][j]) );
        s_vel = _mm_load_ps( &(VEL[i][j]) );
        s_actual = _mm_load_ps( &(APF[i][j]) );

        s_left1 = _mm_load_ps( &(APF[i-1][j]) );
        s_left2 = _mm_load_ps( &(APF[i-2][j]) );
        s_right2 = _mm_load_ps( &(APF[i+2][j]) );
        s_right1 = _mm_load_ps( &(APF[i+1][j]) );
        s_above1 = _mm_loadu_ps( &(APF[i][j-1]) );
        s_under1 = _mm_loadu_ps( &(APF[i][j+1]) );
        s_above2 = _mm_loadl_pi( _mm_shuffle_ps(s_actual, s_actual, _MM_SHUFFLE(1, 0, 0, 0)),
                                &(APF[i][j-2]));

        s_under2 = _mm_loadh_pi( _mm_shuffle_ps(s_actual, s_actual, _MM_SHUFFLE(0, 0, 3, 2)),
                                &(APF[i][j+4]));

        // sum elements with an offset of one
        s_under1 = _mm_add_ps( s_under1, _mm_add_ps( s_above1, _mm_add_ps( s_left1, s_right1)));
        // sum elements with an offset of two
        s_above2 = _mm_add_ps( s_left2, _mm_add_ps( s_right2, _mm_add_ps( s_under2, s_above2)));
        // multiply with 16
        s_under1 = _mm_mul_ps( s_sixteen, s_under1 );
        //
        s_under1 = _mm_sub_ps( _mm_sub_ps( s_under1,  s_above2), _mm_mul_ps( s_sixty, s_actual ) );
        s_under1 = _mm_add_ps( _mm_mul_ps( s_vel, s_under1), _mm_sub_ps(_mm_mul_ps( s_two, s_actual ), s_ppf) );

        // save the result
        _mm_store_ps( &(NPF[i][j]), s_under1);

        #ifdef _VVERBOSE
          printf("[%d][%d]\n", i, j);
        #endif
      }
      #ifdef _VVERBOSE
        printf("\n");
      #endif
    }

    #ifdef _VERBOSE
//     shows one # at each 10% of the total processing time
      if (t/(timeSteps/10) > progressTimer )
      {
        printf("#");
        progressTimer++;
        fflush(stdout);
      }
    #endif

    // switch pointers instead of copying data
    PPF = APF;
    APF = NPF;
    NPF = PPF;
  }

  #ifdef _VERBOSE
    printf("\nend process!\n");
  #endif
}