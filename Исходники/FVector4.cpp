/**
 *	Convert this to a ubyte value, with zero mapping to zero and 255 mapping to 255, clamped.
 */
UINT32		CFVec4::QuantizeToU8( void ) const
{
	UINT32 uRV;
	const XMVECTOR& v4V = *reinterpret_cast<const XMVECTOR*>( this );
	XMStoreUByte4( reinterpret_cast<XMUBYTE4*>(&uRV), v4V );
	return uRV;
}