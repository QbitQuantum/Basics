/**
 * Pads a specified number of bytes to the memory writer to maintain alignment
 */
void PadMemoryWriter(FMemoryWriter* MemoryWriter, uint8*& TrackData, const int32 Alignment)
{
	const PTRINT ByteStreamLoc = (PTRINT) TrackData;
	const int32 Pad = static_cast<int32>( Align( ByteStreamLoc, Alignment ) - ByteStreamLoc );
	const uint8 PadSentinel = 85; // (1<<1)+(1<<3)+(1<<5)+(1<<7)
	
	for ( int32 PadByteIndex = 0; PadByteIndex < Pad; ++PadByteIndex )
	{
		MemoryWriter->Serialize( (void*)&PadSentinel, sizeof(uint8) );
	}
	TrackData += Pad;
}