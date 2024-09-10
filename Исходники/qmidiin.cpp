int main( int argc, char *argv[] )
{
  RtMidiIn *midiin = 0;
  std::vector<unsigned char> message;
  int nBytes, i;
  double stamp;

  // Minimal command-line check.
  if ( argc > 2 ) usage();

  // RtMidiIn constructor
  try {
    midiin = new RtMidiIn();
  }
  catch ( RtError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  // Check available ports vs. specified.
  unsigned int port = 0;
  unsigned int nPorts = midiin->getPortCount();
  if ( argc == 2 ) port = (unsigned int) atoi( argv[1] );
  if ( port >= nPorts ) {
    delete midiin;
    std::cout << "Invalid port specifier!\n";
    usage();
  }

  try {
    midiin->openPort( port );
  }
  catch ( RtError &error ) {
    error.printMessage();
    goto cleanup;
  }

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);

  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
  while ( !done ) {
    stamp = midiin->getMessage( &message );
    nBytes = message.size();
    for ( i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
    if ( nBytes > 0 )
      std::cout << "stamp = " << stamp << std::endl;

    // Sleep for 10 milliseconds.
    SLEEP( 10 );
  }

  // Clean up
 cleanup:
  delete midiin;

  return 0;
}