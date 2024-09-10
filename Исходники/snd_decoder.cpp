/*
====================
idSampleDecoder::Shutdown
====================
*/
void idSampleDecoder::Shutdown( void ) {
	decoderMemoryAllocator.Shutdown();
	sampleDecoderAllocator.Shutdown();
}