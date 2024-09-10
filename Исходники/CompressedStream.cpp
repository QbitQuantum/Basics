void CompressedStream::HandleBufferFull()
{
	Compress();
	AbstractStreamDecorator::HandleBufferFull();
}