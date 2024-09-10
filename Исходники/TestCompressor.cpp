// CompressHelper
//------------------------------------------------------------------------------
void TestCompressor::CompressHelper( const char * fileName ) const
{
	// read some test data into a file
	AutoPtr< void > data;
	size_t dataSize;
	{
		FileStream fs;
		TEST_ASSERT( fs.Open( fileName ) );
		dataSize = (size_t)fs.GetFileSize();
		data = (char *)ALLOC( dataSize );
		TEST_ASSERT( (uint32_t)fs.Read( data.Get(), dataSize ) == dataSize );
	}

	OUTPUT( "File           : %s\n", fileName );
	OUTPUT( "Size           : %u\n", (uint32_t)dataSize );

	// compress the data to obtain size
	Compressor comp;
	comp.Compress( data.Get(), dataSize );
	size_t compressedSize = comp.GetResultSize();
	AutoPtr< char > compressedData( (char *)ALLOC( compressedSize ) );
	memcpy( compressedData.Get(), comp.GetResult(), compressedSize );
	float compressedPerc = ( (float)compressedSize / (float)dataSize ) * 100.0f;
	OUTPUT( "Compressed Size: %u (%2.1f%% of original)\n", (uint32_t)compressedSize, compressedPerc );

	// decompress to check we get original data back
	Compressor decomp;
	decomp.Decompress( compressedData.Get() );
	size_t uncompressedSize = decomp.GetResultSize();
	TEST_ASSERT( uncompressedSize == dataSize );
	for ( size_t i=0; i<uncompressedSize; ++i )
	{
		TEST_ASSERT( ( (char *)data.Get() )[ i ] == ( (char *)decomp.GetResult() )[ i ] );
	}

	// speed checks
	//--------------
	const size_t NUM_REPEATS( 100 );

	// compress the data several times to get more stable throughput value
	Timer t;
	for ( size_t i=0; i<NUM_REPEATS; ++i )
	{
		Compressor c;
		c.Compress( data.Get(), dataSize );
		TEST_ASSERT( c.GetResultSize() == compressedSize );
	}
	float compressTimeTaken = t.GetElapsed();
	double compressThroughputMBs = ( ( (double)dataSize / 1024.0 * (double)NUM_REPEATS ) / compressTimeTaken ) / 1024.0;
	OUTPUT( "     Comp Speed: %2.1f MB/s - %2.3fs (%u repeats)\n", (float)compressThroughputMBs, compressTimeTaken, NUM_REPEATS );
	
	// decompress the data
	Timer t2;
	for ( size_t i=0; i<NUM_REPEATS; ++i )
	{
		Compressor d;
		d.Decompress( compressedData.Get() );
		TEST_ASSERT( d.GetResultSize() == dataSize );
	}
	float decompressTimeTaken = t2.GetElapsed();
	double decompressThroughputMBs = ( ( (double)dataSize / 1024.0 * (double)NUM_REPEATS ) / decompressTimeTaken ) / 1024.0;
	OUTPUT( "   Decomp Speed: %2.1f MB/s - %2.3fs (%u repeats)\n", (float)decompressThroughputMBs, decompressTimeTaken, NUM_REPEATS );

	// time memcpy to compare with
	Timer t0;
	for ( size_t i=0; i<NUM_REPEATS; ++i )
	{
		char * mem = (char *)ALLOC( dataSize );
		memcpy( mem, data.Get(), dataSize );
		FREE( mem );
	}
	float memcpyTimeTaken = t0.GetElapsed();
	double memcpyThroughputMBs = ( ( (double)dataSize / 1024.0 * (double)NUM_REPEATS ) / memcpyTimeTaken ) / 1024.0;
	OUTPUT( "   MemCpy Speed: %2.1f MB/s - %2.3fs (%u repeats)\n", (float)memcpyThroughputMBs, memcpyTimeTaken, NUM_REPEATS );
}