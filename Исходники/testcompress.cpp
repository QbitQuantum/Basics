// Test basic interface
int test(int argc, const char *argv[])
{
	// Bad data to compress!
	char *data = (char *)malloc(DATA_SIZE);
	for(int l = 0; l < DATA_SIZE; ++l)
	{
		data[l] = l*23;
	}
	
	// parameters about compression	
	int maxOutput = Compress_MaxSizeForCompressedData(DATA_SIZE);
	TEST_THAT(maxOutput >= DATA_SIZE);

	char *compressed = (char *)malloc(maxOutput);
	int compressedSize = 0;
	
	// Do compression, in small chunks
	{
		Compress<true> compress;
		
		int in_loc = 0;
		while(!compress.OutputHasFinished())
		{
			int ins = DATA_SIZE - in_loc;
			if(ins > CHUNK_SIZE) ins = CHUNK_SIZE;
			
			if(ins == 0)
			{
				compress.FinishInput();
			}
			else
			{
				compress.Input(data + in_loc, ins);
			}
			in_loc += ins;
			
			// Get output data
			int s = 0;
			do
			{
				TEST_THAT(compressedSize < maxOutput);
				s = compress.Output(compressed + compressedSize, maxOutput - compressedSize);
				compressedSize += s;
			} while(s > 0);
		}
	}
	
	// a reasonable test, especially given the compressability of the input data.
	TEST_THAT(compressedSize < DATA_SIZE);

	// decompression
	char *decompressed = (char*)malloc(DATA_SIZE * 2);
	int decomp_size = 0;
	{	
		Compress<false> decompress;
		
		int in_loc = 0;
		while(!decompress.OutputHasFinished())
		{
			int ins = compressedSize - in_loc;
			if(ins > DECOMP_CHUNK_SIZE) ins = DECOMP_CHUNK_SIZE;
			
			if(ins == 0)
			{
				decompress.FinishInput();
			}
			else
			{
				decompress.Input(compressed + in_loc, ins);
			}
			in_loc += ins;
			
			// Get output data
			int s = 0;
			do
			{
				TEST_THAT(decomp_size <= DATA_SIZE);
				s = decompress.Output(decompressed + decomp_size, (DATA_SIZE*2) - decomp_size);
				decomp_size += s;
			} while(s > 0);
		}
	}
	
	TEST_THAT(decomp_size == DATA_SIZE);
	TEST_THAT(::memcmp(data, decompressed, DATA_SIZE) == 0);

	::free(data);
	::free(compressed);
	::free(decompressed);
	
	return test_stream();
}