t_int *leaker_perform(t_int *w)
{
  int i,j,odd,even;
  float a1,a2,b1,b2;

  t_leaker *x = (t_leaker *) (w[1]);
  t_float *in1 = (t_float *)(w[2]);
  t_float *in2 = (t_float *)(w[3]);
  t_float *in3 = (t_float *)(w[4]);
  t_float *out = (t_float *)(w[5]);
  t_int n = w[6];

  float fade_value = x->fade_value;	
  float *input1 = x->input1;
  float *input2 = x->input2;
  int inCount = x->inCount;
  int R = x->R;
  int N = x->N;
  int N2 = x->N2;
  int D = x->D;
  int Nw = x->Nw;
  float *Wanal = x->Wanal;
  float *Wsyn = x->Wsyn;
  float *output = x->output;
  float *buffer1 = x->buffer1;
  float *buffer2 = x->buffer2;
  float *channel1 = x->channel1;
  float *channel2 = x->channel2;
  int *sieve = x->sieve;
  int *bitshuffle = x->bitshuffle;
  float *trigland = x->trigland;
  float mult = x->mult;	

  /* dereference struncture  */	
  if( x->mute) {
    while(n--){
      *out++ = 0.;
    }
    return (w+7);
  }	
  if( x->bypass ) {
    while(n--){
      *out++ = *in1++;
    }
    return (w+7);
  } 

#if MSP
  if(x->fade_connected)
    fade_value = *in3++ * (float) N2;
#endif

#if PD
    fade_value = *in3++ * (float) N2;
#endif

  inCount += D;

  for ( j = 0 ; j < Nw - D ; j++ ){
    input1[j] = input1[j+D];
    input2[j] = input2[j+D];
  }
  for ( j = Nw - D; j < Nw; j++ ) {
    input1[j] = *in1++;
    input2[j] = *in2++;
  }

  fold(input1, Wanal, Nw, buffer1, N, inCount);		
  fold(input2, Wanal, Nw, buffer2, N, inCount);	
  rdft(N, 1, buffer1, bitshuffle, trigland);
  rdft(N, 1, buffer2, bitshuffle, trigland);


  for ( i = 0; i <= N2; i++ ) {
    odd = ( even = i<<1 ) + 1;
    if( fade_value <= 0 || fade_value < sieve[i]  ){
      a1 = ( i == N2 ? *(buffer1+1) : *(buffer1+even) );
      b1 = ( i == 0 || i == N2 ? 0. : *(buffer1+odd) );

      *(channel1+even) = hypot( a1, b1 ) ;
      *(channel1+odd) = -atan2( b1, a1 );
      *(buffer1+even) = *(channel1+even) * cos(*(channel1+odd));
      if ( i != N2 ){
	*(buffer1+odd) = -(*(channel1+even)) * sin(*(channel1+odd));
      }
    } else {
      a2 = ( i == N2 ? *(buffer2+1) : *(buffer2+even) );
      b2 = ( i == 0 || i == N2 ? 0. : *(buffer2+odd) );
      *(channel1+even) = hypot( a2, b2 ) ;
      *(channel1+odd) = -atan2( b2, a2 );
      *(buffer1+even) = *(channel1+even) * cos(*(channel1+odd) );
      if ( i != N2 ){
	*(buffer1+odd) = -(*(channel1+even)) * sin( *(channel1+odd) );
      }
    }
  }

  rdft( N, -1, buffer1, bitshuffle, trigland );
  overlapadd( buffer1, N, Wsyn, output, Nw, inCount);

  for ( j = 0; j < D; j++ )
    *out++ = output[j] * mult;

  for ( j = 0; j < Nw - D; j++ )
    output[j] = output[j+D];

  for ( j = Nw - D; j < Nw; j++ )
    output[j] = 0.;

  x->inCount = inCount % Nw;
  
  return (w+7);
}		