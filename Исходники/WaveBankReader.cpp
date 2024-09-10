 void BigEndian()
 {
     *reinterpret_cast<uint32_t*>( this ) = _byteswap_ulong( *reinterpret_cast<uint32_t*>( this ) );
 }