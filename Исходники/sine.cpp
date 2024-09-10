int main( int argc, char *argv[] )
{
  float base_freq = 220.0;
  int i;

  // Minimal command-line checking.
  if ( argc != 5 ) usage();

  int channels = (int) atoi( argv[1] );
  double time = atof( argv[3] );
  double srate = atof( argv[4] );

  // Create our object instances.
  FileWvOut output;
  SineWave **oscs = (SineWave **) malloc( channels * sizeof(SineWave *) );
  for ( i=0; i<channels; i++ ) oscs[i] = 0;

  // If you want to change the default sample rate (set in Stk.h), do
  // it before instantiating any objects!!
  Stk::setSampleRate( srate );

  // Define the sinewaves.
  for ( i=0; i<channels; i++ )
    oscs[i] = new SineWave;

  // Set oscillator frequency(ies) here ... somewhat random.
  for ( i=0; i<channels; i++ )
    oscs[i]->setFrequency( base_freq + i*(45.0) );

  long nFrames = (long) ( time * Stk::sampleRate() );
  StkFrames frames( nFrames, channels );

  // Open the soundfile for output.  Other file format options
  // include: FILE_SND, FILE_AIF, FILE_MAT, and FILE_RAW.  Other data
  // type options include: STK_SINT8, STK_SINT32, StkFloat32, and
  // StkFloat64.
  try {
    output.openFile( argv[2], channels, FileWrite::FILE_WAV, Stk::STK_SINT16 );
  }
  catch ( StkError & ) {
    goto cleanup;
  }

  // Here's the runtime code ... no loop
  for ( i=0; i<channels; i++ )
    oscs[i]->tick( frames, i );

  output.tick( frames );

 cleanup:
  for ( i=0; i<channels; i++ )
    delete oscs[i];
  free( oscs );

  return 0;
}