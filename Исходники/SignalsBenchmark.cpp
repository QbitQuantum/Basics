// profile time for emission with 4 slots, 2 in group 0 and 2 in group 1
static void benchSignalEmissionGroups()
{
	Signal<void ( void*, uint64_t )> sigIncrement;
	sigIncrement.connect( testCounterAdd2 );
	sigIncrement.connect( testCounterAdd2 );
	sigIncrement.connect( 1, testCounterAdd2 );
	sigIncrement.connect( 1, testCounterAdd2 );

	const uint64_t startCounter = TestCounter::get();
	const uint64_t benchStart = timestampBenchmark();

	uint64_t i;
	for( i = 0; i < 1000000; i++ )
		sigIncrement.emit( nullptr, 1 );

	const uint64_t benchDone = timestampBenchmark();
	const uint64_t endCounter = TestCounter::get();

	assert( endCounter - startCounter == ( i * 4 ) );

	cout << "OK" << endl;
	cout << "\tper emission: " << double( benchDone - benchStart ) / double( i ) << "ns"
	<< ", per slot: " << double( benchDone - benchStart ) / double( i * 4 ) << "ns"
	<< endl;
}