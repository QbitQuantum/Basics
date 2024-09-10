int main( int argc, char *argv[] )
{
  // Minimal command-line checking.
  if ( argc < 3 || argc > 4 ) usage();

  FileWvIn input;
  InetWvOut output;

  // Load the file.
  try {
    input.openFile( (char *)argv[1] );
  }
  catch ( StkError & ) {
    exit( 1 );
  }

  // Set the global STK sample rate to the file rate.
  Stk::setSampleRate( input.getFileRate() );

  // Set input read rate.
  double rate = 1.0;
  if ( argc == 4 ) rate = atof( argv[3] );
  input.setRate( rate );

  // Find out how many channels we have.
  int channels = input.channelsOut();
  StkFrames frames( 4096, channels );

  // Attempt to connect to the socket server.
  try {
    //output.connect( 2006, Socket::PROTO_UDP, (char *)argv[2], channels, Stk::STK_SINT16 );
    output.connect( 2006, Socket::PROTO_TCP, (char *)argv[2], channels, Stk::STK_SINT16 );
  }
  catch ( StkError & ) {
    exit( 1 );
  }

  // Here's the runtime loop
  while ( !input.isFinished() )
    output.tick( input.tick( frames ) );

  return 0;
}