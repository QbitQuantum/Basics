void PadByteStream(TArray<uint8>& CompressedByteStream, const int32 Alignment, uint8 sentinel)
{
	int32 Pad = Align( CompressedByteStream.Num(), 4 ) - CompressedByteStream.Num();
	for ( int32 i = 0 ; i < Pad ; ++i )
	{
		CompressedByteStream.Add(sentinel);
	}
}