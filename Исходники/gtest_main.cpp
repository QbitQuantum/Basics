void inline BSF( unsigned long* index, size_t& mask )
{
	_BitScanForward64( index, mask );
}